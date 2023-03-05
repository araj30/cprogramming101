/*****************************************************************
 * Anya Rajan, arajan2
 * Spring 2022 CSE 101 PA5
 * List.cpp
 * List.cpp contains the definitions of List ADTs
 * ***************************************************************/

#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

// Node constructor
List::Node::Node(ListElement x) {
	data = x;
	next = nullptr;
	prev = nullptr;
}

// Class Constructors & Destructors ----------------------------------------

// Creates new List in the empty state.
List::List() {
	frontDummy = new Node(-4);
	backDummy = new Node(-5);

	frontDummy->next = backDummy;
	backDummy->prev = frontDummy;

	beforeCursor = frontDummy;
	afterCursor = backDummy;

	pos_cursor = 0;
	num_elements = 0;
}

// Copy constructor.
List::List(const List& L) {
	// make this an empty list
	frontDummy = new Node(-4);
        backDummy = new Node(-5);

	frontDummy->next = backDummy;
	backDummy->prev = frontDummy;

        beforeCursor = frontDummy;
        afterCursor = backDummy;

        pos_cursor = 0;
        num_elements = 0;

	Node* N = L.frontDummy->next;
	while (N != L.backDummy) {
		this->insertAfter(N->data);
		moveNext();
		N = N->next;
	}

}

// Destructor
List::~List() {
	// do we need a while loop h
	clear();

	delete frontDummy;
	delete backDummy;
}

