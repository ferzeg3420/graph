// List.c
// Fernando Zegada
// Implementation of the list ADT in C.

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "IntList.h"

// structs --------------------------------------------------------------------

// private IntNodeObj type
typedef struct IntNodeObj
{
   int data;
   struct IntNodeObj* next;
   struct IntNodeObj* previous;
} IntNodeObj; 

// private IntNode type
typedef IntNodeObj* IntNode;

// private IntListObj type
typedef struct IntListObj
{
   IntNode front;
   IntNode back;
   IntNode cursor;         
   int length;
   int Index;           
} IntListObj;


// Constructors and Destructors ------------------------------------------------

// newIntNode()
// Returns reference to new IntNode object. Initializes next and data fields.
// Private.
IntNode newIntNode(int data)
{
   IntNode N = malloc(sizeof(IntNodeObj));
   N->data = data;
   N->next = NULL;
   N->previous = NULL;
   return(N);
}

// freeIntNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
// Private.
void freeIntNode(IntNode* pN)
{
   if( pN!=NULL && *pN!=NULL )
   {
      free(*pN);
      *pN = NULL;
   }
}

// newIntList()
// Returns reference to new empty IntList object.
IntList newIntList(void)
{
   IntList L;
   L = malloc(sizeof(IntListObj));
   L->front = L->back = L->cursor = NULL; 
   L->length = 0;
   L->Index = -1;
   
   return(L);
}

// freeIntList()
// Frees all heap memory associated with IntList *pL, and sets *pL to NULL.S
void freeIntList(IntList* pL)
{
   if(pL==NULL && *pL==NULL)
   { 
      printf("IntList Error: calling freeIntList() on NULL list reference.\n");
      exit(1);
   }
   clear(*pL);                                                    
   free(*pL);
   *pL = NULL;
}

// Access functions -----------------------------------------------------------

// IntListLength()
// Returns the length of L.
int IntListLength(IntList L)
{
   if( L==NULL )
   {
      printf("IntList Error: calling length() on NULL list reference.\n");
      exit(1);
   }
   return L->length;
}

// IntListIndex()
// Returns the Index of the cursor.
int IntListIndex(IntList L)
{
     if( L==NULL )
   {
      printf("IntList Error: calling IntListIndex() on NULL list reference.\n");
      exit(1);
   }
   return L->Index;
}

// IntListFront()
// Returns the value at the front of L.
// Pre: list is not empty.
int IntListFront(IntList L)
{
   if( L==NULL )
   {
      printf("IntList Error: calling IntListFront() on NULL IntList"
             " reference.\n");
      exit(1);
   }
   if( IntListLength(L) <= 0 )
   {
      printf("IntList Error: calling IntListFront() on an empty IntList.\n");
      exit(1);
   }
   return(L->front->data);
}

// IntListBack()
// Returns the value at the back of L.
// Pre: list is not empty.
int IntListBack(IntList L)
{
   if( L==NULL )
   {
      printf("IntList Error: calling back() on NULL IntList reference.\n");
      exit(1);
   }
   if( IntListLength(L) <= 0 )
   {
      printf("IntList Error: calling back() on an empty IntList.\n");
      exit(1);
   }
   return(L->back->data);
}

// IntListGet()
// Returns the value of the cursor node.
int IntListGet(IntList L)
{
   if( L==NULL )
   {
      printf("IntList Error: calling get() on NULL IntList reference.\n");
      exit(1);
   }
   if( IntListIndex(L) < 0 )
   {
      printf("IntList Error: calling get() on undefined cursor.\n");
      exit(1);
   }
   return L->cursor->data; 
}

// IntListEquals()
// returns true (1) if A is identical to B, false (0) otherwise
int IntListEquals(IntList A, IntList B)
{
   int eq = 0;
   IntNode N = NULL;
   IntNode M = NULL;

   if( A==NULL || B==NULL )
   {
      printf("IntList Error: calling equals() on NULL list reference.\n");
      exit(1);
   }

   eq = ( A->length == B->length );
   N = A->front;
   M = B->front;
   while( eq && N!=NULL)
   {
      eq = (N->data==M->data);
      N = N->next;
      M = M->next;
   }
   return eq;
} 

