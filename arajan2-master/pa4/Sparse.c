/********************************************************************************* 
 * Anya Rajan
 * 2022 Spring CSE101 PA4
 * Sparse.c
 * Sparse.c for to utilize Matrix ADT functions 
 * **********************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include "Matrix.h"
#include "List.h"

int main(int argc, char * argv[]) {
	FILE *in, *out;

	in = fopen(argv[1], "r");
      	if (in == NULL) {
      		printf("Unable to open file %s for reading\n", argv[1]);
      		exit(1);
   	}

	out = fopen(argv[2], "w");
  	 if (out == NULL) {
      		printf("Unable to open file %s for writing\n", argv[2]);
      		exit(1);
   	 }

	int n = 0;
	int a = 0;
	int b = 0;
	// char enter;

	fscanf(in, "%d %d %d", &n, &a, &b);
	// fscanf(in, "%c", &enter);

	Matrix A = newMatrix(n);
	// A->nnz = a;

	Matrix B = newMatrix(n);
	// B->nnz = b;
	
	int row;
	int col;
	double val;

	for (int i = 0; i < a; i++) {
		fscanf(in, "%d %d %lf", &row, &col, &val);
		changeEntry(A, row, col, val);
	}

	// fscanf(in, "%c", &enter);

	for (int x = 0; x < b; x++) {
		fscanf(in, "%d %d %lf", &row, &col, &val);
		changeEntry(B, row, col, val);
	}

	fprintf(out, "A has %d non-zero entries:\n", a);
	printMatrix(out, A);

	fprintf(out, "B has %d non-zero entries:\n", b);
	printMatrix(out, B);

	fprintf(out, "(1.5)*A =\n");
	Matrix S = scalarMult(1.5, A);
	printMatrix(out, S);

	fprintf(out, "A+B =\n");
	Matrix ADD = sum(A, B);
	printMatrix(out, ADD);

	fprintf(out, "A+A =\n");
	Matrix H = sum(A, A);
	printMatrix(out, H);

	fprintf(out, "B-A =\n");
	Matrix G = diff(B, A);
	printMatrix(out, G);

	fprintf(out, "A-A =\n");
	Matrix K = diff(A, A);
	printMatrix(out, K);

	fprintf(out, "Transpose(A) =\n");
	Matrix T = transpose(A);
	printMatrix(out, T);

	
	freeMatrix(&A);
	freeMatrix(&B);
	freeMatrix(&S);
	freeMatrix(&ADD);
	freeMatrix(&H);
	freeMatrix(&G);
	freeMatrix(&K);
	freeMatrix(&T);
	
	fclose(in);
	fclose(out);

	return EXIT_SUCCESS;
}

