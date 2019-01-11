/* ------------------------------------------------------------------------TODO

-- Change the names of functions in EntryList to reflect his change of name. 
Maybe change the names of functions like Index to intListIndex or 
entryListIndex.

-- Change the #includes in Matrix.h, Heap.h, Graph.h to reflect the change of
names in List.h.

-- Chage the #includes in the .c files of the ADTs listed in the previous 
entry of my todo queue.

-- Test all the heap, matrix, list, and Matrix versions in all my files to
 make sure they work.

-- Study heap, matrix and graph.

-----------------------------------------------------------------------------*/

// Graph.c
// Fernando Zegada
// Implementation of the Graph ADT in C.

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <stdbool.h>
#include "Graph.h"
#include "Heap.h"
#include "List.h"
#include "Matrix.h"
//#define NIL 0
//#define INF -2 // -2 to not get confused with the undefined index of a list.

// structs --------------------------------------------------------------------

typedef struct GraphObj
{
   int order;
   int size;
   int source;

   List* neighbors;
   bool* beenVisited;
   int* parents;
   int* distance;

} GraphObj;

// Constructors-Destructors ---------------------------------------------------

// newGraph()
// Returns a graph pointing to an empty GraphObj with n vertices and no edges.
Graph newGraph(int n)
{
   Graph G;
   G = malloc(sizeof(GraphObj));
   G->order = n; 
   G->size = 0;
   G->source = NIL;
   G->neighbors = (List *)malloc( (n + 1) * sizeof(List) );
   G->beenVisited = (bool *)malloc( (n + 1) * sizeof(bool) ); 
   G->parents = (int *)malloc( (n + 1) * sizeof(int) );
   G->distance = (int *)malloc( (n + 1) * sizeof(int) );

   for( int i = 0; i <= n; i++ )
   {
      G->neighbors[i] = newList();
      G->beenVisited[i] = false;
      G->parents[i] = NIL;
      G->distance[i] = INF;
   }
   return(G);
}

// freeGraph()
// Frees all heap memory associated with graph. Sets *pG to NULL.
void freeGraph(Graph* pG)
{
   if(pG==NULL && *pG==NULL)
   { 
      printf("Graph Error: calling freeGraph() on NULL Graph reference.\n");
      exit(1);
   }
   int n =  getGraphOrder(*pG);

   for( int i = 0; i <= n; i++ )
   {
      freeList( &((*pG)->neighbors[i]) );
   }

   free( (*pG)->beenVisited );
   free( (*pG)->parents );
   free( (*pG)->distance );
   free( (*pG)->neighbors );

   (*pG)->size = 0;
   free(*pG);
   *pG = NULL;
}

// Access functions -----------------------------------------------------------

// getGraphOrder()
// Returns the order of the graph (number of vertices).
int getGraphOrder(Graph G)
{
   if( G==NULL )
   {
      printf("Graph Error: calling getGraphOrder() on NULL Graph reference.\n");
      exit(1);
   }
   return G->order;
}

// getGraphSize()
// Returns the size of the graph (the number of edges).
int getGraphSize(Graph G)
{
   if( G==NULL )
   {
      printf("Graph Error: calling getGraphSize() on NULL Graph reference.\n");
      exit(1);
   }
   return G->size;
}

// getSource()
// Returns the vertex that was most recently the source of BFS() or NIL
// if BFS() has never been called.
int getSource(Graph G)
{
   if( G==NULL )
   {
      printf("Graph Error: calling getSource() on NULL Graph reference.\n");
      exit(1);
   }
   return G->source;
}

// getParent()
// Returns the parent of the vertex generated when running BFS() or NIL.
// if BFS() has never been called.
// Precondition: 1<= u < order of the graph.
int getParent(Graph G, int u)
{
   if( G==NULL )
   {
      printf("Graph Error: calling getParent() on NULL Graph reference.\n");
      exit(1);
   }
   if( u <= 0 || getGraphOrder(G) < u)
   {
      printf("Graph Error: calling getParent() for an out of bounds vertex.\n");
      exit(1);
   }
   return G->parents[u];
}

// getDist()
// returns the distance from the source to the input vertex. Returns INF
// if BFS() has never been called.
// Precondition: 1<= u < order of the graph.
int getDist(Graph G, int u)
{
   if( G==NULL )
   {
      printf("Graph Error: calling getDist() on NULL Graph reference.\n");
      exit(1);
   }
   if( u <= 0 || getGraphOrder(G) < u)
   {
      printf("Graph Error: calling getDist() for an out of bounds vertex.\n");
      exit(1);
   }
   return G->distance[u];
}

// getPath()
// Appends to the List L the vertices of the shortest path in G from 
// source to u. Appends to L the value of NIL if no such path exists.
// Precondition: getSource(G) != NIL.
// Precondition: 1<= u < order of the graph.
void getPath(List L, Graph G, int u)
{
   if( G==NULL )
   {
      printf("Graph Error: calling getPath() on NULL Graph reference.\n");
      exit(1);
   }
   if( getSource(G) == 0 )
   {
      printf("Graph Error: In getPath(), undefined source, \n"
             "BFS() has never been called.\n");
      exit(1);
   }
   if( u <= 0 || getGraphOrder(G) < u)
   {
      printf("Graph Error: calling BFS() with an out of bounds source.\n");
      exit(1);
   }
   if (G->parents[u] == 0 && G->source != u)
   {
     append(L, NIL);
     return;
   }
   append(L, u);
   int v = G->parents[u];
   
   moveBack(L);
   while( v != NIL )
   {
      insertBefore(L, v);
      movePrev(L);
      v = G->parents[v];
   }
}

