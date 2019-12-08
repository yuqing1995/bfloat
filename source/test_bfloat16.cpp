#include <iostream>
#include "bfloat16.hpp"

using namespace std;

int main()
{
   cout<<"--------------- BFloat16 Calculation --------------" <<endl;
   //Test binary2float
   // Bfloat16 bfloat1(859.283);
   //Bfloat16 bfloat2 = 0.325;
   Bfloat16 bfloat3 = 992;
   Bfloat16 bfloat4 = 992;
   //Bfloat16 bfloat5 = 4.272;
   //Bfloat16 bfloat6 = 255.325;
   //Bfloat16 bfloat7 = 130906;
   Bfloat16 bfloat9 = bfloat3 + bfloat4;
   //Bfloat16 bfloat10 = bfloat5 - bfloat4;
   //Bfloat16 bfloat11 = bfloat6 + bfloat7;
   
   // bool equal = bfloat1 == bfloat4;
   // bool compare = bfloat1 < bfloat2;
   // bool compare2 = bfloat3 > bfloat4;
   // bool compare3 = bfloat4 < bfloat2;
   
   // cout<<"bfloat1: " << bfloat1.binary2float() << endl;
   //cout<<"bfloat2: " << bfloat2.binary2float() << endl;
   cout<<"bfloat3: " << bfloat3.binary2float() << endl;
   cout<<"bfloat4: " << bfloat4.binary2float() << endl;
   cout<<bfloat3.binary2float() << " + " << bfloat4.binary2float() << " = " << bfloat9.binary2float() << endl;
   // cout<<bfloat1.binary2float() << " - " << bfloat2.binary2float()<< " = " << bfloat6.binary2float() << endl;
   //cout<<bfloat2.binary3float() << " - " << bfloat2.binary2float()<< " = " << bfloat9.binary2float() << endl;
   //cout<<bfloat5.binary2float() << " - " << bfloat4.binary2float()<< " = " << bfloat10.binary2float() << endl;
   //cout<<bfloat6.binary2float() << " * " << bfloat7.binary2float()<< " = " << bfloat11.binary2float() << endl;
   // cout<<bfloat4.binary2float() << " / " << bfloat5.binary2float()<< " = " << bfloat10.binary2float() << endl;
   // cout<<bfloat2.binary2float() << " / " << bfloat4.binary2float()<< " = " << bfloat11.binary2float() << endl; 
   // cout << "---------------BFloat16 Comparison-------------- "<< endl;
   // cout<<bfloat1.binary2float() << " == " << bfloat4.binary2float()<<" : " << equal << endl;  
   // cout<<bfloat1.binary2float() << " < " << bfloat2.binary2float()<<" : " << compare << endl;
   // cout<<bfloat4.binary2float() << " < " << bfloat2.binary2float()<<" : " << compare3 << endl;
   // cout<<bfloat3.binary2float() << " > " << bfloat4.binary2float()<<" : " << compare2 << endl;
   return 0;
}