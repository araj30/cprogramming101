/*************************************************************************
 * Anya Rajan, arajan2
 * 2022 Spring CSE101 PA7
 * Dictionary.cpp
 * Dictionary.cpp is the function definitions for the Dictionary ADT
 * *************************************************************************/

#include<iostream>
#include<string>
#include<stdexcept>
#include "Dictionary.h"

// Private Constructor --------------------------------------------------------

// Node Constructor

Dictionary::Node::Node (keyType k, valType v) {
	key = k;
	val = v;
	parent = nullptr;
	left = nullptr;
	right = nullptr;
}

// Class Constructors & Destructors ----------------------------------------

// Creates Dictionary in the empty state
Dictionary::Dictionary() {
	nil = new Node("", -1);
	root = nil;
	current = nil;
	num_pairs = 0;
}

// Copy constructor.
Dictionary::Dictionary(const Dictionary& D) {
	root = new Node("", -1);
	nil = root;
	current = nil;
	num_pairs = 0;

	preOrderCopy(D.root, D.nil);
}

// Destructor
Dictionary::~Dictionary() {
	clear();

	postOrderDelete(root);

	delete nil;
	//delete root;
	//delete current;
}

// Helper Functions (Optional) ---------------------------------------------

// transplant()
void Dictionary::transplant(Node* U, Node* V) {
	// pseudo from tantalo
	if (U->parent == nil) {
		root = V;
	}
	else if (U == U->parent->left) {
		U->parent->left = V;
	}
	else {
		U->parent->right = V;
	}
	if (V != nil) {
		V->parent = U->parent;
	}
}

// search()
// Searches the subtree rooted at R for a Node with key==k. Returns
// the address of the Node if it exists, returns nil otherwise.
// why does this need to be a pointer?
Dictionary::Node* Dictionary::search(Node *R, keyType k) const {
        // pseudo from tantalo
	if (R == nil) {
                return nil;
        }
	else if (k == R->key) {
		return R;
	}
        else if (k < R->key) {
                return search(R->left, k);
        }
        else {
                return search(R->right, k);
        }
}

// findMin()
// If the subtree rooted at R is not empty, returns a pointer to the
// leftmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMin(Node* R) {
	// pseudo from tantalo
	if (R == nil) {
		return nil;
	}

	while (R->left != nil) {
		R = R->left;		
	}
	
	return R;
}

// findMax()
// If the subtree rooted at R is not empty, returns a pointer to the
// rightmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMax(Node* R) {
	//Node *N = R;
	// pseudo from tantalo
        if (R == nil) {
                return nil;
        }

        while (R->right != nil) {
                R = R->right;
        }

        return R;
}

// findNext()
Dictionary::Node* Dictionary::findNext(Node* N) {
	/*if (N == nil) {
		return nil;
	}*/
	// pseudo from tantalo
        if (N->right != nil) {
                return findMin(N->right);
        }

        Node* Y = N->parent;
        while (Y != nil && N == Y->right) {
                N = Y;
                Y = Y->parent;
        }	

	return Y;
}

// findPrev()
Dictionary::Node* Dictionary::findPrev(Node* N) {
	/*if (N == nil) {
		return nil;
	}*/
	// pseudo from tantalo
	if (N->left != nil) {
		return findMax(N->left);
	}

	Node* Y = N->parent;
        while (Y != nil && N == Y->left) {
                N = Y;
                Y = Y->parent;
        }

        return Y;
}

// postOrderDelete
// Deletes all Nodes in the subtree rooted at R, sets R to nil.
void Dictionary::postOrderDelete(Node* R) {
	// pseudo from tantalo
	if (R != nil) {
		postOrderDelete(R->left);
		postOrderDelete(R->right);
		if (R->parent->left == R) {
			R->left = nil;
		}
		if (R->parent->right == R) {
			R->right = nil;
		}
		delete R;
		num_pairs -= 1;
	}
	else {
		return;
	}
}

// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this 
// Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Node* R, Node* N) {
	// pseudo from tantalo
	if (R != N) {
		setValue(R->key, R->val);
		preOrderCopy(R->left, N);
		preOrderCopy(R->right, N);
	}	
}

// inOrderString()
// Appends a string representation of the tree rooted at R to string s. The
// string appended consists of: "key : value \n" for each key-value pair in
// tree R, arranged in order by keys.
void Dictionary::inOrderString(std::string& s, Node* R) const {
	// pseudo from tantalo
	if (R != nil) {
		inOrderString(s, R->left);
		s += R->key; 
		s += " : "; 
		s += std::to_string(R->val);
		s += "\n";
		inOrderString(s, R->right);
		
	}
}