// Manipulation procedures ----------------------------------------------------

// makeNull()
// Deletes all the edges of G, restoring it to its original no edges state.
void makeNull(Graph G)
{
   if( G==NULL )
   {
      printf("Graph Error: calling makeNull() on NULL Graph reference.\n");
      exit(1);
   }
   for( int i = 1; i <= getGraphSize(G); i++ )
   {
      clear( G->neighbors[i] );
   }
   G->size = 0;
}

// addEdge()
// Inserts a new edge to the graph by changing the adjacency lists. Increasing
// order is maintained.
// Precondtiion: both int arguments must be between 1 and the size of the graph.
void addEdge(Graph G, int u, int v)
{
   if( G==NULL )
   {
      printf("Graph Error: calling addEdge() on NULL Graph reference.\n");
      exit(1);
   }
   if( u <= 0 || getGraphOrder(G) < u || v <= 0 || getGraphOrder(G) < v )
   {
      printf("Graph Error: calling addEdge() for (an) out of bounds\n"
             "vertex (or vertices).\n");
      exit(1);
   }
   insertInOrder( &(G->neighbors[u]), v );
   insertInOrder( &(G->neighbors[v]), u );
   (G->size)++;
}

// addArc()
// Inserts a directed edge to the graph. Increasing order is be maintained.
// Precondtiion: both int arguments must be between 1 and the size of the graph.
void addArc(Graph G, int u, int v)
{
   if( G==NULL )
   {
      printf("Graph Error: calling addArc() on NULL Graph reference.\n");
      exit(1);
   }
   if( u <= 0 || getGraphOrder(G) < u || v <= 0 || getGraphOrder(G) < v )
   {
      printf("Graph Error: calling addArc() for (an) out of bounds"
             "vertex (or vertices).\n");
      exit(1);
   }
   insertInOrder( &(G->neighbors[u]), v );
   (G->size)++;
}

// BFS()  // NOT WORKING IN THIS IMPLEMENTATION!
// Implements the breadth first search algorithm.
// precondition source is not out of bounds.
void BFS(Graph G, int s)
{
   if( G==NULL )
   {
      printf("Graph Error: calling BFS() on NULL Graph reference.\n");
      exit(1);
   }
   if( s <= 0 || getGraphOrder(G) < s)
   {
      printf("Graph Error: calling BFS() with an out of bounds source.\n");
      exit(1);
   }
   List Q = newList();
   List * workingAdjList;
   int v = 0, u = 0;

   G->source = s;
   
   for( int i = 1; i <= getGraphOrder(G); i++ )
   {
      G->beenVisited[i] = false;
      G->distance[i] = INF;
      G->parents[i] = NIL;
   }
   G->beenVisited[s] = true;
   G->distance[s] = 0;

   append(Q, s);

   while( length(Q) != 0 )
   {
      u = front(Q);
      deleteFront(Q);
   
      workingAdjList = &(G->neighbors[u]);
      for
      ( moveFront(*workingAdjList);
        Index(*workingAdjList) != -1;
        moveNext(*workingAdjList)
      ){
         v = get(*workingAdjList);
         if( !(G->beenVisited[v]) )
         {
            G->beenVisited[v] = true;
            G->distance[v] = G->distance[u] + 1;
            G->parents[v] = u;
            append(Q, v);
         }
      }
   }
   freeList(&Q);
}  // PROBABLY NOT WORKING IN THIS IMPLEMENTATION!

// Other Functions ------------------------------------------------------------

// graphToString()
// writes the a representation of the graph to an input file
void graphToString(FILE* out, Graph G) // change to graphToString().
{
   if( G==NULL )
   {
      printf("Graph Error: calling printGraph() on NULL Graph reference.\n");
      exit(1);
   }
   for(int i = 1; i <= getOrder(G); i++ )
   { 
      fprintf( out, "%d: ",i); 
      printList(out,  G->neighbors[i]);
      fprintf(out, "\n"); 
   }
}

// Shortest path algorithms and helper functions ------------------------------ 

// dijkstrasAlgorithm()
// Finds the minimumal path from the source to any vector reachable from it.
void djikstrasAlgorithm(Graph G, Matrix weights, int source)
{
   initialize(G, source);
   List visited = newList();
   Heap heap = newHeap( G->order, &(G->distance) );
   int x, y;
   while( !isEmpty(heap) )
   {
      x = extractMin(heap);

      for( moveFront(G->neighbors[x]);
           Index(G->neighbors[x]) != -1;
           moveNext(G->neighbors[x]) )
      {
         y = get(G->neighbors[x]);
         relax(heap, G, weights, x, y);
      }
   }
}

// initialize()
// Initializes all vertices in G to a state that's ideal for path algorithms.
void initialize(Graph G, int source)
{
  for( int i = 1; i <= G->order; i++)
  {
    G->distance[i] = INF;
    G->parents[i] = NIL;
  }
  G->distance[source] = 0;
}

// relax()
// If the new path from vertex x to y is shorter than the previous recorded
// path change the distance reported by vertex Y.
void relax(Heap H, Graph G, Matrix weights, int vertexX, int vertexY)
{
   int newDistance = G->distance[vertexX] + getweights(G, vertexX, vertexY);
   if( G->distance[vertexY] > newDistance )
   {
      G->parents[vertexY] = vertexX;
      G->distance[vertexY] = newDistance;
      decreaseKey(H, vertexY, newDistance);
   }
}
