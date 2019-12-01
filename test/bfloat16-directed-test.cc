#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include "../source/bfloat16.hpp"
#include "utst.h"

using namespace std;

void test_case_float32_to_bfloat16_simple(){
    cout << "\n" << __func__ << "\n" <<endl;
    Bfloat16 bfloat1(45.5);
    Bfloat16 bfloat2 = 30.33;
    Bfloat16 bfloat3 = 124.5;
    UTST_ASSERT_FLOAT_EQ( bfloat1.binary2float(), 45.5, 0.5);
    UTST_ASSERT_FLOAT_EQ( bfloat2.binary2float(), 30.33, 0.5 );
    UTST_ASSERT_FLOAT_EQ( bfloat3.binary2float(), 124.3,0.5);
}

void test_case_float32_to_bfloat16_more(){
    cout << "\n" << __func__ << "\n" <<endl;
    Bfloat16 bfloat1(45.5);
    Bfloat16 bfloat2 = 30.33;
    Bfloat16 bfloat3 = 124.5;
    UTST_ASSERT_FLOAT_EQ( bfloat1.binary2float(), 45.5, 0.5);
    UTST_ASSERT_FLOAT_EQ( bfloat2.binary2float(), 30.33, 0.5 );
    UTST_ASSERT_FLOAT_EQ( bfloat3.binary2float(), 124.5,0.5);
    float tmp = 3.73;
    for (size_t i = 0; i < 23; i++){
        bfloat3 = tmp;
        UTST_ASSERT_FLOAT_EQ( bfloat3.binary2float(), tmp, 0.5);
        tmp += 5.6;
    }
}

void test_case_float32_to_bfloat16_complex(ofstream& file1){
    cout << "\n" <<__func__<<"\n"<<endl;
    file1 << "\n" <<__func__<<"\n";
    Bfloat16 bf1;
    int foot = 0;
    for (float i = 0.12; i < 20.0; i+=5.0){
        bf1 = i;
        float ans = bf1.binary2float();
        UTST_ASSERT_FLOAT_EQ( ans, i, 0.5);
        file1 << foot++ << ", "<< ans <<"\n" ;
    }
    for (float i = 0.63; i < 20.0; i+=5.0){
        bf1 = i;
        float ans = bf1.binary2float();
        UTST_ASSERT_FLOAT_EQ( ans, i, 0.5);
        file1 << foot++ << ", "<< ans <<"\n" ;
    }
    for (float i = 20.432; i < 130.0; i+=8.0){
        bf1 = i;
        float ans = bf1.binary2float();
        UTST_ASSERT_FLOAT_EQ( ans, i, 0.5);
        file1 << foot++ << ", "<< ans <<"\n" ;
    }
    for (float i = 100.283; i < 1000; i+=33.0){
        bf1 = i;
        float ans = bf1.binary2float();
        UTST_ASSERT_FLOAT_EQ( ans, i, 2);
        file1 << foot++ << ", "<< ans <<"\n" ;
    }

}

void test_case_bfloat16_multiplication(){
    cout << "\n" << __func__ << "\n" <<endl;
    Bfloat16 var1(45.5);
    Bfloat16 var2 = 30.33;
    Bfloat16 var3 = var1 * var2;
    Bfloat16 var4 = 124.5;
    Bfloat16 var5 = -847.32;
    Bfloat16 var6 = var4 * var5;
    Bfloat16 var7 = -33.5;
    Bfloat16 var8 = -12.32;
    Bfloat16 var9 = var7 * var8;
    Bfloat16 var10 = 43.5;
    Bfloat16 var11 = 98.2;
    Bfloat16 var12 = var10 * var11;
    UTST_ASSERT_FLOAT_EQ(var3.binary2float(), (45.5 * 30.33), 100);
    UTST_ASSERT_FLOAT_EQ(var6.binary2float(), (124.5*-847.32) , 100);
    UTST_ASSERT_FLOAT_EQ(var9.binary2float(), (-33.5 * -12.32) , 100);
    UTST_ASSERT_FLOAT_EQ(var12.binary2float(), (43.5 * 98.2) , 100);
}

void test_case_bfloat16_addition(){
    cout << "\n" << __func__ << "\n" <<endl;
    Bfloat16 var1(45.5);
    Bfloat16 var2 = 30.33;
    Bfloat16 var3 = var1 + var2;
    Bfloat16 var4 = 124.5;
    Bfloat16 var5 = -847.32;
    Bfloat16 var6 = var4 + var5;
    Bfloat16 var7 = -33.5;
    Bfloat16 var8 = -12.32;
    Bfloat16 var9 = var7 + var8;
    Bfloat16 var10 = 43.5;
    Bfloat16 var11 = 98.2;
    Bfloat16 var12 = var7 + var8;
    UTST_ASSERT_FLOAT_EQ(var3.binary2float() / (45.5 + 30.33), 1.0, 0.9);
    UTST_ASSERT_FLOAT_EQ(var6.binary2float() / (124.5+ -847.32) , 1.0, 0.9);
    UTST_ASSERT_FLOAT_EQ(var9.binary2float() / (-33.5 + -12.32) , 1.0, 0.9);
    UTST_ASSERT_FLOAT_EQ(var12.binary2float() / (43.5 + 98.2) , 1.0, 0.9);
}

void test_case_bfloat16_creation_large_number(){
    cout << "\n" << __func__ << "\n" <<endl;
    Bfloat16 bfloat1 = 294.4;
    Bfloat16 bfloat2 = 3222.87;
    Bfloat16 bfloat3 = -6654.2;
    Bfloat16 bfloat4 = -847.32;
    UTST_ASSERT_FLOAT_EQ( bfloat1.binary2float(), 294.4, 5);
    UTST_ASSERT_FLOAT_EQ( bfloat2.binary2float(), 3222.87, 5 );
    UTST_ASSERT_FLOAT_EQ(bfloat3.binary2float(), -6654.2, 5);
    UTST_ASSERT_FLOAT_EQ(bfloat4.binary2float(), -847.32, 5);
}




int main( int argc, char** argv )
{
  int n = ( argc == 1 ) ? 0 : atoi( argv[1] );
  ofstream file1;
  file1.open ("test2.txt");
  if ( ( n == 0 ) || ( n == 0 ) ) test_case_float32_to_bfloat16_simple();
  if ( ( n == 0 ) || ( n == 1 ) ) test_case_float32_to_bfloat16_more();
  if ( ( n == 0 ) || ( n == 2 ) ) test_case_bfloat16_multiplication();
  if ( ( n == 0 ) || ( n == 3 ) ) test_case_float32_to_bfloat16_complex(file1);
  file1.close();
  if ( ( n == 0 ) || ( n == 4 ) ) test_case_bfloat16_addition();
  if ( ( n == 0 ) || ( n == 5 ) ) test_case_bfloat16_creation_large_number();
  return 0;
}