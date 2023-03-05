/* ***********************************************************************************
* Anya Rajan, arajan2
* 2022 Spring CSE101 PA3 
* Graph.h 
* Graph.h for function prototypes of Graph ADT functions 
* ***********************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include "List.h"
#define NIL 0
#define UNDEF -1
#define w 2
#define g 3
#define b 4

// Structs --------------------------------------------------------------------------------------------
typedef struct GraphObj* Graph;

// Constructors-Destructors  --------------------------------------------------------------------------
Graph newGraph(int n);
void freeGraph(Graph* pG);

// Access functions -----------------------------------------------------------------------------------
int getOrder(Graph G);
int getSize(Graph G);
int getParent(Graph G, int u);
int getDiscover(Graph G, int u);
int getFinish(Graph G, int u); 

// Manipulation procedures ----------------------------------------------------------------------------
void addArc(Graph G, int u, int v); 
void addEdge(Graph G, int u, int v); 
void DFS(Graph G, List S);

// Other Functions ------------------------------------------------------------------------------------
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE* out , Graph G);
