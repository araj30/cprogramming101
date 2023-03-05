/* **********************************************************************************
* Anya Rajan, arajan2
* 2022 Spring CSE101 PA3 
* Graph.c 
* Graph.c to define Graph ADT functions 
***********************************************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "Graph.h"
#include "List.h"
int time = 0;

// structs ----------------------------------------------------------------------- 
// private GraphObj type
typedef struct GraphObj {
        int order;
        int size;
	// int time;
        List *neighbors;
        char *colors;
        int *parents;
        int *finish;
	int *discover;
} GraphObj;

// constructors-destructors ------------------------------------------------------
// newGraph()
// Initializes all the variables and arrays associated with a Graph.
// Allocates memory for these elements.
// Returns a new Graph G.
Graph newGraph(int n) {
        Graph G = malloc(sizeof(GraphObj));
        G->order = n;
        G->size = 0;
        G->neighbors = calloc(n+1, sizeof(List));
        G->colors = calloc(n+1, sizeof(int));
        G->parents = calloc(n+1, sizeof(int));
        G->discover = calloc(n+1, sizeof(int));
	G->finish = calloc(n+1, sizeof(int));
        G->neighbors[0] = NULL;
        for (int i = 1; i <= n; i++) {
                G->neighbors[i] = newList();
                G->colors[i] = w;
                G->parents[i] = NIL;
                G->finish[i] = UNDEF;
		G->discover[i] = UNDEF;
        }
	// G->time = 0;
        return(G);
}

// freeGraph()
// Frees all memory associated with the Graph passed in.
void freeGraph(Graph* pG) {
        if (*pG == NULL || pG == NULL) {
                printf("Graph Error: calling freeGraph on NULL Graph reference\n");
                exit(EXIT_FAILURE);
        }

        // makeNull(*pG);
        for (int i = 1; i <= (*pG)->order; i++) {
                freeList(&(*pG)->neighbors[i]);
		(*pG)->neighbors[i] = NULL;
        }

        free((*pG)->neighbors);
        free((*pG)->colors);
        free((*pG)->parents);
        free((*pG)->finish);
	free((*pG)->discover);

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
        return G->order;
}

// getSize()
//  pre: check is Graph G is NULL. if it is, throw an error. otherwise, continue.
//  return the sizse of G
int getSize(Graph G) {
        if (G == NULL) {
                printf("Graph Error: calling getSize() on NULL Graph\n");
                exit(EXIT_FAILURE);

        }
        return G->size;
}

// getParent()
// pre: check is Graph G is NULL. if it is, throw an error. otherwise, continue.
// pre: 1<=u<=n=getOrder(G)
int getParent(Graph G, int u) {
        if (G == NULL) {
                printf("Graph Error: calling getParent() on NULL Graph\n");
                exit(EXIT_FAILURE);

        }
        //if (getSource(G) == NIL) {
        //        return NIL;
        //}
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

// getDiscover()
// pre: check is Graph G is NULL. if it is, throw an error. otherwise, continue.
// pre: 1<=u<=n=getOrder(G)
int getDiscover(Graph G, int u) {
	if (G == NULL) {
                printf("Graph Error: calling getDiscover() on NULL Graph\n");
                exit(EXIT_FAILURE);

        }
	if (u < 1) {
                printf("Graph Error: calling getDiscover() on u that is greater than or equal to 0\n");
                exit(EXIT_FAILURE);
        }
        if (getOrder(G) < u) {
                printf("Graph Error: calling getDiscover() on u less than or equal to order of G\n");
                exit(EXIT_FAILURE);
        }
	
	return G->discover[u];
}

// getFinish()
// pre: check is Graph G is NULL. if it is, throw an error. otherwise, continue.
// pre: 1<=u<=n=getOrder(G)
int getFinish(Graph G, int u) {
	if (G == NULL) {
                printf("Graph Error: calling getFinish() on NULL Graph\n");
                exit(EXIT_FAILURE);

        }
        if (u < 1) {
                printf("Graph Error: calling getFinish() on u that is greater than or equal to 0\n");
                exit(EXIT_FAILURE);
        }
        if (getOrder(G) < u) {
                printf("Graph Error: calling getFinish() on u less than or equal to order of G\n");
                exit(EXIT_FAILURE);
        }

        return G->finish[u];
}

// manipulation procedures ------------------------------------------------------------

// pre: 1<=u<=n, 1<=v<=n
// pre: G is not NULL
void addArc(Graph G, int u, int v) {
	if (G == NULL) {
                printf("Graph Error: calling addArc() on NULL Graph\n");
                exit(EXIT_FAILURE);
        }
        if (u < 1) {
                printf("Graph Error: calling addArc on u that is less than 1\n");
                exit(EXIT_FAILURE);
        }
        if (u > getOrder(G)) {
                printf("Graph Error: calling addArc on u that is greater than getOrder(G)\n");
                exit(EXIT_FAILURE);
        }
        if (v < 1) {
                printf("Graph Error: calling addArc on v that is less than 1\n");
                exit(EXIT_FAILURE);
        }
        if (v > getOrder(G)) {
                printf("Graph Error: calling addArc on v that is greater than getOrder(G)\n");
                exit(EXIT_FAILURE);
        }
        if (length(G->neighbors[u]) == 0) {
                append(G->neighbors[u], v);
                G->size += 1;
                return;
        }
	// help from Raj, the course tutor
	if (v < front(G->neighbors[u])) {
		prepend(G->neighbors[u], v);
		G->size += 1;
		return;
	}
	if (v > back(G->neighbors[u])) {
		append(G->neighbors[u], v);
		G->size += 1;
		return;
	}

	moveFront(G->neighbors[u]);
        while (index(G->neighbors[u]) != -1) {
                if (get(G->neighbors[u]) > v) {
			insertBefore(G->neighbors[u], v);
			G->size += 1;
                }
                else if (get(G->neighbors[u]) == v) {
                        break;
                }
		moveNext(G->neighbors[u]);
         }

}

// addEdge()
// pre: 1<=u<=n, 1<=v<=n
// pre: G is not NULL
void addEdge (Graph G, int u, int v) {
	if (G == NULL) {
                printf("Graph Error: calling addEdge() on NULL Graph\n");
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

// visit()
// pre?
void visit(List L, Graph G, int x) {
	// PSEUDO FOR THIS FUNCTION PROVIDED BY PATRICK TANTALO
	time += 1;
	G->discover[x] = time;
	G->colors[x] = g;
	moveFront(G->neighbors[x]);
	while (index(G->neighbors[x]) != -1) {
		int y = get(G->neighbors[x]);
		if (G->colors[y] == w) {
			//if (x == 1) {
			//	G->parents[y] = 0;
			//	visit(L, G, y);
				
			//}
			//else { 
				G->parents[y] = x;
				visit(L, G,  y);
			//}
			
		}
		moveNext(G->neighbors[x]);				
	}
	G->colors[x] = b;
	time += 1;
	G->finish[x] = time;
	prepend(L, x);
	
}

// DFS()
// pre: check is Graph G is NULL. if it is, throw an error. otherwise, continue.
// length(S)==getOrder(G)
void DFS (Graph G, List S) {
	if (G == NULL) {
                printf("Graph Error: calling DFS() on NULL Graph\n");
                exit(EXIT_FAILURE);

        }
	if (length(S) != getOrder(G)) {
		printf("Graph Error: calling DFS() on List S that's length isn't equal to order of G");
	}
	// PSEUDO FOR THIS FUNCTION PROVIDED BY PATRICK TANTALO	
	for (int i = 1; i <= getOrder(G); i++) {
		G->colors[i] = w;
		G->parents[i] = NIL;
	}
	time = 0;
	int p;
	// int *point = &time;
	// clear(S);
	moveFront(S);
	while (index(S) != -1) {
		p = get(S);
		if (G->colors[p] == w) {
			visit(S, G, p);
		}
		moveNext(S);
	}
	
	for (int x = 0; x < getOrder(G); x++) {
		deleteBack(S);
	}
}

// other operations -------------------------------------------------------------------

// transpose()
// pre: check for null
Graph transpose(Graph G) {
	if (G == NULL) {
                printf("Graph Error: calling transpose() on NULL Graph\n");
                exit(EXIT_FAILURE);

        }
	Graph new = newGraph(G->order);
	for (int i = 1; i <=  getOrder(G); i++) {
		if (length(G->neighbors[i]) != 0) {
				moveFront(G->neighbors[i]);
				while(index(G->neighbors[i]) != -1) {
					int y = get(G->neighbors[i]);
					addArc(new, y, i);
					moveNext(G->neighbors[i]);
				}
		}
	}
	return new;
	
}
// copyGraph()
// pre: check for null
Graph copyGraph(Graph G) {
	if (G == NULL) {
                printf("Graph Error: calling copyGraph() on NULL Graph\n");
                exit(EXIT_FAILURE);

        }
        Graph new = newGraph(G->order);
        for (int i = 1; i <= getOrder(G); i++) {
                if (length(G->neighbors[i]) != 0) {
                                moveFront(G->neighbors[i]);
                                while(index(G->neighbors[i]) != -1) {
                                        int y = get(G->neighbors[i]);
                                        addArc(new, i, y);
                                        moveNext(G->neighbors[i]);
                                }
                }
        }
        return new;

}

// printGraph()
// pre: check for null
void printGraph(FILE* out, Graph G) {
        if (G == NULL) {
                printf("Graph Error: calling printGraph() on NULL Graph\n");
                exit(EXIT_FAILURE);

        }
        if (out == NULL) {
                printf("Unable to open file outfile for writing\n");
                exit(EXIT_FAILURE);
        }

        for (int i = 1; i <= G->order; i++) {
                moveFront(G->neighbors[i]);
                fprintf(out, "%d : ", i);
                while (index(G->neighbors[i]) != -1) {
                        fprintf(out, "%d ", get(G->neighbors[i]));
                        moveNext(G->neighbors[i]);
                }
                fprintf(out, "\n");
        }
}
