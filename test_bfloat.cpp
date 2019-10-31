#include <iostream>
#include "bfloat16.hpp"

using namespace std;

int main()
{
   cout<<"BFloat16 Calculation\n";
   // Test binary2float

   Bfloat16 bfloat1(45.5); // -8.1852
   Bfloat16 bfloat2 = 23.4;
   Bfloat16 bfloat3(-0.0625); // -1.0625
   Bfloat16 bfloat4 = 1.625; // 1.625
   //bfloat1 + bfloat2;
   cout<<"binary2float:\nap_float1: " << bfloat1.binary2float() << endl;
   cout<<"ap_float2: " << bfloat2.binary2float() << endl;
   cout<<"ap_float3: " << bfloat3.binary2float() << endl;
   cout<<"ap_float4: " << bfloat4.binary2float() << endl;
   
   
   return 0;
}