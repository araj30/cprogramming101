/********************************************************************************* 
 * Anya Rajan, arajan2
 * 2022 Spring CSE101 PA2 
 * GraphTest.c
 * GraphTest.c file to test Graph ADT functions 
 * ***********************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include"List.h"
#include"Graph.h"

int main(int argc, char* argv[]){
   // some tests and structures provided by Patrick Tantalo
   int n = 5;
   List L = newList();
   Graph G = newGraph(n);

   for (int i = 1; i <= n; i++) { 
	append(L, i);
   }

   addEdge(G, 1,2);
   addArc(G, 1,3);
   // addArc(G, 2,1);
   addArc(G, 3,1);
   addArc(G, 4,2);
   addArc(G, 4,5);
   addArc(G, 5,4); 
   fprintf(stdout, "Graph adjacency list of G:\n");
   printGraph(stdout, G);
   fprintf(stdout, "\n");

   fprintf(stdout, "Order of G: %d", getOrder(G));
   fprintf(stdout, "\n");
   fprintf(stdout, "Size of G: %d", getSize(G));
   fprintf(stdout, "\n");

   DFS(G, L);
   fprintf(stdout, "\n");
   fprintf(stdout, "Discover times, finish times, and parents of vertices in G:\n");
   fprintf(stdout, "x:  d  f  p\n");
   for(int x = 1; x <= n; x++){
      fprintf(stdout, "%d: %2d %2d %2d\n", x, getDiscover(G, x), getFinish(G, x), getParent(G, x));
   }
   fprintf(stdout, "\n");
   fprintf(stdout, "List of G ordered by finish times of vertices: ");
   printList(stdout, L);
   fprintf(stdout, "\n");

   Graph T = newGraph(getOrder(G));
   Graph C = newGraph(getOrder(G));
	
   T = transpose(G);
   C = copyGraph(G);
   fprintf(stdout, "\n");
   fprintf(stdout, "Copy of G:\n");
   printGraph(stdout, C);
   fprintf(stdout, "\n");
   fprintf(stdout, "Transpose of G:\n");
   printGraph(stdout, T);
   fprintf(stdout, "\n");

   DFS(T, L);
   int counter = 0;

   moveBack(L);
   while (index(L) != -1) {
   	if (getParent(T, get(L)) == NIL) {
        	counter += 1;
        }
        movePrev(L);
   }

   fprintf(stdout, "G contains %d strongly connected components:\n", counter);

   int track = 0;
   List temp = newList();
   moveBack(L);
   while (index(L) != -1) {
   	if (getParent(T, get(L)) != NIL) {
        	prepend(temp, get(L));
        }
        else {
                track += 1;
                fprintf(stdout, "Component %d: ", track);
                prepend(temp, get(L));
                printList(stdout, temp);
                fprintf(stdout, "\n");
                clear(temp);
       	}
        movePrev(L);
   }

   freeList(&L);
   // freeList(&L);
   freeGraph(&G);
   freeGraph(&T);
   freeGraph(&C);
   return(0);
}


