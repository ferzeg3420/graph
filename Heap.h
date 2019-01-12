#ifndef _QUEUE_H_INCLUDE_
#define _QUEUE_H_INCLUDE_
#define INF -2
#define NIL 0

// Exported type --------------------------------------------------------------
typedef struct HeapObj* Heap;

// Contructors and destructors ------------------------------------------------

// newHeap()
// Returns reference to new empty Heap object.
//Heap newHeap(int maxLength);

// newHeap()
// Returns reference to new heap object containing an array passed as input.
Heap newHeap(int arrayLength, int * array);

// freeQueue()
// Frees all heap memory associated with Queue *pQ, and sets *pQ to NULL.S
void freeHeap(Heap* pH);

// Access functions -----------------------------------------------------------

// getHeapSize()
// returns the size of the heap
int getHeapSize(Heap H);

// parent()
// Returns the index of the parent.
int parent(int index);

// left()
// Returns the index of the left child.
int left(int index);

// right()
// Returns the index of the right child.
int right(int index);

// Manipulation procedures ----------------------------------------------------

// heapify()
// Establishes the minimumHeap property.
// Precondition: Index cannot be negative or zero.
void heapify( Heap H, int index);

// buildHeap()
// Takes an array and returns an array that represents a heap.
void buildHeap(Heap H);

// heapSort()
// Sorts an input array greatest to smallest by using a heap.
int * heapSort(int * array, int length);

// priorityQueue // min priority queue

// heapMinimum()
// returns the minimum value.
// Precondition: The size of the heap must not be zero.
int heapMinimum(Heap H);

// heapDeleteMin()
// deletes the first element in a priorityQueue.
// Precondition: The size of the heap must not be zero.
void heapDeleteMin(Heap H);

// heapExtractMin()
// Returns the minimum and deletes it using heapDeleteMin()
// Precondition: The size of the heap must not be zero.
int heapExtractMin(Heap H);

// heapDecreaseKey()
// Modifies the key of an index only if this decreases its old value.
// Precondition: The index must be less than heap size and greater than zero.
void heapDecreaseKey(Heap H, int index, int key);

// heapInsert()
// Inserts a record to the priorityQueue
// Precondition: The size of the heap must be strictly less than that of the
// inner array
void heapInsert(Heap H, int k);
 
// Helper functions -----------------------------------------------------------

// swap()
// swaps two indices in an input array.
void swap(int * array, int index1, int index2);

// printHeap()
// prints heap.
void printHeap(Heap H);

#endif
