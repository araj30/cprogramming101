/********************************************************************************* 
 * Anya Rajan, arajan2
 * 2022 Spring CSE101 PA4 
 * Matrix.c 
 * Matrix.c to define Matrix ADT functions 
 * ***********************************************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "Matrix.h"
#include "List.h"

// structs ----------------------------------------------------------------------- 

// private Entry type
typedef struct EntryObj* Entry;

// private EntryObj type 
typedef struct EntryObj {
	int column;
	double value;
} EntryObj;

// private MatrixObj type
typedef struct MatrixObj {
	int size;
	List *info;
	int nnz;	
} MatrixObj;

// Constructors-Destructors -----------------------------------------------------

// newEntry()
// returns reference to new entry
Entry newEntry(int col, double x) {
	Entry E = malloc(sizeof(EntryObj));
	E->column = col;
	E->value = x;
	return E;
}

// freeEntry()
// frees heap memory associated with an Entry
void freeEntry (Entry *pE) {
	if (pE != NULL && *pE != NULL) {
		free(*pE);
		*pE = NULL;
	}
}

// newMatrix()
// Returns a reference to a new nXn Matrix object in the zero state.
Matrix newMatrix(int n) {
	Matrix M = malloc(sizeof(MatrixObj));
	M->info = calloc(n+1, sizeof(List));
	M->size = n;
	M->nnz = 0;	
	for (int i = 1; i <= n; i++) {
		M->info[i] = newList();
	}
	return M;
}

// freeMatrix()
// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix* pM) {
	if (*pM == NULL || pM == NULL) {
                printf("Matrix Error: calling freeMatrix on NULL Matrix reference\n");
                exit(EXIT_FAILURE);
        }
	
	for (int i = 1; i <= (*pM)->size; i++) {
                freeList(&(*pM)->info[i]);
		(*pM)->info[i] = NULL;
        }

	free(*pM);
        *pM = NULL;
}

// access functions ----------------------------------------------------------------

// size()
// Return the size of square Matrix M
int size(Matrix M) {
	if (M == NULL) {
		printf("Matrix Error: calling size() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}

	return M->size;
}

// NNZ()
// Return the number of non-zero elements in M.
int NNZ(Matrix M) {
	if (M == NULL) {
                printf("Matrix Error: calling NNZ() on NULL Matrix reference\n");
                exit(EXIT_FAILURE);
        }

        return M->nnz;
}

// equals()
// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B) {
	int i;

	if (size(A) != size(B)) {
		return 0;
	}

	Entry temp_a;
	Entry temp_b;
	for (i = 1; i <= A->size; i++) {
		moveFront(A->info[i]);
		moveFront(B->info[i]);
		while (index(A->info[i]) != -1 && index(B->info[i]) != -1) {
			temp_a = get(A->info[i]);
			temp_b = get(B->info[i]);
			if (temp_a->column != temp_b->column || temp_a->value != temp_b->value) {
				return 0;
			}
			moveNext(A->info[i]);
			moveNext(B->info[i]);						
		}
	}
	return 1;
}

// Manipulation procedures ------------------------------------------------------------------

// makeZero()
// Re-sets M to the zero Matrix state.
void makeZero(Matrix M) {
	for (int i = 1; i <= size(M); i++) {
		clear(M->info[i]);			
		
	}
	M->nnz = 0;	
}

// changeEntry()
// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x) {
	if (M == NULL) {
                printf("Matrix Error: calling changeEntry() on NULL Matrix reference\n");
                exit(EXIT_FAILURE);
        }
	if (i < 1) {
		printf("Matrix Error: calling changeEntry() i less than 1\n");
                exit(EXIT_FAILURE);
	}
	if (i > size(M)) {
		printf("Matrix Error: calling changeEntry() i greater than size(M)\n");
                exit(EXIT_FAILURE);
	} 
	if (j < 1) {
                printf("Matrix Error: calling changeEntry() j less than 1\n");
                exit(EXIT_FAILURE);
        }
	if (j > size(M)) {
                printf("Matrix Error: calling changeEntry() j greater than size(M)\n");
                exit(EXIT_FAILURE);
	}
	
	// Entry temp = newEntry(i, x);
	if (x != 0.0) {
		//printf("heyooo\n");
		Entry temp = newEntry(j, x);
		// if there's nothing in the list, prepend to it and return
		if (length(M->info[i]) == 0) {
			//printf("yoOo\n");
			prepend(M->info[i], temp);
			M->nnz += 1;
			return;
		}
		
		// now we know there's at least one entry in the list
		// does the entry already exist? if so, change the value
		// that's in there
		// if we reach j+1, insertBefore (reduce redundancy)
		int counter = 0;
		
		Entry move;
		moveFront(M->info[i]);
		//printf("%d %d\n", length(M->info[i]), i);
		while (index(M->info[i]) != -1) {
			counter += 1;
			move = get(M->info[i]);
			//printf("%d %f ", move->column, move->value);
			//printf("why\n");
			//printList(stdout, M->info[i]);
			if (move->column == j) {
				//printf("inside if move->column\n");
				move->value = x;
				return;
			}	
			if (counter == j+1) {
				//printf("BOO\n");
				insertBefore(M->info[i], temp);
				M->nnz += 1;
				return;
			}
			moveNext(M->info[i]);	
		}

		append(M->info[i], temp);
		// printf("%d %d\n", length(M->info[i]), i);
		M->nnz += 1; 

	}

	if (x == 0.0) {
		// if the list is empty. do nothing
		if (length(M->info[i]) == 0) {
			return;
		}
		// does the space exist? if so, delete that space
		Entry next;
		moveFront(M->info[i]);
                while (index(M->info[i]) != -1) {
			next = get(M->info[i]);
                        if (next->column == j) {
				M->nnz = M->nnz - 1;
				delete(M->info[i]);
				return; 
                        }
                        moveNext(M->info[i]);
                }
		// if we reach this point, it means the space doesn't exist
		// we don't need to do antything. we don't add in zero values.
		return;
	}
}

// Manipulation procedures ------------------------------------------------------------------

// copy()
// Returns a reference to a new Matrix object having the same entries as A
Matrix copy(Matrix A) {
	// create new matrix object, set the size equal to size(A)
	// set nnz to the same as A
	// loop through lists of A
	// create new entry and set those fields equal. 
	// append each of these entries as you go.
	// return matrix
	Matrix copy = newMatrix(size(A));
	copy->nnz = NNZ(A);
	
	Entry new;
	for (int i = 1; i <= size(A); i++) {
		moveFront(A->info[i]);
		while (index(A->info[i]) != -1) {
			new = get(A->info[i]);
			append(copy->info[i], new);	
			moveNext(A->info[i]);
		}
	}

	return copy;
}

// transpose()
// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A) {
	// create new matrix that's size(A)
	Entry new;
	Matrix T = newMatrix(size(A)); 
	T->nnz = NNZ(A);

	for (int i = 1; i <= size(A); i++) {
		moveFront(A->info[i]);
		while (index(A->info[i]) != -1) {
			new = get(A->info[i]);
			Entry e;
			e = newEntry(i, new->value);
			append(T->info[new->column], e);
			moveNext(A->info[i]);	
		}
	}
	return T;
}

// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A) {
	// create new matrix obj, make it sizeof A
	// go through lists, for and while loop
	// multiple the values of the list by scalar
	Matrix C = newMatrix(size(A));
	if (x == 0.0) {
		C->nnz = 0;
		return C;	
	}	

	C->nnz = NNZ(A);
	Entry new;
	for (int i = 1; i <= size(A); i++) {
		moveFront(A->info[i]);
		while (index(A->info[i]) != -1) {
			new = get(A->info[i]);	
			Entry add_on;
			add_on = newEntry(new->column, new->value*x);
			append(C->info[i], add_on);
			moveNext(A->info[i]);	
		}
	}

	return C;
}

// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B) {
	// create new matrix, size of size(A)
	// loop through both matrices simultaneously
	if (size(A) != size(B)) {
		printf("Matrix Error: calling sum() on matrices A and B that are different sizes\n");
		exit(EXIT_FAILURE);		
	}

	if (A == B) {
		return scalarMult(2, A);
	}

	Matrix S = newMatrix(size(A));
	Matrix R = newMatrix(size(B));
	/*
	Entry a;
	Entry b;
	double sum;
	for (int i = 1; i <= size(A); i++) {
		// if (length(A->info[i]) > length(B->info[i])) {
		moveFront(A->info[i]);
		moveFront(B->info[i]);
		while (index(A->info[i]) != -1 || index(B->info[i]) != -1) {
			if (index(A->info[i]) == -1 && index(B->info[i]) != -1) {
				//fprintf(out, "first if\n");
				b = get(B->info[i]);
				append(S->info[i], b);
				S->nnz += 1;
				moveNext(B->info[i]);
				//fprintf(out, "after if\n");
			}
			if (index(B->info[i]) == -1 && index(A->info[i]) != -1) {
				//printf("next if\n");
				a = get(A->info[i]);
				append(S->info[i], a);
				S->nnz += 1;
				moveNext(A->info[i]);
				//printf("after next if\n");
			}
			else { 
				//printf("TOOP\n");
				a = get(A->info[i]);
				//printf("BOOP\n");
				b = get(B->info[i]);
				//printf("HELLO\n");
				if (a->column == b->column) {
					sum = a->value + b->value;
					if (sum == 0.0) {
						S->nnz = S->nnz;
					}	
					else {
						Entry new = newEntry(a->column, sum);
						append(S->info[i], new);
						S->nnz += 1;
					}
					moveNext(A->info[i]);
					moveNext(B->info[i]);
				}
				else {
					if (a->column > b->column) {
						append(S->info[i], b);
						moveNext(B->info[i]);
						// append(S->info[i], a);
						S->nnz += 1;
					}	
					else if (b->column > a->column) {
						append(S->info[i], a);
						moveNext(A->info[i]);
						// append(S->info[i], b);
						S->nnz += 1;
					}
				}
			}
			// moveNext(A->info[i]);
			// moveNext(B->info[i]);						
		}
	} */

	freeMatrix(&R);	
	return S;
}

