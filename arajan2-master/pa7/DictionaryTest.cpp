 /*************************************************************************
 * Anya Rajan, arajan2
 * 2022 Spring CSE101 PA7
 * DictionaryTest.cpp
 * DictionaryTest.cpp is the test client for the Dictionary ADT
 * *************************************************************************/

#include<iostream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"
using namespace std;

int main(){
	Dictionary D;
	
	string s[] = {"hello", "goodbye", "afternoon", "lovely"};

	
	for (int i=0; i<3; i++){
      		D.setValue(s[i], i+1);
   	}

	cout << "Tree A" << endl;
	cout << D.to_string() << endl;

	Dictionary B = D;

	cout << "Tree Size D and B" << endl;
	cout << "A.size() = " << D.size() << endl  << D << endl;
   	cout << "B.size() = " << B.size() << endl  << B << endl;

	B.setValue("foo", 2);

	cout << "D==B is " << (D==B?"true":"false") << endl;

	cout << D.getValue("goodbye") << endl;
	D.remove("hello");

	cout << "Tree D" << endl;
	cout << D.to_string() << endl;

	D.end();
	B.begin();

	cout << "D Current Info" << endl;
	cout << D.hasCurrent() << endl;
	cout << D.currentKey() << endl;
	cout << D.currentVal() << endl;
	
	D.prev();
	B.next();

	cout << "B Current info" << endl;
	cout << B.hasCurrent() << endl;
        cout << B.currentKey() << endl;
        cout << B.currentVal() << endl;

	cout << "Contains for B" << endl;
	cout << B.contains("lovely") << endl;

	cout << "Tree B" << endl;
	cout << B.pre_string() << endl;

	D.clear();
	cout << "Final D" << endl;
	cout << D.to_string() << endl;
}
