/*********************************************************************************
 * * Anya Rajan, arajan2
 * * 2022 Spring CSE101 PA4
 * * README 
 * * README as a table of contents for project files
 * **********************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"List.h"

int main(int argc, char* argv[]){
   List A = newList();
   List B = newList();
   int i;
   int X[] = {0,1,2,3,4,5,6,7,8,9,10,11,12};

   for(i=1; i<=10; i++){
      append(A,&X[i]);
      prepend(B,&X[i]);
   }

   printf("Length of A: %d\n", length(A));
   printf("Length of B: %d\n", length(B));

   printf("Front of A: %d\n", *(int*)front(A));
   printf("Front of B: %d\n", *(int*)front(B));

   printf("Back of A: %d\n", *(int*)back(A));
   printf("Back of B: %d\n", *(int*)back(B));

   moveFront(A);
   moveNext(A);
   printf("%d\n", *(int*)get(A));

   moveFront(A);
   printf("%d\n", *(int*)get(A));

   moveBack(B);	
   printf("%d", *(int*)get(A));

   // insertBefore(B, 444);

   deleteFront(A);
   deleteBack(A);
  
   printf("\n");
   printf("Length of A: %d\n", length(A));

   freeList(&A);
   freeList(&B);

   return(0);
}

