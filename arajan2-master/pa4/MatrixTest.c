#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include"Matrix.h"
     
int main(){
   int n = 100;
   Matrix A = newMatrix(n);
   Matrix B = newMatrix(n);
   Matrix H;
   Matrix F;
   Matrix C;
   Matrix D;
   // Matrix E;
   Matrix G;

   changeEntry(A, 1,1,0);  
   changeEntry(A, 1,2,3);  
   changeEntry(A, 1,4,1);  
   changeEntry(A, 2,3,3);  
   changeEntry(A, 3,1,6);  
   changeEntry(A, 3,2,3);  
   changeEntry(A, 3,4,1);  

   printf("Matrix A:\n");
   printMatrix(stdout, A);
   printf("\n");

   changeEntry(B, 1,1,2);
   changeEntry(B, 1,3,1);
   changeEntry(B, 2,1,3);
   changeEntry(B, 3,1,4);
   changeEntry(B, 3,2,1);
   changeEntry(B, 4,1,2);
   changeEntry(B, 4,2,3);
   
   printf("Matrix B:\n");
   printMatrix(stdout, B);
   printf("\n");

   printf("NNZ of A: %d\n", NNZ(A));
   printf("NNZ of B: %d\n", NNZ(B));
  
   printf("\n");

   printf("Size of A: %d\n", size(A));
   printf("Size of B: %d\n", size(B));

   printf("\n");
   
   // printf("Scalar mult of A:\n");
   C = scalarMult(2, A);
   printf("Scalar mult of A:\n");
   printMatrix(stdout, C);
   printf("NNZ of new matrix: %d\n", NNZ(C));
   printf("\n");
   
   // printf("Sum of A+A:\n");
   D = sum(A, A);
   // printf("NNZ of new matrix: %d\n", NNZ(D));
   printf("Sum of A+A:\n");
   printMatrix(stdout, D);
   printf("NNZ of new matrix: %d\n", NNZ(D));
   printf("\n");

   // printf("Difference of A-B:\n");
   //E = diff(A, B);
   //printf("Difference of A-B:\n");
   //printMatrix(stdout, E);
   //printf("NNZ of new matrix: %d\n", NNZ(E));
   //printf("\n");

   F = transpose(A);
   printf("Transpose of A:\n");
   printMatrix(stdout, F);
   printf("NNZ of new matrix: %d\n", NNZ(F));
   printf("\n");

   G = product(A, B);
   printf("Product of A*B:\n");
   printMatrix(stdout, G);
   printf("NNZ of new Matrix: %d\n", NNZ(G));
   printf("\n"); 

   H = copy(B);
   printf("Copy of B:\n");
   printMatrix(stdout, H);
   printf("NNZ of new matriz: %d\n", NNZ(H));
   printf("\n");

   printf("%s\n", equals(B, H)?"true":"false" );
   printf("%s\n", equals(A, B)?"true":"false" );
   printf("%s\n", equals(A, A)?"true":"false" );

   // printf("Make zero of both matrices (A and B):\n");
   // makeZero(A);
   // printf("NNZ of new matrix A: %d\n", NNZ(A));
   // printMatrix(stdout, A);

   // makeZero(B);
   // printf("NNZ of new matrix B: %d\n", NNZ(B));
   // printMatrix(stdout, B);

   freeMatrix(&A);
   freeMatrix(&B);
   freeMatrix(&C);
   freeMatrix(&D);
   // freeMatrix(&E);
   freeMatrix(&F);
   freeMatrix(&G);
   freeMatrix(&H);

   return EXIT_SUCCESS;
}

