#include<iostream>
#include<string>
#include<stdexcept>
#include"BigInteger.h"

using namespace std;

int main(){

   string s1 = "912873999999900000345619187236478";
   string s3 = "5439856734856794583654365346534";

   //BigInteger N;
   BigInteger A = BigInteger(s1);
   BigInteger B = BigInteger(s3);

   //cout << endl;

   cout << "A = " << A << endl;
   cout << "B = " << B << endl;
   //cout << endl;

   return EXIT_SUCCESS;
}

