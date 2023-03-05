 /****************************************************************
 * Anya Rajan, arajan2
 * Spring 2022 CSE 101 PA5
 * List.cpp
 * List.cpp contains the definitions of List ADTs
 * ***************************************************************/
#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

using namespace std;

int main(){
   List A;
   A.moveFront();

   for (int i = 1; i < 15; i++) {
	A.insertAfter(i);
        A.moveNext();
   } 
  
  cout << A << endl;

  cout << A.length() << endl;
  cout << A.front() << endl;
  cout << A.back() << endl;
  A.movePrev();
  cout << A.position() << endl;

  cout << A.peekNext() << endl;
  cout << A.peekPrev() << endl;

  A.moveBack();
  cout << A.peekPrev() << endl;

  A.movePrev();
  cout << A.peekPrev() << endl;

  A.movePrev();
  A.insertBefore(100);
  cout << A << endl;

  A.movePrev();
  A.setAfter(88);
  A.setBefore(99); 

  cout << A << endl;

  A.eraseAfter();
  A.eraseBefore();

  cout << A << endl;
  
  cout << A.findNext(13) << endl;
  cout << A.findPrev(4) << endl; 

  List B;
  B.moveFront();
  B.insertAfter(100);
  B.moveNext();
  B.insertAfter(101);
  B.moveNext();
  B.insertAfter(102);
  B.moveNext();

  A.concat(B);

  List C = A;

  cout << A.equals(C) << endl;
  cout << (A == C) << endl;

  A.movePrev();
  A.movePrev();

  A.insertBefore(5);
  A.insertAfter(4);

  cout << A << endl;

  A.cleanup();

  cout << A << endl;
  A.clear();
  cout << A << endl;

   
   return( EXIT_SUCCESS );
}
