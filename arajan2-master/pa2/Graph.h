/**********************************************************************************
* Anya Rajan, arajan2
* 2022 Spring CSE101 PA2 
* Graph.h 
* Graph.h for function prototypes of Graph ADT functions 
* ***********************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include "List.h"
#define INF -1
#define NIL 1
#define w 2
#define g 3
#define b 4

// define macros here to pass checks

// Structs --------------------------------------------------------------------------------------------
typedef struct GraphObj* Graph;

// Constructors-Destructors  --------------------------------------------------------------------------
Graph newGraph(int n);
void freeGraph(Graph* pG);

// Access Functions -----------------------------------------------------------------------------------
int getOrder(Graph G);
int getSize(Graph G);
int getSource(Graph G);
int getParent(Graph G, int u);
int getDist(Graph G, int u);
void getPath(List L, Graph G, int u);

// Manipulation Procedures ----------------------------------------------------------------------------
void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void BFS(Graph G, int s);

// Other Operations -----------------------------------------------------------------------------------
void printGraph(FILE* out, Graph G);