// Manipulation procedures ----------------------------------------------------

// IntListClear()
// Resets the list to its original empty state.
void IntListClear(IntList L)
{
   if( L==NULL )
   {
      printf("IntList Error: calling clear() on NULL IntList reference.\n");
      exit(1);
   }
   while( IntListLength(L) > 0 )
   { 
      IntListDeleteFront(L); 
   }
   L->front = L->back = L->cursor = NULL; 
   L->length = 0;
   L->Index = -1; 
}

// IntListMoveFront()
// If IntList is non-empty, places the cursor under the front element, otherwise
// does nothing.
void IntListMoveFront(IntList L)
{
   if( L==NULL )
   {
      printf("IntList Error: calling IntListMoveFront() on NULL"
             " IntList reference.\n");
      exit(1);
   }
   if( IntListLength(L) > 0 )
   {
      L->cursor = L->front;
      L->Index = 0;
   }
}

// IntListMoveBack()
// If IntList is non-empty, places the cursor under the back element, otherwise
// does nothing.
void IntListMoveBack(IntList L)
{
   if( L==NULL )
   {
      printf("IntList Error: calling IntListMoveBack() on NULL IntList"
             " reference.\n");
      exit(1);
   }
   if( IntListLength(L) <= 0 )
   {
      printf("IntList Error: calling IntListMoveBack() on empty IntList.\n");
      exit(1);
   }
   L->cursor = L->back;
   L->Index = L->length - 1;
}

// IntListMovePrev()
// If cursor is defined and not at front, moves cursor one step toward
// front of this IntList, if cursor is defined and at front, cursor becomes
// undefined, if cursor is undefined does nothing.
void IntListMovePrev(IntList L)
{
   if( L==NULL )
   {
      printf("IntList Error: calling IntListMovePrev() on NULL IntList "
             "reference.\n");
      exit(1);
   }
   if( IntListIndex(L) != -1 )
   {
     L->cursor = L->cursor->previous; 
     L->Index = L->Index - 1;
   }
}
  
// IntListMoveNext()
// If cursor is defined and not at back, moves cursor one step toward
// back of this IntList, if cursor is defined and at back, cursor becomes
// undefined, if cursor is undefined does nothing.
void IntListMoveNext(IntList L)
{
   if( L==NULL )
   {
      printf("IntList Error: calling IntListMoveNext() on NULL IntList"
             " reference.\n");
      exit(1);
   }
   if( L->Index == (L->length - 1) )
   {
      L->cursor = NULL;
      L->Index = -1;
   }
   else if( IntListIndex(L) != -1 )
   {
      L->cursor = L->cursor->next; 
      L->Index = L->Index + 1;
   }
}

// IntListPrepend()
// Insert new element into this IntList. If IntList is non-empty,
// insertion takes place before front element.
void IntListPrepend(IntList L, int data) 
{
   if( L==NULL )
   {
      printf("IntList Error: calling IntListPrepend() on NULL IntList"
             " reference.\n");
      exit(1);
   }

   IntNode nodeToPrepend = newIntNode(data);
   
   if( IntListLength(L) <= 0 )
   {
      L->front = L->back = nodeToPrepend;
   }
   else
   {
      nodeToPrepend->next = L->front;
      L->front->previous = nodeToPrepend;
      L->front = nodeToPrepend;
   }
   if( IntListIndex(L) > -1 )
   {
      (L->Index)++;
   }
   (L->length)++; 
}