// preOrderString()
// Appends a string representation of the tree rooted at R to s. The appended
// string consists of keys only, separated by "\n", with the order determined
// by a pre-order tree walk.
void Dictionary::preOrderString(std::string& s, Node* R) const {
	// pseudo from tantalo
	if (R != nil) {
		s += R->key;
		s += "\n";
		preOrderString(s, R->left);
		preOrderString(s, R->right);
	}
}

// transplant()
/*void Dictionary::transplant(Node* U, Node* V) {
	if (U->parent == nil) {
		root = V;
	}
	else if (U == U->parent->left) {
		U->parent->left = V;
	}
	else {
		U->parent->right = V;
	}	

	if (V != nil) {
		V->parent = U->parent;
	}
} */

// Access functions --------------------------------------------------------

// size()
// Returns the size of this Dictionary.
int Dictionary::size() const {
	//Dictionary D = *this;

	return num_pairs;
}

// contains()
// Returns true if there exists a pair such that key==k, and returns false
// otherwise.
bool Dictionary::contains(keyType k) const {
	// Dictionary G = *this;
	if (search(root, k) != nil) {
		return true;
	}
	else {
		return false;
	}
}

// getValue()
// Returns a reference to the value corresponding to key k.
// Pre: contains(k)
valType& Dictionary::getValue(keyType k) const {
	// Dictionary H = *this;
	if (contains(k) == false) {
		throw std::logic_error("Dictionary: Dictionary doesn't contain k-- get value");
	}	
	else {
		Node* N = search(root, k);
		return N->val;
	}
}

// hasCurrent()
// Returns true if the current iterator is defined, and returns false 
// otherwise.
bool Dictionary::hasCurrent() const {
	// Dictionary B = *this;
	
	if (current != nil && current != nullptr) {
		return true;
	}
	else {
		return false;
	}
}

// currentKey()
// Returns the current key.
// Pre: hasCurrent() 
keyType Dictionary::currentKey() const {
	//Dictionary L = *this;

	if (hasCurrent() == false) {
		throw std::logic_error("Dictionary: Dictionary has an undefined current iterator");
	}
	
	return current->key;
}

// currentVal()
// Returns a reference to the current value.
// Pre: hasCurrent()
valType& Dictionary::currentVal() const {
	//Dictionary V = *this;

	if (hasCurrent() == false) {
                throw std::logic_error("Dictionary: Dictionary has an undefined current iterator");
        }

	return current->val;
}


// Manipulation procedures -------------------------------------------------

// clear()
// Resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear() {
	postOrderDelete(root);
	root = nil;
	current = nil;
	num_pairs = 0;
	return;

	/*begin();
	while (current != nil) {
		current = nullptr;
		next();			
	}

	// loop through and set to null
	num_pairs = 0;	
	// current = nullptr;
	nil = nullptr; */	
} 

// setValue()
// If a pair with key==k exists, overwrites the corresponding value with v, 
// otherwise inserts the new pair (k, v).
void Dictionary::setValue(keyType k, valType v) {
	//std::cout << "HEY\n" << std::endl;
        /*if (search(root, k) != nil) {
		Node* M = search(root, k);
		M->val = v;
		return;
	} */
	// pseudo from tantalo
        Node *Y = nil;
	Node *X = root;
	Node *H = new Node(k, v);
	//std::cout << "YO\n" << std::endl;
	while (X != nil) {
		Y = X;
		if (k < X->key) {
			X = X->left;
		}
		else if (k > X->key) {
			X = X->right;
		}
		else {
			// break;
			X->val = H->val;
			return;
		}
	}

	//std::cout << "after while\n" << std::endl;
	H->parent = Y;
	if (Y == nil) {
		root = H; 
	}
	else if (k < Y->key) {
		Y->left = H;
	}
	else if (k > Y->key){
		Y->right = H;
	}

        //std::cout << "made it to num_pairs\n" << std::endl;
	//if (nil == nullptr) {
	//	std::cout << "NULL in SET" << std::endl;
	//}
	H->left = nil;
	H->right = nil;
	num_pairs++;
}

