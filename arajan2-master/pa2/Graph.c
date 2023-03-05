/************************************************************************************
* Anya Rajan, arajan2
* 2022 Spring CSE101 PA2 
* Graph.c 
* Graph.c to define Graph ADT functions 
* ***********************************************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "Graph.h"
#include "List.h"

// structs ----------------------------------------------------------------------- 
// private GraphObj type
typedef struct GraphObj {
	int n;
	int size;
	int source;
	List *neighbors;
	char *colors;
	int *parents;
	int *distance;
} GraphObj;

// constructors-destructors ------------------------------------------------------
// newGraph()
// Initializes all the variables and arrays associated with a Graph.
// Allocates memory for these elements.
// Returns a new Graph G.
Graph newGraph(int n) {
	Graph G = malloc(sizeof(GraphObj));
	G->n = n;
 	G->size = 0;
 	G->source = NIL;
	G->neighbors = calloc(n+1, sizeof(List));
	G->colors = calloc(n+1, sizeof(int));
        G->parents = calloc(n+1, sizeof(int));
        G->distance = calloc(n+1, sizeof(int));
	G->neighbors[0] = NULL;
	for (int i = 1; i <= n; i++) {
		G->neighbors[i] = newList();
		G->colors[i] = w;
		G->parents[i] = NIL; 
		G->distance[i] = INF;
	}
	return(G);	
}

// freeGraph()
// Frees all memory associated with the Graph passed in.
void freeGraph(Graph* pG) {
	if (*pG == NULL || pG == NULL) {
		printf("List Error: calling freeList on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	
	makeNull(*pG);
	for (int i = 1; i <= (*pG)->n; i++) {
		freeList(&(*pG)->neighbors[i]);
	}	
	
	free((*pG)->neighbors);
	free((*pG)->colors);
	free((*pG)->parents);
	free((*pG)->distance);

	free(*pG);
	*pG = NULL;

}

// access functions ----------------------------------------------------------------
// getOrder()
// pre: check is Graph G is NULL. if it is, throw an error. otherwise, continue.
// return the order of G
int getOrder(Graph G) {
	if (G == NULL) {
                printf("Graph Error: calling getOrder() on NULL Graph\n");
                exit(EXIT_FAILURE);

        }
	return G->n;	
}

// getSize()
// pre: check is Graph G is NULL. if it is, throw an error. otherwise, continue.
// return the sizse of G
int getSize(Graph G) {
	if (G == NULL) {
                printf("Graph Error: calling getSize() on NULL Graph\n");
                exit(EXIT_FAILURE);

        }
	return G->size;
}

// getSource()
// pre: check is Graph G is NULL. if it is, throw an error. otherwise, continue.
// pre: if the source of G is NIL, return NIL
// returns the source vertex most recently used in function BFS(), or NIL if
// BFS() has not yet been called. 
int getSource(Graph G) {
	if (G == NULL) {
		printf("Graph Error: calling getSource() on NULL Graph\n");
		exit(EXIT_FAILURE);

	}
	if (G->source == NIL) {
		return NIL;
	}
	return G->source;
}

// getParent()
// pre: check is Graph G is NULL. if it is, throw an error. otherwise, continue.
// pre: if the source of G is NIL, return NIL
// returns the source vertex most recently used in function BFS(), or NIL if
// BFS() has not yet been called.
int getParent(Graph G, int u) {
 	if (G == NULL) {
                printf("Graph Error: calling getParent() on NULL Graph\n");
                exit(EXIT_FAILURE);

        }
	if (getSource(G) == NIL) {
                return NIL;
        }
        if (u < 1) {
                printf("Graph Error: calling getParent() on u that is greater than or equal to 0\n");
                exit(EXIT_FAILURE);
        }
        if (getOrder(G) < u) {
                printf("Graph Error: calling getParent() on u less than or equal to order of G\n");
                exit(EXIT_FAILURE);
	}

	return G->parents[u];
}

// getDist()
// pre: check is Graph G is NULL. if it is, throw an error. otherwise, continue.
// pre: if the source of G is NIL, return INF 
// Function getDist() returns the distance from
// the most recent BFS source to vertex u, or INF if BFS() has not yet been called.
int getDist(Graph G, int u) {
	if (G == NULL) {
                printf("Graph Error: calling getDist() on NULL Graph\n");
                exit(EXIT_FAILURE);

        }
	if (getSource(G) == NIL) {
                return INF;
        }
	if (u < 1) {
		printf("Graph Error: calling getDist() on u that is greater than or equal to 0\n");
		exit(EXIT_FAILURE);
	}
	if (getOrder(G) < u) {
		printf("Graph Error: calling getDist() on u less than or equal to order of G\n");
		exit(EXIT_FAILURE);
	}
	return G->distance[u];
}

// getPath()
// pre: check is Graph G is NULL. if it is, throw an error. otherwise, continue.
// pre: if the source of G is NIL, throw an error
// pre: check if u is between 1 and getOrder(G), otherwise throw an error
// appends to the List L the vertices of a shortest path in G from source to u, 
// or appends to L the value NIL if no such path exists. 
void getPath(List L, Graph G, int u) {
	if (G == NULL) {
                printf("Graph Error: calling getPath() on NULL Graph\n");
                exit(EXIT_FAILURE);

        }
	if (getSource(G) == NIL) {
                printf("Graph Error: calling getPath() on NULL source ONE TWO THREE\n");
                exit(EXIT_FAILURE);
        }
        if (u < 1) {
                printf("Graph Error: calling getPath() on u that is greater than or equal to 0\n");
                exit(EXIT_FAILURE);
        }
        if (getOrder(G) < u) {
                printf("Graph Error: calling getPath() on u less than or equal to order of G\n");
                exit(EXIT_FAILURE);
	}
	// if (getDist(G, u) == NIL) {
	//	append(L, NIL);
	//	return;
	//}

	if (G->source == u) {
		append(L, u);
	}

	else if (G->parents[u] == NIL) {
		clear(L);
		append(L, NIL);
	}
	else {
		getPath(L, G, G->parents[u]);
        	append(L, u);
	}	
}

// manipulation procedures ------------------------------------------------------------

// makeNull()
// pre: check is Graph G is NULL. if it is, throw an error. otherwise, continue.
// Function makeNull() deletes all edges of G, restoring it to its original (no edge) state. 
void makeNull(Graph G) {
	if (G == NULL) {
                printf("Graph Error: calling getPath() on NULL Graph\n");
                exit(EXIT_FAILURE);

        }

	G->size = 0;
	G->source = NIL;
	for (int i = 1; i <= G->n; i++) {
                clear(G->neighbors[i]);
                G->colors[i] = w;
                G->parents[i] = NIL;
                G->distance[i] = INF;
        }
}

// addEdge()
// pre: check is Graph G is NULL. if it is, throw an error. otherwise, continue.
// pre: check if u is between 1 and getOrder(G), otherwise throw an error
// check if v is between 1 and getOrder(G), otherwise throw an error
// Function addEdge() inserts a new edge joining u to v (add to the adjacency list of each other)
void addEdge(Graph G, int u, int v) {
	if (G == NULL) {
                printf("Graph Error: calling getPath() on NULL Graph\n");
                exit(EXIT_FAILURE);

        }
	if (u < 1) {
		printf("Graph Error: calling addEdge on u that is less than 1\n");
		exit(EXIT_FAILURE);
	}
	if (u > getOrder(G)) {
		printf("Graph Error: calling addEdge on u that is greater than getOrder(G)\n");
		exit(EXIT_FAILURE);
	}
	if (v < 1) {
		printf("Graph Error: calling addEdge on v that is less than 1\n");
                exit(EXIT_FAILURE);
	}
	if (v > getOrder(G)) {
                printf("Graph Error: calling addEdge on v that is greater than getOrder(G)\n");
                exit(EXIT_FAILURE);
        }
	if (u == v) {
		return;
	}

	addArc(G, u, v);

	addArc(G, v, u);
	G->size -= 1;		
}

// addArc()
// pre: check is Graph G is NULL. if it is, throw an error. otherwise, continue.
// pre: check if u is between 1 and getOrder(G), otherwise throw an error
// check if v is between 1 and getOrder(G), otherwise throw an error
// Function addArc() inserts a new directed edge from u to v
void addArc(Graph G, int u, int v) {
	if (G == NULL) {
                printf("Graph Error: calling getPath() on NULL Graph\n");
                exit(EXIT_FAILURE);
        }
	if (u < 1) {
                printf("Graph Error: calling addEdge on u that is less than 1\n");
                exit(EXIT_FAILURE);
        }
        if (u > getOrder(G)) {
                printf("Graph Error: calling addEdge on u that is greater than getOrder(G)\n");
                exit(EXIT_FAILURE);
        }
        if (v < 1) {
                printf("Graph Error: calling addEdge on v that is less than 1\n");
                exit(EXIT_FAILURE);
        }
        if (v > getOrder(G)) {
                printf("Graph Error: calling addEdge on v that is greater than getOrder(G)\n");
                exit(EXIT_FAILURE);
        }
	if (G->neighbors[u] == 0) {
		append(G->neighbors[u], v);
		G->size += 1;
		return;
	}

	moveFront(G->neighbors[u]);
	while (index(G->neighbors[u]) != -1) {
		if (get(G->neighbors[u]) < v) {
			moveNext(G->neighbors[u]);
		}
		else {
			break;
		}
	}

	if (index(G->neighbors[u]) == -1) {
		append(G->neighbors[u], v);
	}

	else {
		insertBefore(G->neighbors[u], v);
	}

	G->size += 1;

}

// BFS()
// pre: check is Graph G is NULL. if it is, throw an error. otherwise, continue.
// Function BFS() runs the BFS algorithm on the Graph G with source s,
// setting the color, distance, parent, and source fields of G accordingly.
void BFS(Graph G, int s) {
	if (G == NULL) {
                printf("Graph Error: calling getPath() on NULL Graph\n");
                exit(EXIT_FAILURE);
        }

	// if (s < 0 || s > G->n) {
	//	  printf("Graph Error: calling BFS on source that is out of bounds\n");
        //}         exit(EXIT_FAILURE);
	
	for (int i = 1; i <= getOrder(G); i++) {
		G->colors[i] = w;
		G->distance[i] = INF;
		G->parents[i] = NIL;
	}
	G->source = s;
	G->colors[s] = g;
	G->distance[s] = 0;
	G->parents[s] = NIL;

	List L = newList();
	append(L, s);

	// printList(stdout, L);		
	while (length(L) > 0) {
		// printf("ONE OPEN");
		int x = front(L);
		deleteFront(L);
		if (length(G->neighbors[x]) != 0) {
			moveFront(G->neighbors[x]);
			// printList(stdout, G->neighbors[x]);
			while (index(G->neighbors[x]) != -1) {
				// printf("TWO OPEN");
				int y = get(G->neighbors[x]);
				// printf("%d\n", y);
				if (G->colors[y] == w) {
					//printf("IF STATEMENT");
					G->colors[y] = g;
					G->distance[y] = G->distance[x] + 1;
					G->parents[y] = x;
					append(L, y);
				}
				moveNext(G->neighbors[x]);
			}
		}
		// printf("TWO END");
		G->colors[x] = b;
	}
	// printf("ONE END");
	freeList(&L);		
}

// other operations -------------------------------------------------------------------

// printGraph()
// pre: check is Graph G is NULL. if it is, throw an error. otherwise, continue.
// pre: if the out file is equal to NULL, throw an error
// printGraph() prints the adjacency list representation of G to the file pointed to by out
void printGraph(FILE* out, Graph G) {
	if (G == NULL) {
                printf("Graph Error: calling getPath() on NULL Graph\n");
                exit(EXIT_FAILURE);

        }
	if (out == NULL) {
      		printf("Unable to open file outfile for writing\n");
      		exit(EXIT_FAILURE);
   	}

	for (int i = 1; i <= G->n; i++) {
		moveFront(G->neighbors[i]);
		fprintf(out, "%d : ", i);
		while (index(G->neighbors[i]) != -1) {
			fprintf(out, "%d ", get(G->neighbors[i]));
			moveNext(G->neighbors[i]);
		}
		fprintf(out, "\n");
	}		
}
