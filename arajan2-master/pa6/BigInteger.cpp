/*****************************************************************
 * Anya Rajan, arajan2
 * Spring 2022 CSE 101 PA6
 * BigInteger.cpp
 * BigInteger.cpp contains the definitions of BigInteger ADTs
 * ***************************************************************/

#include<iostream>
#include<string>
#include<stdexcept>
#include<iomanip>
#include<utility>
#include"List.h"
#include"BigInteger.h"
#define POWER  9
#define BASE 1000000000

// BigInteger()
// Constructor that creates a new BigInteger in the zero state: 
// signum=0, digits=().
BigInteger::BigInteger() {
	int signum = 0; // +1 (positive), -1 (negative), 0 (zero)
	List digits;	// List of digits in this BigInteger
}

// BigInteger()
// Constructor that creates a new BigInteger from the string s.
// Pre: s is a non-empty string consisting of (at least one) base 10 digit
// {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
BigInteger::BigInteger(std::string s) {
	// split the string based on p
	// we know the size of the list (length function) and p
	// we split in to substrings?
	// feed substrings 
	// convert string to long with stol
	// if string to long fails at some point, catch exception and
	// throw our own exception
	int count = s.length();

	if (s[0] == '+') {
		signum = 1;
		s.erase(0, 1);
		count--;
	}

	else if (s[0] == '-') {
		signum = -1;
		s.erase(0, 1);
		count--;
	}

	else {
		signum = 1;
	}

	// eliminates leading zeros
	// while loop that checks if s[0] is 0 and length/count is > 1
	// keep erasing (s.erase and count)
	// if all that's left is a zero, then set signum to 0 && length > 0
	while (s[0] == '0' && count > 1) {
		s.erase(0, 1);
		count--;
	}

	if (s[0] == '0' && count > 0) {
		signum = 0;
	}

	// check if the length is 0 or if the string contains non-numeric character
	// ... throw error 
	if (count == 0) {
		throw std::length_error("BigInteger: Constructor: empty string");
	}
		
	for (int i = 0; i < count; i++) {
		if (isdigit(s[i]) == 0) {
			throw std::logic_error("BigInteger: Constructor: non-numeric string");
		}
	}

	// digits = List();
	ListElement L;
	if (s[0] != '0') {
		for (int j = s.length()-POWER-1; j >= 0; j -= POWER) {
			L = std::stol(s.substr(j, j+POWER));
			digits.insertBefore(L);
			std::cout << L << std::endl;
		}

		// if length%power > 0
		// 0, remainder
		// same two lines
		int rem = count%POWER;
		//std::cout << "hello" << rem << std::endl;

		if (rem > 0) {
			L = std::stol(s.substr(0, rem));
                        digits.insertBefore(L);
		}

	}

	// return B;
		
}
 
// BigInteger()
// Constructor that creates a copy of N.
BigInteger::BigInteger(const BigInteger& N) {
	BigInteger C;
	C.signum = N.signum;
	C.digits = N.digits;
}

// Access Functions -------------------------------------------------------------

// sign()
// Returns -1, 1 or 0 according to whether this BigInteger is positive, 
// negative or 0, respectively.
int BigInteger::sign() const {
	return signum;
}

