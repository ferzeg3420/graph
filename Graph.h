// Graph.h
// Fernando Zegada
// fzegadar
// Implementation of the Graph ADT in C.

#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_
#include<stdio.h>
#include "List.h"
#define NIL  0
#define INF  -2
typedef struct GraphObj* Graph;

// Constructors-Destructors ---------------------------------------------------

// newGraph()
// Returns a graph pointing to an empty GraphObj with n vertices and no edges.
Graph newGraph(int n);

// freeGraph()
// Frees all heap memory associated with graph. Sets *pG to NULL.
void freeGraph(Graph* pG);

// Access functions -----------------------------------------------------------

// getOrder()
// Returns the order of the graph (number of vertices).
int getOrder(Graph G);

// getSize()
// Returns the size of the graph (the number of edges).
int getSize(Graph G);

// getSource()
// Returns the vertex that was most recently the source of BFS() or NIL
// if BFS() has never been called.
int getSource(Graph G);

// getParent()
// Returns the parent of the vertex generated when running BFS() or NIL.
// if BFS() has never been called.
// Precondition: 1<= u < order of the graph.
int getParent(Graph G, int u);

// getDist()
// returns the distance from the source to the input vertex. Returns INF
// if BFS() has never been called.
// Precondition: 1<= u < order of the graph.
int getDist(Graph G, int u);

// getPath()
// Appends to the List L the vertices of the shortest path in G from 
// source to u. Appends to L the value of NIL if no such path exists.
// Precondition: getSource(G) != NIL.
// Precondition: 1<= u < order of the graph.
void getPath(List L, Graph G, int u);

// Manipulation procedures ----------------------------------------------------

// makeNull()
// Deletes all the edges of G, restoring it to its original no edges state.
void makeNull(Graph G);

// addEdge()
// Inserts a new edge to the graph by changing the adjacency lists. Increasing
// order is maintained.
// Precondtiion: both int arguments must be between 1 and the size of the graph.
void addEdge(Graph G, int u, int v);

// addArc()
// Inserts a directed edge to the graph. Increasing order is be maintained.
// Precondtiion: both int arguments must be between 1 and the size of the graph.
void addArc(Graph G, int u, int v);

// BFS()
// Implements the breadth first search algorithm.
// precondition source is not out of bounds.
void BFS(Graph G, int s);

// Other Functions ------------------------------------------------------------

// dijkstrasAlgorithm()
// Finds the minimumal path from the source to any vector reachable from it.
//void djikstrasAlgorithm(Graph G, int source);

// initialize()
// Initializes all vertices in G to a state that's ideal for path algorithms.
void initialize(Graph G, int source);

// relax()
// If the new path from vertex x to y is shorter than the previous recorded
// path change the distance reported by vertex Y.
void relax(Heap H, Graph G, int vertexX, int vertexY);

// printGraph()
// Prints the adjacency list representation of the graph.
void printGraph(FILE* out, Graph G);

#endif
