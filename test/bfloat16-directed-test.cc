#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <bits/stdc++.h>
#include "../source/bfloat16.hpp"
#include "utst.h"
#include <chrono>

using namespace std;

string dir1 = "/home/qy95/bfloat/output/my_test1.txt";
string tf_dir1 = "/home/qy95/bfloat/output/tf_test1.txt";
string dir2 = "/home/qy95/bfloat/output/my_test2.txt";
string tf_dir2 = "/home/qy95/bfloat/output/tf_test2.txt";
string dir_sub = "/home/qy95/bfloat/output/my_test_subtract.txt";
string tf_dir_sub = "/home/qy95/bfloat/output/tf_test_subtract.txt";
string dir_add = "/home/qy95/bfloat/output/my_test_add.txt";
string tf_dir_add = "/home/qy95/bfloat/output/tf_test_add.txt";
string dir_divide = "/home/qy95/bfloat/output/my_test_divide.txt";
string tf_dir_divide = "/home/qy95/bfloat/output/tf_test_divide.txt";
string dir_multiply = "/home/qy95/bfloat/output/my_test_multiply.txt";
string tf_dir_multiply = "/home/qy95/bfloat/output/tf_test_multiply.txt";


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
    float tmp = 3.73;
    for (size_t i = 0; i < 23; i++){
        Bfloat16 bfloat3 = tmp;
        UTST_ASSERT_FLOAT_EQ( bfloat3.binary2float(), tmp, 0.5);
        tmp += 5.6;
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
    Bfloat16 var12 = var10 + var11;
    UTST_ASSERT_FLOAT_EQ(var3.binary2float() / (45.5 + 30.33), 1.0, 0.9);
    UTST_ASSERT_FLOAT_EQ(var6.binary2float() / (124.5+ (-847.32)) , 1.0, 0.9);
    UTST_ASSERT_FLOAT_EQ(var9.binary2float() / (-33.5 + (-12.32)) , 1.0, 0.9);
    UTST_ASSERT_FLOAT_EQ(var12.binary2float() / (43.5 + 98.2) , 1.0, 0.9);
}

void test_case_bfloat16_creation_large_number(){
    cout << "\n" << __func__ << "\n" <<endl;
    Bfloat16 bfloat1 = 294.4;
    Bfloat16 bfloat2 = 3222.87;
    Bfloat16 bfloat3 = -6654.2;
    Bfloat16 bfloat4 = -847.32;
    UTST_ASSERT_FLOAT_EQ( bfloat1.binary2float(), 294.4, 5);
    UTST_ASSERT_FLOAT_EQ( bfloat2.binary2float(), 3222.87, 10 );
    UTST_ASSERT_FLOAT_EQ(bfloat3.binary2float(), -6654.2, 10);
    UTST_ASSERT_FLOAT_EQ(bfloat4.binary2float(), -847.32, 5);
}

// -------------------------------------------------------------------------------//
/* Comparison test with tensorflow bfloat16*/
// -------------------------------------------------------------------------------//

void float32_to_bfloat16_small_range_helper(){
    ofstream file1;
    file1.open (dir1);
    Bfloat16 bf1;
    for (float i = 0.12; i < 20.0; i+=3.0){
        bf1 = i;
        float ans = bf1.binary2float();
        file1 << ans <<"\n" ;
    }
    for (float i = 0.63; i < 20.0; i+=3.0){
        bf1 = i;
        float ans = bf1.binary2float();
        file1 << ans <<"\n" ;
    }
    for (float i = 0.432; i < 200.0; i+=3.0){
        bf1 = i;
        float ans = bf1.binary2float();
        file1 << ans <<"\n" ;
    }
    for (float i = 0.736; i < 200.0; i+=3.0){
        bf1 = i;
        float ans = bf1.binary2float();
        file1 << ans <<"\n" ;
    }
    file1.close();
}

void float32_to_bfloat16_large_range_helper(){
    ofstream file1;
    file1.open (dir2);
    Bfloat16 bf1;
    for (float i = 0.12; i < 1000.0; i+=34.0){
        bf1 = i;
        float ans = bf1.binary2float();
        file1 << ans <<"\n" ;
    }
    for (float i = 0.63; i < 1000.0; i+=47.0){
        bf1 = i;
        float ans = bf1.binary2float();
        file1 << ans <<"\n" ;
    }
    for (float i = 0.432; i < 2000.0; i+=97.0){
        bf1 = i;
        float ans = bf1.binary2float();
        file1 << ans <<"\n" ;
    }
    for (float i = 0.736; i < 5000.0; i+=106.0){
        bf1 = i;
        float ans = bf1.binary2float();
        file1 << ans <<"\n" ;
    }
    file1.close();
}

void comparison_helper(ifstream& f1, ifstream& f2, float precision){
    string s1, s2;
    if (f1 && f2){
        while(getline(f1,s1) && getline(f2, s2)){
            float bf1 = std::stof(s1);
            float bf2 = std::stof(s2);
            UTST_ASSERT_FLOAT_EQ( bf1 / bf2, 1.0, precision);
        }
    }
}

void test_case_float32_to_bfloat16_range_test(const string& dir1,
const string& tf_dir1, const string& test_name){
    cout << "\n" <<test_name<<"\n"<<endl;
    float32_to_bfloat16_small_range_helper();
    ifstream f1;
    ifstream tf_f1;
    f1.open(dir1);
    tf_f1.open(tf_dir1);
    comparison_helper(f1, tf_f1, 0.001);
    f1.close();
    tf_f1.close();
}