// IntListAppend()
// Insert new element into this IntList. If IntList is non-empty,
// insertion takes place after back element.
void IntListAppend(IntList L, int data)  
{
   if( L==NULL )
   {
      printf("IntList Error: calling InListAppend() on NULL IntList reference.\n");
      exit(1);
   }

   IntNode nodeToAppend = newIntNode(data); 

   if( IntListLength(L) <= 0)
   {
      L->front = L->back = nodeToAppend;
   }
   else
   {
      nodeToAppend->previous = L->back;
      L->back->next = nodeToAppend;
      L->back = nodeToAppend;
   }
   (L->length)++;
}

// IntListInsertBefore()
// Insert new element before cursor.
// Pre: length()>0, Index() >=0
void IntListInsertBefore(IntList L, int data)
{
   if( L==NULL )
   {
      printf("IntList Error: calling IntListInsertBefore() on NULL IntList"
             " reference.\n");
      exit(1);
   }
   if( IntListLength(L) <= 0 )
   {
      printf("IntList Error: calling IntListInsertBefore() on empty list.\n");
      exit(1);
   }
   if( IntListIndex(L) < 0 )
   {
      printf("IntList Error: calling IntListInsertBefore() on undefined"
             " cursor.\n");
      exit(1);
   }

   IntNode nodeToInsert = newIntNode(data);
   
   if( L->cursor->previous == NULL )
   {
      L->cursor->previous = nodeToInsert;
      nodeToInsert->next = L->cursor;
      L->front = nodeToInsert;
   }
   else
   {
      nodeToInsert->next = L->cursor;
      nodeToInsert->previous = L->cursor->previous;
      L->cursor->previous->next = nodeToInsert;
      L->cursor->previous = nodeToInsert;
   }
   (L->Index)++;
   (L->length)++;
}

// IntListInsertAfter()
// Insert new element after cursor.
// Pre: length()>0, Index() >=0
void IntListInsertAfter(IntList L, int data)
{
   if( L==NULL )
   {
      printf("IntList Error: calling insertAfter() on NULL IntList reference.\n");
      exit(1);
   }
   if( IntListLength(L) <= 0 )
   {
      printf("IntList Error: calling insertAfter() on empty list.\n");
      exit(1);
   }
   if( IntListIndex(L) < 0 )
   {
      printf("IntList Error: calling insertAfter() on undefined cursor.\n");
      exit(1);
   }

   IntNode nodeToInsert = newIntNode(data);
      
   if( L->cursor->next == NULL )
   {
      L->cursor->next = nodeToInsert;
      nodeToInsert->previous = L->cursor;
      L->back = nodeToInsert;
   }
   else
   {
      nodeToInsert->previous = L->cursor;
      nodeToInsert->next = L->cursor->next;
      L->cursor->next->previous = nodeToInsert;
      L->cursor->next = nodeToInsert;
   }
   (L->length)++;
}

// IntListDeleteFront()
// Deletes the front element. Pre: length() > 0
void IntListDeleteFront(IntList L) 
{
   if( L == NULL )
   {
      printf("IntList Error: calling IntListDeleteFront() on NULL IntList reference.\n");
      exit(1);
   }
   if( IntListLength(L) <= 0 )
   {
      printf("IntList Error: calling IntListDeleteFront() on empty list.\n");
      exit(1);
   }
   if( IntListLength(L) == 1 )
   {
      if( IntListIndex(L) == 0 )
      {
         L->cursor = NULL;
         L->Index = - 1;
      }
      freeIntNode(&L->front);
      L->back = L->front = NULL;
   }
   else
   {
      if( IntListIndex(L) != -1 )
      {
         (L->Index)--;
         if( IntListIndex(L) == -1 )
            L->cursor = NULL;
      }
      L->front = L->front->next;
      L->front->previous->next = NULL;
      freeIntNode(&L->front->previous);
      L->front->previous = NULL;
   }
   (L->length)--;
}