// compare()
// Returns -1, 1 or 0 according to whether this BigInteger is less than N,
// greater than N or equal to N, respectively.
int BigInteger::compare(const BigInteger& N) const {
	// would we need to ever compare with 0? it's just reserved for 0
	// BigInteger B = this;
	BigInteger L = N;
	BigInteger B = *this;

	if (B.signum == -1 && (L.signum == 1 || L.signum == 0)) {
		return -1;
	}
	else if ((B.signum == 1 || B.signum == 0) && L.signum == -1) {
		return 1;
	}
	else if ((B.digits == L.digits) == 1) {
		return 0;
	}


	// compare the two sizes
	B.digits.moveFront();
	L.digits.moveFront();

	int counter_zero = 0;
	int counter_one = 0;

	while (B.digits.position() != B.digits.length() || L.digits.position() != L.digits.length()) {
		if (B.digits.position() != B.digits.length()) {
			B.digits.moveNext();
			counter_zero += 1;
		}
		if (L.digits.position() != L.digits.length()) {
			L.digits.moveNext();
			counter_one += 1;
		}
	}	

	if (counter_zero > counter_one) {
		return 1;	
	}
	else if (counter_zero < counter_one) {
		return -1;
	}
	else {
		// the two must be the same length so we
		// need to compare each element
		B.digits.moveFront();
        	L.digits.moveFront();

		if (B.digits.peekNext() > L.digits.peekNext()) {
			return 1;
		}
		if (B.digits.peekNext() < L.digits.peekNext()) {
			return -1;
		}

		while (B.digits.position() != B.digits.length()) {
			if (B.digits.peekNext() > L.digits.peekNext()) {
				return 1;
			}
			if (B.digits.peekNext() < L.digits.peekNext()) {
				return -1;
			}
			B.digits.moveNext();
			L.digits.moveNext();
		}	
	}

	return 0;
}

// Manipulation procedures -------------------------------------------------

// makeZero()
// Re-sets this BigInteger to the zero state.
void BigInteger::makeZero() {
	signum = 0;
	digits.clear();	
}

// negate()
// If this BigInteger is zero, does nothing, otherwise reverses the sign of
// this BigInteger positive <--> negative. 
void BigInteger::negate() {
	if (signum == 0) {
		return;
	}
	
	signum = signum * -1;	
}

// BigInteger Arithmetic operations ----------------------------------------

// shiftList()
// Prepends p zero digits to L, multiplying L by base^p. Used by mult().
//void shiftList(List& L, int p) {

//}

// scalarMultList()
// Multiplies L (considered as a vector) by m. Used by mult().
//void scalarMultList(List& L, ListElement m) {
	
//}

// normalizeList()
// normalizes a list
/*List normalizeList(List& L) {
	if (L.position() == 0) {
		L.moveFront();
	}
		
		long temp = L.peekNext();
		long hold = L.peekNext();
		int count = 0;
		// how to count digits algorithm found on:
		// https://studyfied.com/program/cpp-basic/count-number-of-digits-in-a-given-integer/
		while (temp != 0) {
			count += 1;
			temp /= 10;
		}
		if (count > POWER) {
			long h = hold - BASE;
			L.setAfter(h);
			L.moveNext();
			long put = L.peekNext() + 1;
			L.insertAfter(put);
		}

		else if (hold < 0) {
			if (L.position() == L.length()) {
				return L;						
			}
			long b = hold + BASE;
			L.setAfter(b);
			L.moveNext();
			long m = L.peekNext() - 1;
			L.insertAfter(m);
		}

		if (L.position() == L.length()) {
			return L;
		}

		// L.moveNext();
		L.normalizeList();
} */

// add()
// Returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger& N) const {
	BigInteger C = N;
	BigInteger J = *this;
	if (J.compare(C) == 1 && J.signum == -1 && C.signum != 0) {
		BigInteger K;
		if (C.signum == 1) {
			J.negate();
			K = sub(N);
			K.negate();
			return K;
		} 
		else {
			J.negate();
			C.negate();
			K = add(N);
			K.negate();
			return K;
		}
	}

	else {
		BigInteger B;
		long k = 0;
		B.digits.moveFront();
		J.digits.moveFront();
		C.digits.moveFront();
		//Node* E = B->digits->frontDummy->next;
		//Node* P = frontDummy->next;
		//Node* L = N.digits->frontDummy->next;

		while (J.digits.position() != J.digits.length() || C.digits.position() != C.digits.length()) {
                	if (J.digits.position() != J.digits.length()) {
				k += J.digits.peekNext();
                        	J.digits.moveNext();
                	}

                	if (C.digits.position() != C.digits.position()) {
				k += C.digits.peekNext();
                        	C.digits.moveNext();
                	}
			
			B.digits.insertAfter(k);
			B.digits.moveNext();
        	}

		B.digits.moveFront();
		long temp;
		long hold;
		int count;

		while (B.digits.position() != B.digits.length()) {
			temp = B.digits.peekNext();
			hold = B.digits.peekNext();
			count = 0;

			while (temp != 0) {
				count += 1;
				temp /= 10;		
			}

			if (count > POWER) {
				long h = hold - BASE;
				B.digits.setAfter(h);
				B.digits.moveNext();
				long put = B.digits.peekNext() + 1;
				B.digits.setAfter(put);
			}

			else if (hold < 0) {
				long b = hold + BASE;
				B.digits.setAfter(b);
				B.digits.moveNext();
				long m = B.digits.peekNext() - 1;
				B.digits.setAfter(m);
			}
		}

		if (B.digits.back() > 0) {
			B.signum = 1;
		}	
		else if (B.digits.back() < 0) {
			long num = B.digits.back() * -1;
			B.digits.moveBack();
			B.digits.setBefore(num);
			B.signum = -1;
		}

		return B;
	} 
}

