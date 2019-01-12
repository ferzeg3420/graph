//-----------------------------------------------------------------------------
// GraphClient.c
// Test client for the Graph ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include"IntList.h"
#include"Graph.h"
#include"Matrix.h"

int main(int argc, char* argv[])
{
   Graph A = newGraph(4);
   Graph B = newGraph(6);
   Graph C = NULL;
   Graph D = newGraph(5);

   IntList path = newIntList();
   
   printf("Testing Graph A\n");
   addEdge(A, 1, 2);
   addEdge(A, 2, 3);
   addEdge(A, 3, 4);
   addEdge(A, 4, 1);

   printf("\nThe size of Graph A is: %d\n\n", getGraphSize(A));
   printf("The order of Graph A is: %d\n\n", getGraphOrder(A));

   graphToString(stdout, A);                               
   for( int i = 1; i <= getGraphOrder(A); i++ )
   {
      moveFront(path);
      printf("\n\nRunning BFS() with source %d\n", i);
      BFS(A, i);

      for( int j = 1; j <= getGraphOrder(A); j++ )
      {
         printf("vector: %d, distance: %d, parent: %d.\n",
                 j, getDist(A, j), getParent(A, j) );
      }
      
      for( int k = 1; k <= getGraphOrder(A); k++ )
      {
         printf("The path from vertex %d to vertex %d is: ", i, k);
         getPath(path, A, k);
         intListToString(stdout, path);
         printf("\n");
      }
   }
   
   // Graph B
   printf("\n\nTesting Graph B\n");
   addEdge(B, 1, 2);
   addEdge(B, 1, 3);

   addEdge(B, 2, 4);
   addEdge(B, 2, 5);
   addEdge(B, 2, 6);

   addEdge(B, 3, 4);
   addEdge(B, 4, 5);
   addEdge(B, 5, 6);

   printf("The size of Graph B is: %d\n", getGraphSize(B));
   printf("The order of Graph B is: %d\n", getGraphOrder(B));

   graphToString(stdout, B);                              

   for( int i = 1; i <= getGraphOrder(B); i++ )
   {
      BFS(B, i);
      printf("\n\nRunning BFS() with source %d\n", i);

      for( int j = 1; j <= getGraphOrder(B); j++ )
      {
         printf("vector: %d, distance: %d, parent: %d.\n",
                 j, getDist(B, j), getParent(B, j) );
      }
      
      for( int k = 1; k <= getGraphOrder(B); k++ )
      {
         printf("The path from vertex %d to vertex %d is: ", i, k);
         getPath(path, B, k);
         intListToString(stdout, path);
         printf("\n");
         clear(path);
      }
   }

   // Graph D (directed)
   printf("\n\nTesting Graph D\n");
   addArc(D, 1, 4);
   addArc(D, 1, 5);

   addArc(D, 2, 1);
   addArc(D, 2, 5);

   addArc(D, 3, 2);
   addArc(D, 3, 5);

   addArc(D, 5, 4);

   printf("The size of Graph D is: %d\n", getGraphSize(D));
   printf("The order of Graph D is: %d\n", getGraphOrder(D));

   graphToString(stdout, D);                              

   for( int i = 1; i <= getGraphOrder(D); i++ )
   {
      BFS(D, i);
      printf("\n\nRunning BFS() with source %d\n", i);

      for( int j = 1; j <= getGraphOrder(D); j++ )
      {
         printf("vector: %d, distance: %d, parent: %d.\n",
                 j, getDist(D, j), getParent(D, j) );
      }
      
      for( int k = 1; k <= getGraphOrder(D); k++ )
      {
         printf("The path from vertex %d to vertex %d is: ", i, k);
         getPath(path, D, k);
         intListToString(stdout, path);
         printf("\n");
         clear(path);
      }
   }
   
   printf("Before makeNull():\n");
   printf("The size of Graph A is: %d\n", getGraphSize(A));
   graphToString(stdout, A);                              

   makeNull(A);
   printf("After makeNull():\n");
   printf("The size of Graph A is: %d\n", getGraphSize(A));
   graphToString(stdout, A);                              

   printf("Running makeNull() again:\n");
   makeNull(A);
   printf("The size of Graph A is: %d\n", getGraphSize(A));
   graphToString(stdout, A);                              

   freeGraph(&A);
   freeGraph(&B);
   freeGraph(&D);
   freeIntList(&path);

   return(0);
}

/*
  int i, n=8;
  IntList S = newIntList();
  Graph G = newGraph(n);
  Graph T=NULL, C=NULL;

  for(i=1; i<=n; i++) append(S, i);

  addArc(G, 1,2);
  addArc(G, 1,5);
  addArc(G, 2,5);
  addArc(G, 2,6);
  addArc(G, 3,2);
  addArc(G, 3,4);
  addArc(G, 3,6);
  addArc(G, 3,7);
  addArc(G, 3,8);
  addArc(G, 6,5);
  addArc(G, 6,7);
  addArc(G, 8,4);
  addArc(G, 8,7);
  graphToString(stdout, G);

  DFS(G, S);
  fprintf(stdout, "\n");
  fprintf(stdout, "x:  d  f  p\n");
  for(i=1; i<=n; i++){
    fprintf(stdout, "%d: %2d %2d %2d\n",
	    i, getDiscover(G, i), getFinish(G, i), getParent(G, i));
  }
  fprintf(stdout, "\n");
  intListToString(stdout, S);
  fprintf(stdout, "\n");

  T = transpose(G);
  C = copyGraph(G);
  fprintf(stdout, "\n");
  graphToString(stdout, C);
  fprintf(stdout, "\n");
  graphToString(stdout, T);
  fprintf(stdout, "\n");

  DFS(T, S);
  fprintf(stdout, "\n");
  fprintf(stdout, "x:  d  f  p\n");
  for(i=1; i<=n; i++){
    fprintf(stdout, "%d: %2d %2d %2d\n",
	    i, getDiscover(T, i), getFinish(T, i), getParent(T, i));
  }
  fprintf(stdout, "\n");
  intListToString(stdout, S);
  fprintf(stdout, "\n");

  freeList(&S);
  freeGraph(&G);
  freeGraph(&T);
  freeGraph(&C);
  return(0);
 */
