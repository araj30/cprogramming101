/************************************************************************************
* Anya Rajan, arajan2
* 2022 Spring CSE101 PA4 
* Matrix.h 
* Matrix.h for function prototypes of Matrix ADT functions 
* ***********************************************************************************/

#include<stdbool.h>
#include<stdio.h>

// Structs -------------------------------------------------------------------
typedef struct MatrixObj* Matrix;

// Constructors-Destructors ---------------------------------------------------
Matrix newMatrix(int n); // Returns a reference to a new nXn Matrix object in the zero state.
void freeMatrix(Matrix* pM); // Frees heap memory associated with *pM, sets *pM to NULL.

// Access functions -----------------------------------------------------------
int size(Matrix M); // Return the size of square Matrix M.
int NNZ(Matrix M); // Return the number of non-zero elements in M.
int equals(Matrix A, Matrix B); // Return true (1) if matrices A and B are equal, false (0) otherwise.

// Manipulation procedures -----------------------------------------------------
void makeZero(Matrix M); // Re-sets M to the zero Matrix state.
void changeEntry(Matrix M, int i, int j, double x); // Changes the ith row, jth column of M to the value x.

// Matrix Arithmetic operations --------------------------------------------------
Matrix copy(Matrix A); // Returns a reference to a new Matrix object having the same entries as A
Matrix transpose(Matrix A); //  Returns a reference to a new Matrix object representing the transpose of a
Matrix scalarMult(double x, Matrix A); // Returns a reference to a new Matrix object representing xA.
Matrix sum(Matrix A, Matrix B); //  Returns a reference to a new Matrix object representing A+B.
Matrix diff(Matrix A, Matrix B); // Returns a reference to a new Matrix object representing A-B.
Matrix product(Matrix A, Matrix B); // Returns a reference to a new Matrix object representing AB
void printMatrix(FILE* out, Matrix M); // Prints a string representation of Matrix M to filestream out. 