// remove()
// Deletes the pair for which key==k. If that pair is current, then current
// becomes undefined.
// Pre: contains(k).
void Dictionary::remove(keyType k) {
	if (contains(k) == false) {
		throw std::logic_error("Dictionary: Dictionary doesn't contain k-- remove");		
	}

	
	//std::cout << "delete output" << std::endl;
	//std::cout << to_string() << std::endl;
	// pseudo from tantalo
	Node* Y;
	Node* Z = search(root, k);
	
		/*if (Z->left == nullptr) {
			std::cout << "LEFT is NULL" << std::endl;
		}
		if (Z->right == nullptr) {
			std::cout << "RIGHT is NULL" << std::endl;
		} */
	
	if (Z == current) {
		current = nil;
		//return;
	}	

	if (Z->left == nil) {
		//std::cout << "ENTER" << std::endl;
		transplant(Z, Z->right);
		//num_pairs -= 1;
		delete Z;
		//return;
	} 	
	else if (Z->right == nil) {
		transplant(Z, Z->left);
		//num_pairs -= 1;
		delete Z;
		//return;
	} 
	else { 
		//if (Z->right == nullptr) {
		//	std::cout << "NULL" << std::endl; 
		//}
		Y = findMin(Z->right);
		if (Y->parent != Z) {
			transplant(Y, Y->right);
			Y->right = Z->right;
			Y->right->parent = Y;
		} 
		
		transplant(Z, Y);
		Y->left = Z->left;
		Y->left->parent = Y;
		//num_pairs -= 1;
		delete Z; 
	}
	//return;
	num_pairs--; 
	//std::cout << to_string() << std::endl;
	return;
}

// begin()
// If non-empty, places current iterator at the first (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing.
void Dictionary::begin() {
	if (num_pairs != 0) {
		current = findMin(root);
		//std::cout << current->key << "  " << current->val << std::endl;
	}	
}

// end()
// If non-empty, places current iterator at the last (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::end() {
	if (num_pairs != 0) {
		current = findMax(root);
	}
}

// next()
// If the current iterator is not at the last pair, advances current
// to the next pair (as defined by the order operator < on keys). If
// the current iterator is at the last pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::next() {
	if (hasCurrent() == false) {
                throw std::logic_error("Dictionary: Dictionary has an undefined current iterator");
        }

	if (current == nil) {
		throw std::logic_error("Dictionary: Current is nil");
	}

	if (current == findMax(root)) {
		current = nil;
	} 

	else {
		current = findNext(current);
	}
}

// prev()
// If the current iterator is not at the first pair, moves current to
// the previous pair (as defined by the order operator < on keys). If
// the current iterator is at the first pair, makes current undefined
// Pre: hasCurrent()
void Dictionary::prev()  {
	if (hasCurrent() == false) {
                throw std::logic_error("Dictionary: Dictionary has an undefined current iterator");
 
        }  
	
	if (current == nil) {
                throw std::logic_error("Dictionary: Current is nil");
        } 

	if (current == findMin(root)) {
                current = nil;
        }

        else {
                current = findPrev(current);
        }
}

// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this Dictionary. Consecutive (key, value)
// pairs are separated by a newline "\n" character, and the items key and value
// are separated by the sequence space-colon-space " : ". The pairs are arranged
// in order, as defined by the order operator <.
std::string Dictionary::to_string() const {
	std::string s = "";

	inOrderString(s, root);

	return s;
}

// pre_string()
// Returns a string consisting of all keys in this Dictionary. Consecutive
// keys are separated by newline "\n" characters. The key order is given
// by a pre-order tree walk.
std::string Dictionary::pre_string() const {
	std::string s = "";

	preOrderString(s, root);

	return s;
}

// equals()
// Returns true if and only if this Dictionary contains the same (key, value)
// pairs as Dictionary D.
bool Dictionary::equals(const Dictionary& D) const {
	Dictionary G = *this;

	if (G.num_pairs != D.num_pairs)  {
		return false;
	} 

	std::string g = "";
	std::string d = "";

	if (G.to_string() == D.to_string()) {
		return true;
	}
	else {
		return false;
	}
	
	/*G.begin();
	D.begin();
	while (G.current != nil) {
		if (G.current->key != D.current->key) {
			return false;
		}
		else if (G.current->val != D.current->val) {
			return false;
		}
		G.next();
		D.next();
	}

	return true;*/
}

// Overloaded Operators ----------------------------------------------------

// operator<<()
// Inserts string representation of Dictionary D into stream, as defined by
// member function to_string().
std::ostream& operator<<( std::ostream& stream, Dictionary& D ) {
	// to string or pre string??
	// pseudo from tantalo
	return stream << D.Dictionary::to_string();
}

// operator==()
// Returns true if and only if Dictionary A equals Dictionary B, as defined
// by member function equals(). 
bool operator==( const Dictionary& A, const Dictionary& B ) {
	// pseudo from tantalo
	return A.Dictionary::equals(B);
}

// operator=()
// Overwrites the state of this Dictionary with state of D, and returns a
// reference to this Dictionary.
Dictionary& Dictionary::operator=( const Dictionary& D ) {
	// pseudo from tantalo
	if (this != &D) {
		Dictionary temp = D;
		
		std::swap(num_pairs, temp.num_pairs);
		std::swap(nil, temp.nil);
		std::swap(root, temp.root);
		std::swap(current, temp.current);
				
	}

	return *this;
}