void test_case_bfloat16_comparison_subtraction(){
    cout << "\n" <<__func__<<"\n"<<endl;
    ofstream file1;
    file1.open (dir_sub);
    float cnt = 0.0;
    float ans = 0.0;
    while(cnt < 1000){
      Bfloat16 bf1 = (0.63 + cnt)*2.3;
      Bfloat16 bf2 = (0.37 + cnt);
      Bfloat16 bf3 = bf1 - bf2;
      ans = bf3.binary2float();
      file1 << bf1.binary2float()<<" - "<<bf2.binary2float()<<" = "<<ans<<"\n";
      cnt += 12.5;
    }
    file1.close();
    // comparison
    ifstream f;
    ifstream tf;
    f.open(dir_sub);
    tf.open(tf_dir_sub);
    comparison_helper(f, tf, 0.5);
    f.close();
    tf.close();
}

void test_case_bfloat16_comparison_addition(){
    cout << "\n" <<__func__<<"\n"<<endl;
    ofstream file1;
    file1.open (dir_add);
    float cnt = 0.0;
    while(cnt < 1000){
      Bfloat16 bf1 = (0.325 + cnt);
      Bfloat16 bf2 = (0.872 + cnt);
      Bfloat16 bf3 = bf1 + bf2;
      float ans = bf3.binary2float();
      file1 << bf1.binary2float()<<" + "<<bf2.binary2float()<<" = "<<ans << "\n";
      cnt += 3.4;
    }
    file1.close();
    // comparison
    ifstream f;
    ifstream tf;
    f.open(dir_add);
    tf.open(tf_dir_add);
    comparison_helper(f, tf, 0.6);
    f.close();
    tf.close();
}

void test_case_bfloat16_comparison_division(){
    cout << "\n" <<__func__<<"\n"<<endl;
    ofstream file1;
    file1.open (dir_divide);
    float cnt = 0.0;
    float val1 = 2.365;
    float val2 = 1.748;
    while(cnt < 1000){
        val1 = cnt + val1;
        val2 = val2 + 1.0;
        Bfloat16 bf1 = val1;
        Bfloat16 bf2 = val2;
        Bfloat16 bf3 = bf1 / bf2;
        float ans = bf3.binary2float();
        file1 << bf1.binary2float()<<" / "<<bf2.binary2float()<<" = "<<ans << "\n";
        cnt += 3.5;
    }
    file1.close();
    // comparison
    ifstream f;
    ifstream tf;
    f.open(dir_divide);
    tf.open(tf_dir_divide);
    comparison_helper(f, tf, 0.1);
    f.close();
    tf.close();
}

void test_case_bfloat16_comparison_multiply(){
    cout << "\n" <<__func__<<"\n"<<endl;
    ofstream file1;
    file1.open (dir_multiply);
    float cnt = 0.0;
    while(cnt < 50){
      Bfloat16 bf1 = (0.365 + cnt);
      Bfloat16 bf2 = (0.748 + cnt);
      Bfloat16 bf3 = bf1 * bf2;
      float ans = bf3.binary2float();
      file1 << bf1.binary2float()<<" * "<<bf2.binary2float()<<" = "<<ans << "\n";
      cnt += 1.4;
    }
    file1.close();
    // comparison
    ifstream f;
    ifstream tf;
    f.open(dir_multiply);
    tf.open(tf_dir_multiply);
    comparison_helper(f, tf, 0.1);
    f.close();
    tf.close();
}


int main( int argc, char** argv )
{
  int n = ( argc == 1 ) ? 0 : atoi( argv[1] );
  auto start = std::chrono::high_resolution_clock::now();
  if ( ( n == 0 ) || ( n == 0 ) ) test_case_float32_to_bfloat16_simple();
  if ( ( n == 0 ) || ( n == 1 ) ) test_case_float32_to_bfloat16_more();
  if ( ( n == 0 ) || ( n == 2 ) ) test_case_bfloat16_multiplication();
  if ( ( n == 0 ) || ( n == 3 ) ) test_case_bfloat16_addition();
  if ( ( n == 0 ) || ( n == 4 ) ) test_case_bfloat16_creation_large_number();
  if ( ( n == 0 ) || ( n == 5 ) ) test_case_float32_to_bfloat16_range_test(dir1, tf_dir1, "test_case_float32_to_bfloat16_small_range");
  if ( ( n == 0 ) || ( n == 6 ) ) test_case_float32_to_bfloat16_range_test(dir2, tf_dir2, "test_case_float32_to_bfloat16_large_range");
  if ( ( n == 0 ) || ( n == 7 ) ) test_case_bfloat16_comparison_subtraction();
  if ( ( n == 0 ) || ( n == 8 ) ) test_case_bfloat16_comparison_addition();
  if ( ( n == 0 ) || ( n == 9 ) ) test_case_bfloat16_comparison_division();
  if ( ( n == 0 ) || ( n == 10 ) ) test_case_bfloat16_comparison_multiply();
  auto finish = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = finish - start;
  std::cout << "Elapsed time: " << elapsed.count() << " s\n";
  
  return 0;
}