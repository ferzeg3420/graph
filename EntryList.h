// EntryList.h
// Fernando Zegada
// Function prototypes and headers of the list ADT in C.

#ifndef _ENTRYLIST_H_INCLUDE_
#define _ENTRYLIST_H_INCLUDE_
#include<stdbool.h>
#include"Matrix.h"

// Exported type --------------------------------------------------------------
typedef struct ListObj* List;
typedef struct EntryObj* Entry;

// Constructors-Destructors ---------------------------------------------------

// newList()
// Returns reference to new empty List object. 
List newList(void);

// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.
void freeList(List* pL);

// Access functions -----------------------------------------------------------

// length()
// Returns the length of L.
int length(List L);

// Index()
// Returns the Index of the cursor.
int Index(List L);

// front()
// Returns the data of the front node in the List.
Entry front(List L);

// back()
// Returns the data of the back node in the List.
Entry back(List L);

// get()
// Returns the data of the cursor node.
Entry get(List L);

// areListsEquals()
// returns true (1) if A is identical to B, false (0) otherwise.
bool areListsEqual(List A, List B);

// Manipulation procedures ----------------------------------------------------

// clear()
// Resets the list to its original empty state.
void clear(List L);

// moveFront()
// If List is non-empty, places the cursor under the front element, otherwise
// does nothing.
void moveFront(List L);

// moveBack()
// If List is non-empty, places the cursor under the back element, otherwise
// does nothing.
void moveBack(List L);

// movePrev()
// If cursor is defined and not at front, moves cursor one step toward
// front of this List, if cursor is defined and at front, cursor becomes
// undefined, if cursor is undefined does nothing.
void movePrev(List L);
  

// moveNext()
// If cursor is defined and not at back, moves cursor one step toward
// back of this List, if cursor is defined and at back, cursor becomes
// undefined, if cursor is undefined does nothing.
void moveNext(List L);

// prepend()
// insert new element into this List. If List is non-empty,
// insertion takes place before front element.
void prepend(List L, Entry data);

// append()
// insert new element into this List. If List is non-empty,
// insertion takes place after back element.
void append(List L, Entry data);

// insertBefore()
// insert new element before cursor.
// Pre: length()>0, Index() >=0
void insertBefore(List L, Entry data);

// insertAfter()
// insert new element after cursor.
// Pre: length()>0, Index() >=0
void insertAfter(List L, Entry data);

// deleteFront()
// Deletes the front element. Pre: length() > 0
void deleteFront(List L);

// deleteBack()
// Deletes the back element. Pre: length() > 0
void deleteBack(List L);

// delete()
// Deletes cursor element, making the cursor undefined.
// Pre: length()>0, Index() >= 0
void delete(List L);

// Other Functions ------------------------------------------------------------

// listToString()
// Prints data elements in L on a single line to stdout
void listToString(List L, FILE* out);

// copyList()
// Returns a new list representing the same integer sequence as this List.
// The cursor in the new list is undefined, regardless of the state of the
// cursor in this List. This List is unchanged.
List copyList(List L);

// Helper Functions -----------------------------------------------------------
// insertInOrder()
// inserts new nodes in increasing order.
void insertInOrder(List* L, Entry v);


#endif
