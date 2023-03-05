 /***************************************************************
 * Anya Rajan, arajan2
 * Spring 2022 CSE 101 PA5
 * List.cpp
 * List.cpp contains the definitions of List ADTs
 * ***************************************************************/

#include<iostream>
#include<fstream>
#include<string>
#include<stdlib.h>
#include<iomanip>
#include "List.h"

using namespace std;

void shuffle(List &D) {
	if (D.length() == 1) {
		return;
	}

	int split;
	split = D.length()/2;
	List A;
	A.moveFront();

	D.moveFront();
	for (int i = 0; i < split; i++) {
		D.moveNext();
	}
	
	// help from TA Sheel	
	while(D.position() > 0) {
		A.insertAfter(D.peekPrev());
		D.eraseBefore();
	}

	// cout << D << endl;
	// cout << A << endl;

	// help from TA Sheel
	A.moveFront();
	D.moveFront();
	while (A.position() < A.length()) {
		D.moveNext();
		D.insertBefore(A.peekNext());
		A.moveNext();
		// D.moveNext();
	}

	// D = A;
	// cout << D.length() << endl;
} 

int main(int argc, char * argv[]){

   // check command line for correct number of arguments
   if( argc != 2 ){
      cerr << "Usage: " << argv[0] << argv[1] << " program file and integer" << endl;
      return(EXIT_FAILURE);
   }

   int counter;
   
   List L;
   L.moveFront();
   cout << "deck size" << setw(20) << "shuffle count" << endl;
   cout << "------------------------------" << endl;

   for (int i = 1; i <= atoi(argv[1]); i++) {
	counter = 0;
	L.insertAfter(i);
	List C = L;
	shuffle(C); 
	counter += 1;
	while ((L.equals(C)) == 0) {
		shuffle(C);
		counter += 1;
	}

	cout << i << setw(20) << counter << endl;
	L.moveNext();
   }

   return(EXIT_SUCCESS);
}


