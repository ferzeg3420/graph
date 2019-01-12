// IntList.h
// Fernando Zegada
// Function prototypes and headers of the list ADT in C.

#ifndef _INTLIST_H_INCLUDE_
#define _INTLIST_H_INCLUDE_

// Exported type --------------------------------------------------------------
typedef struct IntListObj* IntList;

// Constructors-Destructors ---------------------------------------------------

// newIntList()
// Returns reference to new empty IntList object. 
IntList newIntList(void);

// freeIntList()
// Frees all heap memory associated with IntList *pL, and sets *pL to NULL.
void freeIntList(IntList* pL);

// Access functions -----------------------------------------------------------

// length()
// Returns the length of L.
int IntListLength(IntList L);

// Index()
// Returns the Index of the cursor.
int IntListIndex(IntList L);

// front()
// Returns the data of the front node in the IntList.
int IntListFront(IntList L);

// back()
// Returns the data of the back node in the IntList.
int IntListBack(IntList L);

// get()
// Returns the data of the cursor node.
int IntListGet(IntList L);

// equals()
// returns true (1) if A is identical to B, false (0) otherwise.
int IntListEquals(IntList A, IntList B);

// Manipulation procedures ----------------------------------------------------

// IntListClear()
// Resets the list to its original empty state.
void IntListClear(IntList L);

// IntListMoveFront()
// If IntList is non-empty, places the cursor under the front element, otherwise
// does nothing.
void IntListMoveFront(IntList L);

// IntListMoveBack()
// If IntList is non-empty, places the cursor under the back element, otherwise
// does nothing.
void IntListMoveBack(IntList L);

// IntListMovePrev()
// If cursor is defined and not at front, moves cursor one step toward
// front of this IntList, if cursor is defined and at front, cursor becomes
// undefined, if cursor is undefined does nothing.
void IntListMovePrev(IntList L);

// IntListMoveNext()
// If cursor is defined and not at back, moves cursor one step toward
// back of this IntList, if cursor is defined and at back, cursor becomes
// undefined, if cursor is undefined does nothing.
void IntListMoveNext(IntList L);

// IntListPrepend()
// insert new element into this IntList. If IntList is non-empty,
// insertion takes place before front element.
void IntListPrepend(IntList L, int data);

// IntListAppend()
// insert new element into this IntList. If IntList is non-empty,
// insertion takes place after back element.
void IntListAppend(IntList L, int data);

// IntListInsertBefore()
// insert new element before cursor.
// Pre: length()>0, Index() >=0
void IntListInsertBefore(IntList L, int data);

// insertAfter()
// insert new element after cursor.
// Pre: length()>0, Index() >=0
void IntListInsertAfter(IntList L, int data);

// IntListDeleteFront()
// Deletes the front element. Pre: length() > 0
void IntListDeleteFront(IntList L);

// IntListDeleteBack()
// Deletes the back element. Pre: length() > 0
void IntListDeleteBack(IntList L);

// IntListDelete()
// Deletes cursor element, making the cursor undefined.
// Pre: length()>0, Index() >= 0
void IntListDelete(IntList L);

// Other Functions ------------------------------------------------------------

// intListToString()
// Prints data elements in L on a single line to stdout
void intListToString(FILE* out, IntList L);

// copyIntList()
// Returns a new list representing the same integer sequence as this IntList.
// The cursor in the new list is undefined, regardless of the state of the
// cursor in this IntList. This IntList is unchanged.
IntList copyIntList(IntList L);

// Helper Functions -----------------------------------------------------------
// IntListInsertInOrder()
// inserts new nodes in increasing order.
void IntListInsertInOrder(IntList* L, int v);


#endif
