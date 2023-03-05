/********************************************************************************* 
 * Anya Rajan, arajan2
 * 2022 Spring CSE101 PA2 
 * GraphTest.c 
 * GraphTest.c for to utilize Graph ADT functions 
 * **********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(int argc, char* argv[]){
	// testing newGraph()
	int order = 10;
	
	Graph G = newGraph(order);
	List L = newList();
	
	printf("%d\n", getOrder(G));
	addEdge(G, 1, 2);
	addEdge(G, 3, 5);
	addEdge(G, 8, 9);
	addEdge(G, 5, 9);
	addEdge(G, 3, 4);
	addEdge(G, 1, 6);
	addEdge(G, 2, 10);
	addEdge(G, 7, 6);

	printGraph(stdout, G);

	printf("%d", getSize(G));
	printf("%d", getSource(G));
	printf("%d", getParent(G, 5));
	printf("%d\n", getDist(G, 9));
	
	BFS(G, 8);
	getPath(L, G, 9);
	printf("\n");
	printf("The distance from 8-9 is: %d\n", getDist(G, 9));
	printf("\n");
	printf("A shortest 8-9 path is: \n");
	printList(stdout, L);
	printf("\n");
	freeList(&L);
	makeNull(G);
	freeGraph(&G);
	return(0);
}
