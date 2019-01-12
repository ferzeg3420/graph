// EntryList.c
// Fernando Zegada
// Implementation of the list ADT in C.

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "EntryList.h"

// structs --------------------------------------------------------------------

// private NodeObj type
typedef struct NodeObj
{
   Entry data;
   struct NodeObj* next;
   struct NodeObj* previous;
} NodeObj; 

// private Node type
typedef NodeObj* Node;

// private ListObj type
typedef struct ListObj
{
   Node front;
   Node back;
   Node cursor;         
   int length;
   int Index;           
} ListObj;


// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
// Private.
Node newNode(Entry data)
{
   Node N = malloc(sizeof(NodeObj));
   N->data = data;
   N->next = NULL;
   N->previous = NULL;
   return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
// Private.
void freeNode(Node* pN)
{
   if( pN!=NULL && *pN!=NULL )
   {
      free(*pN);
      *pN = NULL;
   }
}

// newList()
// Returns reference to new empty List object.
List newList(void)
{
   List L;
   L = malloc(sizeof(ListObj));
   L->front = L->back = L->cursor = NULL; 
   L->length = 0;
   L->Index = -1;
   
   return(L);
}


// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.S
void freeList(List* pL)
{
   if(pL==NULL && *pL==NULL)
   { 
      printf("List Error: calling freeList() on NULL list reference.\n");
      exit(1);
   }
   clear(*pL);                                                    
   free(*pL);
   *pL = NULL;
}

// Access functions -----------------------------------------------------------

// length()
// Returns the length of L.
int length(List L)
{
   if( L==NULL )
   {
      printf("List Error: calling length() on NULL list reference.\n");
      exit(1);
   }
   return(L->length);
}

// Index()
// Returns the Index of the cursor.
int Index(List L)
{
     if( L==NULL )
   {
      printf("List Error: calling Index() on NULL list reference.\n");
      exit(1);
   }
   return L->Index;
}

// front()
// Returns the value at the front of L.
// Pre: list is not empty.
Entry front(List L)
{
   if( L==NULL )
   {
      printf("List Error: calling front() on NULL List reference.\n");
      exit(1);
   }
   if( length(L) <= 0 )
   {
      printf("List Error: calling front() on an empty List.\n");
      exit(1);
   }
   return(L->front->data);
}

// back()
// Returns the value at the back of L.
// Pre: list is not empty.
Entry back(List L)
{
   if( L==NULL )
   {
      printf("List Error: calling back() on NULL List reference.\n");
      exit(1);
   }
   if( length(L) <= 0 )
   {
      printf("List Error: calling back() on an empty List.\n");
      exit(1);
   }
   return(L->back->data);
}

// get()
// Returns the value of the cursor node.
Entry get(List L)
{
   if( L==NULL )
   {
      printf("List Error: calling get() on NULL List reference.\n");
      exit(1);
   }
   if( Index(L) < 0 )
   {
      printf("List Error: calling get() on undefined cursor.\n");
      exit(1);
   }
   return L->cursor->data; 
}

// areListEquals()
// returns true (1) if List A and B have the same values, false (0) otherwise.
bool areListsEqual(List A, List B)
{
   bool eq = false;
   Node N = NULL;
   Node M = NULL;

   if( A==NULL || B==NULL )
   {
      printf("List Error: calling equals() on NULL list reference.\n");
      exit(1);
   }

   eq = ( A->length == B->length );
   N = A->front;
   M = B->front;
   while( eq && N!=NULL)
   {
      eq = areEntriesEqual(N->data, M->data);
      N = N->next;
      M = M->next;
   }
   return eq;
} 

// Manipulation procedures ----------------------------------------------------


// clear()
// Resets the list to its original empty state.
void clear(List L)
{
  //  printf("ping from Clear():");  //debug
   if( L==NULL )
   {
      printf("List Error: calling clear() on NULL List reference.\n");
      exit(1);
   }
   while( length(L) > 0 )
   { 
      deleteFront(L); 
   }
   L->front = L->back = L->cursor = NULL; 
   L->length = 0;
   L->Index = -1; 
}

// moveFront()
// If List is non-empty, places the cursor under the front element, otherwise
// does nothing.
void moveFront(List L)
{
   if( L==NULL )
   {
      printf("List Error: calling moveFront() on NULL List reference.\n");
      exit(1);
   }
   if( length(L) > 0 )
   {
      L->cursor = L->front;
      L->Index = 0;
   }
}

// moveBack()
// If List is non-empty, places the cursor under the back element, otherwise
// does nothing.
void moveBack(List L)
{
   if( L==NULL )
   {
      printf("List Error: calling moveBack() on NULL List reference.\n");
      exit(1);
   }
   if( length(L) <= 0 )
   {
      printf("List Error: calling moveBack() on empty List.\n");
      exit(1);
   }
   L->cursor = L->back;
   L->Index = L->length - 1;
}

// movePrev()
// If cursor is defined and not at front, moves cursor one step toward
// front of this List, if cursor is defined and at front, cursor becomes
// undefined, if cursor is undefined does nothing.
void movePrev(List L)
{
   if( L==NULL )
   {
      printf("List Error: calling movePrev() on NULL List reference.\n");
      exit(1);
   }
   if( Index(L) != -1 )
   {
     L->cursor = L->cursor->previous; 
     L->Index = L->Index - 1;
   }
}
  
// moveNext()
// If cursor is defined and not at back, moves cursor one step toward
// back of this List, if cursor is defined and at back, cursor becomes
// undefined, if cursor is undefined does nothing.
void moveNext(List L)
{
   if( L==NULL )
   {
      printf("List Error: calling moveNext() on NULL List reference.\n");
      exit(1);
   }
   if( L->Index == (L->length - 1) )
   {
      L->cursor = NULL;
      L->Index = -1;
   }
   else if( Index(L) != -1 )
   {
      L->cursor = L->cursor->next; 
      L->Index = L->Index + 1;
   }
}

// prepend()
// Insert new element into this List. If List is non-empty,
// insertion takes place before front element.
void prepend(List L, Entry data) 
{
   if( L==NULL )
   {
      printf("List Error: calling prepend() on NULL List reference.\n");
      exit(1);
   }

   Node nodeToPrepend = newNode(data);
   
   if( length(L) <= 0 )
   {
      L->front = L->back = nodeToPrepend;
   }
   else
   {
      nodeToPrepend->next = L->front;
      L->front->previous = nodeToPrepend;
      L->front = nodeToPrepend;
   }
   if( Index(L) > -1 )
   {
      (L->Index)++;
   }
   (L->length)++; 
}

// append()
// Insert new element into this List. If List is non-empty,
// insertion takes place after back element.
void append(List L, Entry data)  
{
   if( L==NULL )
   {
      printf("List Error: calling append() on NULL List reference.\n");
      exit(1);
   }

   Node nodeToAppend = newNode(data); 

   if( length(L) <= 0)
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

// insertBefore()
// Insert new element before cursor.
// Pre: length()>0, Index() >=0
void insertBefore(List L, Entry data)
{
   if( L==NULL )
   {
      printf("List Error: calling insertBefore() on NULL List reference.\n");
      exit(1);
   }
   if( length(L) <= 0 )
   {
      printf("List Error: calling insertBefore() on empty list.\n");
      exit(1);
   }
   if( Index(L) < 0 )
   {
      printf("List Error: calling insertBefore() on undefined cursor.\n");
      exit(1);
   }

   Node nodeToInsert = newNode(data);
   
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

// insertAfter()
// Insert new element after cursor.
// Pre: length()>0, Index() >=0
void insertAfter(List L, Entry data)
{
   if( L==NULL )
   {
      printf("List Error: calling insertAfter() on NULL List reference.\n");
      exit(1);
   }
   if( length(L) <= 0 )
   {
      printf("List Error: calling insertAfter() on empty list.\n");
      exit(1);
   }
   if( Index(L) < 0 )
   {
      printf("List Error: calling insertAfter() on undefined cursor.\n");
      exit(1);
   }

   Node nodeToInsert = newNode(data);
      
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

// deleteFront()
// Deletes the front element. Pre: length() > 0
void deleteFront(List L) 
{
   if( L == NULL )
   {
      printf("List Error: calling deleteFront() on NULL List reference.\n");
      exit(1);
   }
   if( length(L) <= 0 )
   {
      printf("List Error: calling deleteFront() on empty list.\n");
      exit(1);
   }
   if( length(L) == 1 )
   {
      if( Index(L) == 0 )
      {
         L->cursor = NULL;
         L->Index = - 1;
      }
      //      printf("deleteFront( %d ) ", (L->front)->data);//debug
      freeNode(&L->front);
      L->back = L->front = NULL;
   }
   else
   {
      if( Index(L) != -1 )
      {
         (L->Index)--;
         if( Index(L) == -1 )
            L->cursor = NULL;
      }
      L->front = L->front->next;
      L->front->previous->next = NULL;
      //      printf("deleteFront ( %d ) ", (L->front->previous)->data);//debug
      freeNode(&L->front->previous);
      L->front->previous = NULL;
   }
   (L->length)--;
}

// deleteBack()
// Deletes the back element. Pre: length() > 0
void deleteBack(List L) 
{
   if( L == NULL )
   {
      printf("List Error: calling deleteBack() on NULL List reference.\n");
      exit(1);
   }
   if( length(L) <= 0 )
   {
      printf("List Error: calling deleteBack() on empty list.\n");
      exit(1);
   }
   if( length(L) == 1 )
   {
      if( Index(L) == 0 )
      {
         L->cursor = NULL;
         L->Index = -1;
      }
      freeNode(&L->front);
      L->back = L->front = NULL;
   }
   else
   {
      if( Index(L) == (length(L) - 1) )
      {
         L->Index = -1;
         L->cursor = NULL;
      }
      L->back = L->back->previous;
      L->back->next->previous = NULL;
      freeNode(&L->back->next);
      L->back->next = NULL;
   }
   (L->length)--;
}

// delete()
// Deletes cursor element, making the cursor undefined.
// Pre: length() > 0, Index() >= 0
void delete(List L) 
{
   if( L==NULL )
   {
      printf("List Error: calling delete() on NULL List reference.\n");
      exit(1);
   }
   if( length(L) <= 0 )
   {
      printf("List Error: calling delete() on empty list.\n");
      exit(1);
   }
   if( Index(L) == - 1 )
   {
      printf("List Error: calling delete() on undefined cursor.\n");
      exit(1);
   }
   if( length(L) == 1 )
   {
      L->front = NULL;
      L->back = NULL;
   }
   else if( Index(L) == 0 )
   {
      L->front = L->cursor->next;
      L->front->previous = NULL;
      L->cursor->next = NULL;
   }
   else if( Index(L) == (length(L) - 1) )
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
   freeNode(&L->cursor);
   L->cursor = NULL;
   (L->length)--;
}

// Other Functions ------------------------------------------------------------

// listToString()
// Prints data elements in L to output file.
void listToString(List L, FILE* out)
{
   Node N = NULL;
   
   if( L==NULL )
   {
      printf("List Error: calling printList() on NULL List reference\n");
      exit(1);
   }
   for(N = L->front; N != NULL; N = N->next)
   {
      entryToString(N->data, out);
      fprintf(out, " ");
   }
}                                                                           

// copyList()
// Returns a new list representing the same integer sequence as this List.
// The cursor in the new list is undefined, regardless of the state of the
// cursor in this List. This List is unchanged.
List copyList(List L) 
{
   if( L==NULL )
   {
      printf("List Error: calling copyList() on NULL List reference\n");
      exit(1);
   }
   List listCopy = newList();
   Node traverseNode = NULL;              
   traverseNode = L->front;

   while( traverseNode != NULL )
   {
      append(listCopy, traverseNode->data); 
      traverseNode = traverseNode->next;
   }
   freeNode(&traverseNode);
   return listCopy;
}


// Helper Functions -----------------------------------------------------------
// insertInOrder()
// inserts new nodes in increasing order.
void insertInOrder(List* L, Entry v)
{
   if( L == NULL || *L == NULL )
   {
      printf("List Error: calling InsertInOrder() on "
             "NULL List reference or null pointer\n");
      exit(1);
   }
   // maybe create a node to remember the cursor //debug.
   moveFront(*L);
   while( Index(*L) != -1 )
   {
      if( getEntryData(v) < getEntryData( get(*L) ) )
      {
         insertBefore(*L, v);
         break;
      }
      moveNext(*L);
   }
  if( Index(*L) == -1 )
  {
     append(*L, v);
  }
}