// Access functions --------------------------------------------------------

   // length()
   // Returns the length of this List.
   int List::length() const {
	return(num_elements);
   }

   // front()
   // Returns the front element in this List.
   // pre: length()>0
   ListElement List::front() const {
	if( num_elements==0 ){
      		throw std::length_error("List: front(): empty List");
   	}
	
	return(frontDummy->next->data);
   }

   // back()
   // Returns the back element in this List.
   // pre: length()>0
   ListElement List::back() const {
	if( num_elements==0 ){
     		 throw std::length_error("List: back(): empty List");
   	}

	return(backDummy->prev->data);
   }

   // position()
   // Returns the position of cursor in this List: 0 <= position() <= length().
   int List::position() const {
	// NEED TO GO OVER!!	
	if ( pos_cursor < 0 ) {
		throw std::length_error("List: position(): position is less than 0");			
	}
	
	if ( pos_cursor > length()) {
		throw std::length_error("List: position(): position is greater than length()");
	} 

	return(pos_cursor);
   }

   // peekNext()
   // Returns the element after the cursor.
   // pre: position()<length()
   ListElement List::peekNext() const {
	if ( position()>=length() ) {
		throw std::length_error("List: peekNext(): position() is greater than length()");
	}

	return(afterCursor->data);

   }

   // peekPrev()
   // Returns the element before the cursor.
   // pre: position()>0
   ListElement List::peekPrev() const {
	if ( position()<=0 ) {
		throw std::length_error("List: peekPrev(): position is less than 0");
	}

	return(beforeCursor->data);
   }

   // Manipulation procedures -------------------------------------------------

   // clear()
   // Deletes all elements in this List, setting it to the empty state.
   void List::clear() {
	moveFront();
	while (length() != 0) {
		eraseAfter();		
	}	
   }

   // moveFront()
   // Moves cursor to position 0 in this List.
   void List::moveFront() {
	if ( length()==0 ) {
		pos_cursor = 0;
		beforeCursor = frontDummy;
		afterCursor = backDummy;
		return;
	}

	pos_cursor = 0;
	beforeCursor = frontDummy;
	afterCursor = frontDummy->next;	
   }

   // moveBack()
   // Moves cursor to position length() in this List.
   void List::moveBack() {
	if ( length()==0 ) {
                pos_cursor = 0;
                beforeCursor = frontDummy;
                afterCursor = backDummy;
		return;
        }

	pos_cursor = length();
	beforeCursor = backDummy->prev;
	afterCursor = backDummy;
   }

   // moveNext()
   // Advances cursor to next higher position. Returns the List element that
   // was passed over. 
   // pre: position()<length() 
   ListElement List::moveNext() {
	if ( position()>=length() ) {
                throw std::length_error("List: moveNext(): position() is greater than length()");
        }

	pos_cursor = position() + 1;
	beforeCursor = afterCursor;
	afterCursor = afterCursor->next;
	
	return(beforeCursor->data);

   }

   // movePrev()
   // Advances cursor to next lower position. Returns the List element that
   // was passed over. 
   // pre: position()>0
   ListElement List::movePrev() {
   	if ( position()<=0 ) {
                throw std::length_error("List: movePrev(): position is less than 0");
        }
	
	pos_cursor = position() - 1;
	afterCursor = afterCursor->prev;
	beforeCursor = beforeCursor->prev;

	return(afterCursor->data);
   }

   // insertAfter()
   // Inserts x after cursor.
   void List::insertAfter(ListElement x) {
	
	//if ( length()==0 ) {
	//	afterCursor = backDummy;
	//	beforeCursor = frontDummy;
	//}
	
	Node* N = new Node(x);
	
	N->prev = beforeCursor;
	N->next = afterCursor;

	beforeCursor->next = N;
	afterCursor->prev = N;

	afterCursor = N;

	num_elements = length() + 1;
			
   }

   // insertBefore()
   // Inserts x before cursor.
   void List::insertBefore(ListElement x) {
	
	//if ( length()==0 ) {
        //        afterCursor = backDummy;
        //        beforeCursor = frontDummy;
        //}
	
	Node* N = new Node(x);

        N->prev = beforeCursor;
        N->next = afterCursor;

        beforeCursor->next = N;
        afterCursor->prev = N;

	beforeCursor = N;

        num_elements = length() + 1;
	pos_cursor = position() + 1;
   }

   // setAfter()
   // Overwrites the List element after the cursor with x.
   // pre: position()<length()
   void List::setAfter(ListElement x) {
	if ( position()>=length() ) {
                throw std::length_error("List: setAfter(): position() is greater than length()");
        }	

	afterCursor->data = x;
   }

   // setBefore()
   // Overwrites the List element before the cursor with x.
   // pre: position()>0
   void List::setBefore(ListElement x) {
	if ( position()<=0 ) {
                throw std::length_error("List: setBefore(): position is less than 0");
        }

	beforeCursor->data = x;
   }

   // eraseAfter()
   // Deletes element after cursor.
   // pre: position()<length()
   void List::eraseAfter() {
	if ( pos_cursor >= length())  {
                throw std::length_error("List: eraseAfter(): position() is greater than length()");
        }

	//if ( length()== 1) {
	//	delete afterCursor;
	//	return;
	//}
	
	Node* N = afterCursor;
	afterCursor = afterCursor->next;

	afterCursor->prev = beforeCursor;
	beforeCursor->next = afterCursor;

	// Node* N = afterCursor;
	
	delete N;

	// afterCursor = beforeCursor->next;
	num_elements = length() - 1;
	// afterCursor = beforeCursor->next;
	
   }

   // eraseBefore()
   // Deletes element before cursor.
   // pre: position()>0
   void List::eraseBefore() {
	if ( pos_cursor<=0 ) {
                throw std::length_error("List: eraseBefore(): position is less than 0");
        }
	
	//if ( length()==1 ) {
	//	delete beforeCursor;
	//	return;
	//}

	Node* N = beforeCursor;
	beforeCursor = beforeCursor->prev;

	beforeCursor->next = afterCursor;
	afterCursor->prev = beforeCursor;
	
	// Node* N = beforeCursor;

	delete N;

	//beforeCursor = afterCursor->prev;	
	num_elements = num_elements - 1;
	pos_cursor = pos_cursor - 1;	
	// beforeCursor = afterCursor->prev;
   }

   // Other Functions ---------------------------------------------------------

   // findNext()
   // Starting from the current cursor position, performs a linear search (in 
   // the direction front-to-back) for the first occurrence of element x. If x
   // is found, places the cursor immediately after the found element, then 
   // returns the final cursor position. If x is not found, places the cursor 
   // at position length(), and returns -1. 
   int List::findNext(ListElement x) {
	Node* N = afterCursor;

	while (N != backDummy) {
		if (N->data == x) {
			moveNext();
			// pos_cursor += 1;
			return pos_cursor;
		}
		moveNext();
		// pos_cursor += 1;
		N = N->next;
	}
	
	moveBack();
	return(-1);				
   }

   // findPrev()
   // Starting from the current cursor position, performs a linear search (in 
   // the direction back-to-front) for the first occurrence of element x. If x
   // is found, places the cursor immediately before the found element, then
   // returns the final cursor position. If x is not found, places the cursor 
   // at position 0, and returns -1. 
   int List::findPrev(ListElement x) {
	Node* N = beforeCursor;

	while (N != frontDummy) {
		if (N->data == x) {
			movePrev();
			//pos_cursor -= 1;
			return pos_cursor;
		}
		movePrev();
		//pos_cursor -= 1;
		N = N->prev;
	}

	moveFront();
	return(-1);
   }

   // cleanup()
   // Removes any repeated elements in this List, leaving only unique elements.
   // The order of the remaining elements is obtained by retaining the frontmost 
   // occurrance of each element, and removing all other occurances. The cursor 
   // is not moved with respect to the retained elements, i.e. it lies between 
   // the same two retained elements that it did before cleanup() was called.
   void List::cleanup() {
	Node* N = frontDummy->next;
	Node* s = nullptr;
	int outer = 0;
	int inner = 0;
	// two counters, one for first while loop and one for inner
	// start outer one at zero
	// start innner one at outer + 1
	// for before cursor, if the counter is less than the actual cursor, decrease the inner	
	// compare the first pointer with the one that
	// if s->data is equal to N->data
	// if s is beforecursor, then relink ur stuff and then delete it
	// if s is aftercursor, relink ur stuff and then delete
	while (N != backDummy) {
		s = N->next;
		// inner = outer + 1;
		while (s != backDummy) {
			inner = outer + 1;
			if (N->data == s->data) {
				if (s == beforeCursor) {
					beforeCursor = s->prev;
				}

				else if (s == afterCursor) {
					afterCursor = s->next;
				}

				if (inner < pos_cursor) {
                                         pos_cursor = pos_cursor - 1;
                                }

				s->next->prev = s->prev;
                                s->prev->next = s->next;
				
				Node* temp = s;
				delete temp;
				num_elements = num_elements - 1;
				
			}
			s = s->next;
			inner += 1;
		}
		outer += 1;
		N = N->next;
		//s = N->next;
	}

   }
 
   // concat()
   // Returns a new List consisting of the elements of this List, followed by
   // the elements of L. The cursor in the returned List will be at postion 0.
   List List::concat(const List& L) const {
	// pseudo from pat tantalo 
	List C;
	Node* N = this->frontDummy->next;
	Node* M = L.frontDummy->next;
	while (N != this->backDummy) {
		C.insertBefore(N->data);
		N = N->next;
	}

	while (M != L.backDummy) {
		C.insertBefore(M->data);
		M = M->next;
	}

	C.moveFront();
	return C;
   }
   // to_string()
   // Returns a string representation of this List consisting of a comma 
   // separated sequence of elements, surrounded by parentheses.
   std::string List::to_string() const {
	// pseudo from pat tantalo
	Node* N = frontDummy->next;
	std::string s = "(";

	while (N != backDummy) {
		if (N == backDummy->prev) {
			s += std::to_string(N->data);
			break;
		}
		s += std::to_string(N->data) + ", ";
		N = N->next;
	}

	return s + ")";
   }

   // equals()
   // Returns true if and only if this List is the same integer sequence as R.
   // The cursors in this List and in R are unchanged.
   bool List::equals(const List& R) const {
	// pseudo from pat tantalo
	//
	// printf("omg hey\n");
	bool eq = false;
	Node* N = nullptr;
	Node* M = nullptr;

	eq = (this->num_elements == R.num_elements);
	N = this->frontDummy;
	M = R.frontDummy;

	while (eq && N != backDummy) {
		eq = (N->data == M->data);
		N = N->next;
		M = M->next;
	}

	return eq;
   }	

   std::ostream& operator<<( std::ostream& stream, const List& L ) {
	// pseudo from pat tantalo
	return stream << L.List::to_string();
   }

   // operator==()
   // Returns true if and only if A is the same integer sequence as B. The 
   // cursors in both Lists are unchanged.
   bool operator==( const List& A, const List& B ) {
	// pseudo from pat tantalo
	return A.List::equals(B);
   }

   // operator=()
   // Overwrites the state of this List with state of L.
   List& List::operator=( const List& L ) {
      // pseudo/code from pat tantalo
      if( this != &L ){ // not self assignment
      // make a copy of L
      List temp = L;

      // then swap the copy's fields with fields of this
      std::swap(frontDummy, temp.frontDummy);
      std::swap(backDummy, temp.backDummy);
      std::swap(num_elements, temp.num_elements);
      std::swap(pos_cursor, temp.pos_cursor);
      std::swap(beforeCursor, temp.beforeCursor);
      std::swap(afterCursor, temp.afterCursor);
   }

   // return this with the new data installed
   return *this;

   // the copy, if there is one, is deleted upon return	
   }

