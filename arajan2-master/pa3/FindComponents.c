/********************************************************************************* 
 * Anya Rajan, arajan2
 * 2022 Spring CSE101 PA3
 * FindComponents.c 
 * FindComponents.c to utilize Graph ADT functions 
 * ***********************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include "Graph.h"

int main(int argc, char * argv[]) {

	FILE *in, *out;
	// check command line for correct number of arguments
	if (argc != 3) {
      		printf("Usage: %s <input file> <output file>\n", argv[0]);
      		exit(1);
   	}

	// open files for reading and writing
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
	fscanf(in, "%d", &n);
	int var1 = 0;
	int var2 = 0;

	Graph G = newGraph(n);
	while (fscanf(in, "%d %d", &var1, &var2) != EOF) {
		if (var1 == 0 || var2 == 0) {
			break;
		}
		addArc(G, var1, var2);
	}
	
	fprintf(out, "Adjacency list representation of G:\n");
	printGraph(out, G);
	fprintf(out, "\n");
	List L = newList();
	for (int i = 1; i <= n; i++) {
		append(L, i);
	}

        DFS(G, L);

	Graph T = newGraph(n);
	T = transpose(G);

	DFS(T, L);	
	
	int counter = 0;
	
	moveBack(L);
	while (index(L) != -1) {
		if (getParent(T, get(L)) == NIL) {
			counter += 1;
		}
		movePrev(L);
	} 

	fprintf(out, "G contains %d strongly connected components:\n", counter);

	int track = 0;
	List temp = newList();
	moveBack(L);
	while (index(L) != -1) {
		if (getParent(T, get(L)) != NIL) {
			prepend(temp, get(L));
		}
		else {
			track += 1;
			fprintf(out, "Component %d: ", track);
			prepend(temp, get(L));
			printList(out, temp);
			fprintf(out, "\n");
			clear(temp);
		}
		movePrev(L);
	}
 
	fclose(in);
	fclose(out);
	freeGraph(&G);
	freeList(&L);
	freeGraph(&T);
	freeList(&temp);

}

