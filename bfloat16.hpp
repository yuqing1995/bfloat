#ifndef BFLOAT16_V2_HPP
#define BFLOAT16_V2_HPP

#include <iostream>
#include <math.h>
#include <vector>
#include <string>

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
        void normalize(const Bfloat& f);
        Bfloat16 operator+(const Bfloat16& f);
        Bfloat16 operator-(const Bfloat16& f);
        Bfloat16 operator*(const Bfloat16& f);
        Bfloat16 operator/(const Bfloat16& f);
        bool operator==(const Bfloat16& f);
        bool operator<(const Bfloat16& f);
private:
        // number of bits of exponent
        // char _exp[8];
        int _exp;
        // number of bits of precision
        // char _frac[7];
        int _frac;
        // Bias of exponent for fix 16
        int _bias;
        // true if it is a negative number or false vice versa
        bool _neg;
};
void normalize(const Bfloat& f){
    int dis = abs(_exp - f._exp);
    if (_exp > f._exp ){
        f._exp = _exp;
        f._frac = (f._frac >> dis);
    }
    else if (_exp < f._exp){
        _exp = f._exp;
        _exp = (_exp >> dis);
    }else{}
}

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

Bfloat16 operator+(const Bfloat16& f){
    if (_neg != f._neg){
        
    }
    normalize(f);
    _frac = _frac + f._frac;
    // Shif bits when _frac is out of bound
    if (_frac > 127){
        int tmp = _frac % 127;
        _frac = (_frac >> tmp);
        _exp += tmp;
    }
}

Bfloat16 operator-(const Bfloat16& f){
    normalize(f);
    if (this._neg == f._neg && this._neg > 0){
        if (_frac < f._frac){
            this._frac = f._frac - this._frac;
            this._neg = 1;
        }
        else { // zero or positive case;
            this._frac = _frac - f._frac;
        }
    }
    else if (this._neg == f._neg && this._neg < 0){
        if (_frac > f._frac{
            this._frac = f._frac - this._frac;
            this._neg = 1;
        }
        else { // zero or positive case;
            this._frac = _frac - f._frac;
            this._neg = 0;
        }
    }
    else {
        // positive number
        _neg = 0;
        _frac = _frac + f._frac;
        if (_frac > 127){
          int tmp = _frac % 127;
          _frac = (_frac >> tmp);
          _exp += tmp;
        }
    }
}

bool operator <( const Bfloat16& f){
    if (_neg == 1 && f._neg == 0){
        return true;
    }
    else if (f._neg == 1 && _neg == 0){
        return false;
    }
    else if (f._neg == 1 && _neg == 1){
        return (_exp > f._exp || (_exp == f._exp && _frac > f._frac);
    }
    else{
        return (_exp < f._exp || (_exp == f._exp && _frac < f._frac);
    }
}

bool operator==(const Bfloat16& f){
    return (_frac == f._frac && _exp == _exp && _neg == f._neg);
}

void Bfloat16::float2binary(const float f) {
    // Assign private variable
    _neg = f < 0 ? 1 : 0;
    float temp = abs(f);
    cout << temp << endl;
    int integer = int(temp);
    float fp = temp - integer;
    cout << fp << endl;
    if (integer == 0){
        _exp = (int)(log2(fp)) + _bias;
        _frac = 0;
        return;
    }
    int size = (int)(log2(integer));
    cout << size << endl;
    int floatBinary[7];
    // Construct the binary array of char with '0' and '1'
    int idx = size - 2;
    for (; idx > 0; idx--){
        frac <= (integer % 2)
        floatBinary[idx] = (integer % 2);
        integer = integer / 2;
    }
    _exp = size + _bias;
    for(int i = idx; i < 7; i++){
        fp = 2 * fp;
        if (fp > 1){
            floatBinary[i] = 1;
            fp = fp - 1;
        }else{
            floatBinary[i] = 0;
        }
    }
    for (int i = 6; i >= 0; i--){
        _frac += floatBinary[i] == 1 ? pow(2, i) : 0;
    }
    cout << "neg: " << _neg<<" exp: "<<_exp<<" frac: "<<_frac<<endl;
}



#endif