// sub()
// Returns a BigInteger representing the difference of this and N.
BigInteger BigInteger::sub(const BigInteger& N) const {
	BigInteger U = *this;
	BigInteger P = N;
	if (U.compare(P) == 1 && U.signum == 1 && P.signum == 1) {
		BigInteger V;
		V = P.sub(U);
		V.negate();
		return V;
	}

	if (P.signum == -1) {
		P.negate();
		BigInteger H;
		H = add(P);
		return H;
	}	

		BigInteger B;
		long subtract;
		B.digits.moveFront();
		U.digits.moveFront();
		P.digits.moveFront();
                //Node* E = B->digits->frontummy->next;
                // Node* P = frontDummy->next;
                // Node* L = N.digits->frontDummy->next;

                while (U.digits.position() != U.digits.length() || P.digits.position() != P.digits.length()) {
                        if (U.digits.position() != U.digits.length()) {
                                subtract += U.digits.peekNext();
                                U.digits.moveNext();
                        }

                        if (P.digits.position() != P.digits.length()) {
                                subtract -= P.digits.peekNext();
                                P.digits.moveNext();
                        }
			
			B.digits.insertAfter(subtract);
                        B.digits.moveNext();
                }
		
		B.digits.moveFront();
                long temp;
                long hold;
                int count;		
		while (B.digits.position() != B.digits.length()) {
                        temp = B.digits.peekNext();
                        hold = B.digits.peekNext();
                        count = 0;

                        while (temp != 0) {
                                count += 1;
                                temp /= 10;
                        }

                        if (count > POWER) {
                                long h = hold - BASE;
                                B.digits.setAfter(h);
                                B.digits.moveNext();
                                long put = B.digits.peekNext() + 1;
                                B.digits.setAfter(put);
                        }

                        else if (hold < 0) {
                                long b = hold + BASE;
                                B.digits.setAfter(b);
                                B.digits.moveNext();
                                long m = B.digits.peekNext() - 1;
                                B.digits.setAfter(m);
                        }
                }

                if (B.digits.back() > 0) {
                        B.signum = 1;
                }
                else if (B.digits.back() < 0) {
			long put = B.digits.back() * -1;
			B.digits.moveBack();
			B.digits.setBefore(put);
			B.signum = -1;
                }

                return B;
}

// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this BigInteger consisting of its
// base 10 digits. If this BigInteger is negative, the returned string
// will begin with a negative sign '-'. If this BigInteger is zero, the
// returned string will consist of the character '0' only.
std::string BigInteger::to_string() {
	std::string s = "";
	if (signum == 0) {
		s += "0";
		return s;
	}

	else if (signum == -1) {
		s += "-";
	}

	digits.moveBack();
	while (digits.position() != 0) {
		s += std::to_string(digits.peekPrev());
		digits.movePrev();
	}

	return s;

}

// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of N into stream.
std::ostream& operator<<( std::ostream& stream, BigInteger N ) {
	return stream << N.BigInteger::to_string();
} 

