#ifndef BFLOAT16_H
#define BFLOAT16_H

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
            _exp = "00000000";
            _frac = "0000000";
            exp_length = 8;
            frac_length = 7;
            float2binary(temp);
        }
        // Bfloat16(const bool neg){
        //     exp_length = 8;
        //     frac_length = 7;
        //     _neg = neg;
        //     _bias = 127;
        // }
        ~Bfloat16() {};
        // Operation Function 
        float binary2float();
        void float2binary(const float temp);

        Bfloat16 operator+(const Bfloat16& f);
        Bfloat16 operator-(const Bfloat16& f);
        Bfloat16 operator*(const Bfloat16& f);
        Bfloat16 operator/(const Bfloat16& f);
        Bfloat16 operator==(const Bfloat16& f);
    private:
        // number of bits of exponent
        // char _exp[8];
        string _exp;
        int exp_length;
        // number of bits of precision
        // char _frac[7];
        string _frac;
        int frac_length;
        // Bias of exponent for fix 16
        int _bias;
        // true if it is a negative number or false vice versa
        bool _neg;
};

float Bfloat16::binary2float() {
    // Use formular v = s × 2^e × (1 + f) to transfer the floating point
    // Calculate the exponent value and bias based on the digit of exponent
    int e = 0 - _bias;
    for (int i = 0; i < 8; i++){
        if (_exp[i] == '1'){
            e += pow(2, 7-i);
        }
    }
    // Calculate the f
    float f = 0.0;
    for (int i = 0; i < 7; i++){
        if (_frac[i] == '1'){
            f += pow(2, -i-1);
        }
    }
    // Use formular to calculate the result value based on _neg
    return _neg == 1 ? float(0.0 - (pow(2, e) * (1 + f))) : float(pow(2, e) * (1 + f));
}


void Bfloat16::float2binary(const float f) {
    // Assign private variable
    _neg = f < 0 ? 1 : 0;
    float temp = abs(f);
    int integer = int(temp);
    float fp = temp - integer;
    int size = log2(integer) + 1;
    // Construct the binary array of char with '0' and '1'
    for (int i=0; i<size; i++){
        _frac[i] = '0' + (integer % 2);
        integer = integer / 2;
    }
    int exp = size - 1 + _bias;
    for (int i = 0; i < 9; i++){
        _exp[8-i-1] = '0' + (exp % 2);
        exp = exp / 2;
    }
    if ( size - 1 < 7){
        for(int i = size; i < 7-size; i++){
            fp = 2 * fp;
            if (fp > 1){
                _frac[i] = '1';
                fp = fp - 1;
            }else{
                _frac[i] = '0';
            }
        }
    }

    cout << "neg: " << _neg<<" exp: "<<_exp<<" frac: "<<_frac<<endl;
}

#endif