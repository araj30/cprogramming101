/********************************************************************************* 
 * Anya Rajan, arajan2
 * 2022 Spring CSE101 PA2 
 * FindPath.c 
 * FindPath.c to utilize Graph ADT functions 
 * **********************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include "Graph.h"

int main(int argc, char * argv[]) {
   	FILE *in, *out;
   	//char line[MAX_LEN];

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
		// fscanf(in, "%d %d", &var1, &var2);
		if (var1 == 0 || var2 == 0) {
			break;
		}
		addEdge(G, var1, var2);
		// printf("%d\n", getSource(G));
	}
	
	printGraph(out, G);

	// List L = newList();
	while (fscanf(in, "%d %d", &var1, &var2) != EOF) {
		if (var1 == 0 || var2 == 0) {
			break;
		}	
		List L = newList();
		// printf("%d\n", getSource(G));
		//printf("%d\n", var1);
		//printf("%d\n", var2);
		// printf("%d\n", getOrder(G));
		BFS(G, var1);
		// printGraph(stdout, G);
		// printf("%d\n", getSource(G));
		getPath(L, G, var2);
		fprintf(out, "\n");
		fprintf(out, "The distance from %d to %d is %d\n", var1, var2, getDist(G, var2));
		if (getDist(G, var2) == INF) {
			fprintf(out, "No %d-%d path exists\n", var1, var2);
			// continue;
		}	
		fprintf(out, "A shortest %d-%d path is: ", var1, var2);
		printList(out, L);
		fprintf(out, "\n");
		freeList(&L);
	} 

	fclose(in);
	fclose(out);
	// freeList(&L);
	freeGraph(&G); 		
}
