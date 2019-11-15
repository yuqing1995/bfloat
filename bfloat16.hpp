#ifndef BFLOAT16_HPP
#define BFLOAT16_HPP

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <string>
#include <cstdint>

using namespace std;

class Bfloat16
{
public:
        // apfloat Constructor
        Bfloat16() {};
        Bfloat16(const float temp) {
            _bias = 127;
            _exp = 0;
            _frac = 0;
            float2binary(temp);
        }
        ~Bfloat16() {};
        // Operation Function 
        float binary2float();
        void float2binary(const float temp);
        Bfloat16 operator+(const Bfloat16& f);
        Bfloat16 operator-(const Bfloat16& f);
        Bfloat16 operator*( Bfloat16& f );
        Bfloat16 operator/( Bfloat16& f );
        Bfloat16& operator=(const float temp);
        bool operator==(const Bfloat16& f);
        bool operator<(const Bfloat16& f);
        bool operator>(const Bfloat16& f);
        // helper function (non-member function)
        void normalize2bfloatsUpwards(Bfloat16& lhs_f, Bfloat16& rhs_f);
        void normalize2bfloatsDownwards(Bfloat16& lhs_f, Bfloat16& rhs_f);
        void normalizebfloat(Bfloat16& f);
        
private:        
        // number of bits of exponent
        uint16_t _exp;
        // number of bits of precision
        uint16_t _frac;
        // Bias of exponent for fix 16
        uint8_t _bias;
        // true if it is a negative number or false vice versa
        bool _neg;
        
};


float Bfloat16::binary2float() {
    // Use formular v = s × 2^e × (1 + f) to transfer the floating point
    // Calculate the exponent value and bias based on the digit of exponent
    int e = _exp - _bias;
    // Calculate the f
    int tmp_frac = _frac;
    float f = 0.0;
    int reminder = 0;
    for (int i = 7; i > 0; i--){
        reminder = tmp_frac % 2;
        tmp_frac = tmp_frac / 2;
        f += reminder * (1/pow(2, i));
    }
    // Use formular to calculate the result value based on _neg
    return _neg == 1 ? float(0.0 - (pow(2, e) * (1 + f))) : float(pow(2, e) * (1 + f));
}

void Bfloat16::normalize2bfloatsUpwards(Bfloat16& lhs_f, Bfloat16& rhs_f){
    size_t dis = (lhs_f._exp > rhs_f._exp) ?
        (lhs_f._exp) - (rhs_f._exp) : (rhs_f._exp) - (lhs_f._exp);
    if (lhs_f._exp > rhs_f._exp ){
        rhs_f._exp = lhs_f._exp;
        rhs_f._frac = ((rhs_f._frac + 128) >> dis);
        lhs_f._frac |= (1 << 7);
    }
    else if (lhs_f._exp < rhs_f._exp ){
        lhs_f._exp = rhs_f._exp;
        lhs_f._frac >>= ((lhs_f._frac + 128) >> dis);
        rhs_f._frac |= (1 << 7);
    }
    else {
        lhs_f._frac |= (1 << 7);
        rhs_f._frac |= (1 << 7);
    }
}

void Bfloat16::normalize2bfloatsDownwards(Bfloat16& lhs_f, Bfloat16& rhs_f){
    size_t dis = (lhs_f._exp > rhs_f._exp) ?
        (lhs_f._exp) - (rhs_f._exp) : (rhs_f._exp) - (lhs_f._exp);
    if (lhs_f._exp > rhs_f._exp ){
        lhs_f._exp = rhs_f._exp;
        lhs_f._frac = ((lhs_f._frac + 128) << dis);
        rhs_f._frac |= (1 << 7);
    }
    else if (lhs_f._exp < rhs_f._exp ){
        rhs_f._exp = lhs_f._exp;
        rhs_f._frac = ((rhs_f._frac + 128) << dis);
        lhs_f._frac |= (1 << 7);
    }
    else {
        lhs_f._frac |= (1 << 7);
        rhs_f._frac |= (1 << 7);
    }
}

void Bfloat16::normalizebfloat(Bfloat16& f) {
    if (f._frac < 0) {
      f._neg = 1;
      f._frac = -f._frac;
    }
    else {
      f._neg = 0;
    }
    if (f._frac > 255) {
      int shift = f._frac >> 8;
      f._frac = f._frac >> shift;
      f._exp = f._exp + shift;
    }
    if (f._frac < 128) {
      f._frac = f._frac << 1;
      f._exp -= 1; 
    }
    f._frac -= 128;
}

Bfloat16 Bfloat16::operator+(const Bfloat16& f){
    Bfloat16 lhs_f = *this;
    Bfloat16 rhs_f = f;
    normalize2bfloatsUpwards(lhs_f, rhs_f);
    lhs_f._frac = (lhs_f._neg == 1 ? -lhs_f._frac : lhs_f._frac) +
      (rhs_f._neg == 1 ? -rhs_f._frac : rhs_f._frac);
    normalizebfloat(lhs_f);
    return lhs_f;
}

Bfloat16 Bfloat16::operator-(const Bfloat16& f){
    Bfloat16 lhs_f = *this;
    Bfloat16 rhs_f = f;
    normalize2bfloatsUpwards(lhs_f, rhs_f);
    lhs_f._frac = (lhs_f._neg == 1 ? -lhs_f._frac : lhs_f._frac) -
      (rhs_f._neg == 1 ? -rhs_f._frac : rhs_f._frac);
    normalizebfloat(lhs_f);
    return lhs_f;
}