// IntListDeleteBack()
// Deletes the back element. Pre: length() > 0
void IntListDeleteBack(IntList L) 
{
   if( L == NULL )
   {
      printf("IntList Error: calling IntListDeleteBack() on NULL IntList reference.\n");
      exit(1);
   }
   if( IntListLength(L) <= 0 )
   {
      printf("IntList Error: calling IntListDeleteBack() on empty list.\n");
      exit(1);
   }
   if( IntListLength(L) == 1 )
   {
      if( IntListIndex(L) == 0 )
      {
         L->cursor = NULL;
         L->Index = -1;
      }
      freeIntNode(&L->front);
      L->back = L->front = NULL;
   }
   else
   {
      if( IntListIndex(L) == (IntListLength(L) - 1) )
      {
         L->Index = -1;
         L->cursor = NULL;
      }
      L->back = L->back->previous;
      L->back->next->previous = NULL;
      freeIntNode(&L->back->next);
      L->back->next = NULL;
   }
   (L->length)--;
}

// IntListDelete()
// Deletes cursor element, making the cursor undefined.
// Pre: length()>0, Index() >= 0
void IntListDelete(IntList L) 
{
   if( L==NULL )
   {
      printf("IntList Error: calling IntListDelete() on NULL IntList reference.\n");
      exit(1);
   }
   if( IntListLength(L) <= 0 )
   {
      printf("IntList Error: calling IntListDelete() on empty list.\n");
      exit(1);
   }
   if( IntListIndex(L) == - 1 )
   {
      printf("IntList Error: calling IntListDelete() on undefined cursor.\n");
      exit(1);
   }
   if( IntListLength(L) == 1 )
   {
      L->front = NULL;
      L->back = NULL;
   }
   else if( IntListIndex(L) == 0 )
   {
      L->front = L->cursor->next;
      L->front->previous = NULL;
      L->cursor->next = NULL;
   }
   else if( IntListIndex(L) == (length(L) - 1) )
   {
      L->back = L->cursor->previous;
      L->back->next = NULL;
      L->cursor->previous = NULL;
   }
   else
   {
      L->cursor->previous->next = L->cursor->next;
      L->cursor->next->previous = L->cursor->previous;
      L->cursor->next = NULL;
      L->cursor->previous = NULL;
   }
   L->Index = -1;
   freeIntNode(&L->cursor);
   L->cursor = NULL;
   (L->length)--;
}

// Other Functions ------------------------------------------------------------

// IntListToString()
// Prints data elements in L to output file.
void intListToString(FILE* out, IntList L)
{
   IntNode N = NULL;
   
   if( L==NULL )
   {
      printf("IntList Error: calling listToString() on NULL IntList reference\n");
      exit(1);
   }
   for(N = L->front; N != NULL; N = N->next)
   {
      fprintf(out, "%d ", N->data);
   }
}

// copyIntList()
// Returns a new list representing the same integer sequence as this IntList.
// The cursor in the new list is undefined, regardless of the state of the
// cursor in this IntList. This IntList is unchanged.
IntList copyIntList(IntList L) 
{
   if( L==NULL )
   {
      printf("IntList Error: calling copyIntList() on NULL IntList reference\n");
      exit(1);
   }
   IntList listCopy = newIntList();
   IntNode traverseIntNode = NULL;              
   traverseIntNode = L->front;

   while( traverseIntNode != NULL )
   {
      IntListAppend(listCopy, traverseIntNode->data); 
      traverseIntNode = traverseIntNode->next;
   }
   freeIntNode(&traverseIntNode);
   return listCopy;
}


// Helper Functions -----------------------------------------------------------
// insertInOrder()
// inserts new nodes in increasing order.
void IntListInsertInOrder(IntList* L, int v)
{
   if( L == NULL || *L == NULL )
   {
      printf("IntList Error: calling InsertInOrder() on "
             "NULL IntList reference or null pointer\n");
      exit(1);
   }
   IntListMoveFront(*L);
   while( IntListIndex(*L) != -1 )
   {
      if( v < get(*L) )
      {
         IntListInsertBefore(*L, v);
         break;
      }
      IntListMoveNext(*L);
   }
  if( IntListIndex(*L) == -1 )
  {
     IntListAppend(*L, v);
  }
}
