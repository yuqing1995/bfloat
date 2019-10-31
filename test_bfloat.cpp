#include <iostream>
#include "bfloat16.h"

using namespace std;

int main()
{
   cout<<"BFloat16 Calculation\n";
   // Test binary2float

   Bfloat16 bfloat1(45.5); // -8.1852
   Bfloat16 bfloat2(-0.000000000000125185); // -1.25185e-33
   Bfloat16 bfloat3(-1.0625); // -1.0625
   Bfloat16 bfloat4(1.625); // 1.625
   cout<<"binary2float:\nap_float1: " << bfloat1.binary2float() << endl;
   cout<<"ap_float2: " << bfloat2.binary2float() << endl;
   cout<<"ap_float3: " << bfloat3.binary2float() << endl;
   cout<<"ap_float4: " << bfloat4.binary2float() << endl;
   
   
   return 0;
}