Bfloat16 Bfloat16::operator*( Bfloat16& f ){
    Bfloat16 lhs_f = *this;
    Bfloat16 rhs_f = f;
    lhs_f._exp = lhs_f._exp + rhs_f._exp - lhs_f._bias;
    lhs_f._frac |= (1 << 7);
    rhs_f._frac |= (1 << 7);
    int temp = 0;
    for (size_t i = 0; i <= 7; i++){
        int lhs_tmp = lhs_f._frac << i;
        int rhs_tmp = rhs_f._frac & (1 << i);
        if (rhs_tmp > 0){
            temp += lhs_tmp;
        }
    }
    lhs_f._frac = temp >> 7;
    normalizebfloat(lhs_f);
    lhs_f._neg = (lhs_f._neg == rhs_f._neg) ? 0 : 1;
    return lhs_f;
}

Bfloat16 Bfloat16::operator/( Bfloat16& f ){
    Bfloat16 lhs_f = *this;
    Bfloat16 rhs_f = f;
    lhs_f._exp = lhs_f._exp - rhs_f._exp + lhs_f._bias;
    lhs_f._frac |= (1 << 7);
    rhs_f._frac |= (1 << 7);
    if (lhs_f._frac < rhs_f._frac){
        lhs_f._frac = rhs_f._frac;
    }
    //cout << "lhs_f.neg: " << lhs_f._neg<<", lhs_f.exp: "<<lhs_f._exp<<", lhs_f.frac: "<<lhs_f._frac<<endl;
    //cout << "rhs_f.neg: " << rhs_f._neg<<", rhs_f.exp: "<<rhs_f._exp<<", rhs_f.frac: "<<rhs_f._frac<<endl;
    //normalize2bfloatsDownwards(lhs_f, rhs_f);
    //cout << "lhs_f.neg: " << lhs_f._neg<<", lhs_f.exp: "<<lhs_f._exp<<", lhs_f.frac: "<<lhs_f._frac<<endl;
    //cout << "rhs_f.neg: " << rhs_f._neg<<", rhs_f.exp: "<<rhs_f._exp<<", rhs_f.frac: "<<rhs_f._frac<<endl;
    int temp = 0;
    for (size_t i = 0; i <= 7; i++){
        temp <<= 1;
        if (lhs_f._frac<<1 < rhs_f._frac){
            lhs_f._frac <<= 1;
        }
        else {
            temp |= 1;
            lhs_f._frac = lhs_f._frac - rhs_f._frac;
        }   
    }
    lhs_f._frac = temp;
    normalizebfloat(lhs_f);
    lhs_f._neg = (lhs_f._neg == rhs_f._neg) ? 0 : 1;
    return lhs_f;
}

bool Bfloat16::operator <( const Bfloat16& f){
    if (_neg == 1 && f._neg == 0){
        return true;
    }
    else if (f._neg == 1 && _neg == 0){
        return false;
    }
    else if (f._neg == 1 && _neg == 1){
        return (_exp > f._exp || (_exp == f._exp && _frac > f._frac));
    }
    else{
        return (_exp < f._exp || (_exp == f._exp && _frac < f._frac));
    }
}

bool Bfloat16::operator >( const Bfloat16& f){
    if (_neg == 1 && f._neg == 0){
        return false;
    }
    else if (f._neg == 1 && _neg == 0){
        return true;
    }
    else if (f._neg == 1 && _neg == 1){
        return (_exp < f._exp || (_exp == f._exp && _frac < f._frac));
    }
    else{
        return (_exp > f._exp || (_exp == f._exp && _frac > f._frac));
    }
}

bool Bfloat16::operator==(const Bfloat16& f2){
    return (_frac == f2._frac && _exp == f2._exp && _neg == f2._neg);
}

Bfloat16& Bfloat16::operator=(const float temp){
    _bias = 127;
    _exp = 0;
    _frac = 0;
    float2binary(temp);
    return *this;
}

void Bfloat16::float2binary(const float f) {
    // Assign private variable
    _neg = f < 0 ? 1 : 0;
    float temp = f > 0 ? f : (0 - f);
    int integer = temp;
    float fp = temp - integer;
    if (integer == 0){
        _exp = (int8_t)(log2(fp)) + _bias;
        _frac = 0;
        return;
    }
    int size = (int)(log2(integer));
    size_t idx = 0;
    for (; idx < size; idx++){
        _frac |= (uint8_t)(integer % 2) << idx;
        integer >>= 1;
    }
    _exp = size + _bias;
    _frac <<= (7 - idx);
    for(size_t i = 0; i < 7 - idx; i++){
        fp = 2.0 * fp;
        if (fp > 1){
            _frac |= 1 << (7 - idx - i - 1);
            fp = fp - 1;
        }
    }
    if (_frac == 127 && _exp == 255){
        cout << "Reach the maximum value" << endl;
        return;
    }
    if ( _frac & 1 && fp * 2.0 > 1 ){
        if (_frac == 127){
            _frac = 0;
            _exp += 1;
        }else{
            _frac += 1;
        }
    }
    
    //cout << "f: " << f<< ", neg: " << _neg<<", exp: "<<_exp<<", frac: "<<_frac<<endl;
}



#endif