// diff()
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B) {
	if (size(A) != size(B)) {
                printf("Matrix Error: calling sum() on matrices A and B that are different sizes\n");
                exit(EXIT_FAILURE);
        }
	
	if (A == B) {
		return scalarMult(0.0, A);
	}

	Matrix R = newMatrix(size(A));
	Matrix N = newMatrix(size(B));

	freeMatrix(&N);
	return R;

}	

// double vectorDot()
// computes the vector dot product of two matrix rows represented by Lists P and Q
double vectorDot (List P, List Q) {
	Entry p;
	Entry q;
	double answer = 0.0;


		moveFront(P);
                moveFront(Q);
		
		 while (index(P) != -1 && index(Q) != -1) {
                        /*if (index(P) == -1 && index(Q) != -1) {
				moveNext(Q);
                        }
                        if (index(Q) == -1 && index(P) != -1) {
                                moveNext(P);
                        }*/
			
				p = get(P);
				q = get(Q);
				if (p->column == q->column) {
					answer += p->value * q->value;
					moveNext(P);
					moveNext(Q);
				}
				else {
					if(p->column > q->column) {
						moveNext(Q);
					}
					else if (q->column > p->column) {
						moveNext(P);
					}
				}
			
		}
		

	return answer;
}

// product()
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B) {
	if (size(A) != size(B)) {
                printf("Matrix Error: calling sum() on matrices A and B that are different sizes\n");
                exit(EXIT_FAILURE);
 
       }
	
	Matrix T = transpose(B);
	Matrix P = newMatrix(size(A));

	double product;
	// Entry temp;
	Entry put;

	for (int i = 1; i <= size(A); i++) {
		if (length(A->info[i]) > 0) {
		for (int x = 1; x <= size(T); x++) { 
			if (length(T->info[x]) > 0) {
			product = vectorDot(A->info[i], T->info[x]);
			if (product != 0) {
				put = newEntry(x, product);
				append(P->info[i], put);
				P->nnz += 1;
			}
			}
		}
		}
	}
	
	freeMatrix(&T);
	return P;	
}

// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero rows 
// are not printed. Each non-zero row is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M) {
	if (M == NULL) {
                printf("Matrix Error: calling printMatrix() on NULL Matrix reference\n");
                exit(EXIT_FAILURE);
        }
	if (out == NULL) {
                printf("Unable to open file outfile for writing\n");
                exit(EXIT_FAILURE);
        }

	Entry temp = NULL;
	for (int i = 1; i <= size(M); i++) {
		if (length(M->info[i]) > 0) {
			moveFront(M->info[i]);
			fprintf(out, "%d: ", i);
			while (index(M->info[i]) != -1) {
				temp = get(M->info[i]);
				fprintf(out, "(%d, %0.1f)", temp->column, temp->value);
				moveNext(M->info[i]);		
			}
			fprintf(out, "\n");
		}
	}	
} 
