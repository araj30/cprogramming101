/********************************************************************************* 
* Anya Rajan, arajan2
* 2022 Spring CSE101 PA1 
* ListTest.c
* ListTest.c file to test List ADT functions 
***********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"List.h"

int main(int argc, char* argv[]){
   
   // testing newList()
   List A = newList();
   List B = newList();
   List b = NULL;
   int i;

   // testing append and prepend
   for(i=1; i<=10; i++){
      append(A,i);
      prepend(B,i);
   }

   // checking copyList
   b = copyList(B);

   // testing printList
   printList(stdout,A); 
   printf("\n");
   printList(stdout,B); 
   printf("\n");
   printList(stdout,b);
   printf("\n");
   printf("\n");

   printf("%s\n", equals(A,B)?"true":"false");
   printf("%s\n", equals(B,b)?"true":"false");
   printf("%s\n", equals(b,A)?"true":"false");
   printf("\n");

   printf("%d\n", length(A));
   printf("%d\n", length(B));
   printf("%d\n", length(b));
   printf("\n");   

   printf("%d\n", front(A));
   printf("%d\n", front(B));
   printf("%d\n", front(b));
   printf("\n");

   printf("%d\n", back(A));
   printf("%d\n", back(B));
   printf("%d\n", back(b));
   printf("\n");

   moveFront(A);
   printf("%d\n", index(A));
  
   moveNext(A);
   printf("%d\n", get(A));
   
   moveBack(A);
   printf("%d\n", index(A));

   movePrev(A);
   printf("%d\n", index(A));
   
   moveFront(A);
   printf("%d\n", index(A));

   moveNext(A);
   printf("%d\n", index(A));

   moveFront(A);
   insertBefore(A, 888);
   moveNext(A);
   printList(stdout,A);
   printf("\n");
	
   deleteFront(A);
   printList(stdout,A);
   printf("\n");

   deleteBack(A);
   printList(stdout,A);
   printf("\n");

   moveBack(A);
   insertAfter(A, 777);
   printList(stdout,A);
   printf("\n");
   moveBack(A);
   set(A, 111);
   printList(stdout,A);
   printf("\n");

   moveBack(A);
   movePrev(A);
   movePrev(A);
   delete(A);
   printList(stdout,A);
   printf("\n");
   
   clear(A);
   printf("%d\n", length(A));

   freeList(&A);
   freeList(&B);
   freeList(&b);

   return(0);
}

/*
 * Output of this program:
 * 1 2 3 4 5 6 7 8 9 10 
 * 10 8 9 7 6 5 4 3 2 1
 * 10 9 8 7 6 5 4 3 2 1
 *
 * false
 * true
 * false
 *
 * 10
 * 10
 * 10
 *
 * 1
 * 10
 * 10
 *
 * 10
 * 1
 * 1
 *
 * */
