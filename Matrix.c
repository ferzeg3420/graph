// Matrix.c
// Fernando Zegada
// Matrix implements a linear algebra matrix with its addition, multiplication
// defined for square matrices. The particular implementation is for sparse
// matrices using arrays of lists.

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Matrix.h"
#include "EntryList.h"

// Entry struct -------------------------------------------------------------------

typedef struct EntryObj
{
   double data;
   int columnNumber; 
} EntryObj;
      
// Constructors and destructors ---------------------------------------------------

// newEntry()
// creates a new entry object.
Entry newEntry(int columnNumber, double data)
{
   Entry E;
   E = malloc(sizeof(EntryObj));
   E->data = data;
   E->columnNumber = columnNumber;
   return E;
}

// copyEntry()
// returns a new instance of Entry that is a deep copy of the argument Entry.
Entry copyEntry(Entry other)
{
   if( other == NULL )
   {
      printf("Matrix error: calling entry's copyEntry() on null entry as"
             " argument.");
      exit(1);
   }
   Entry E = malloc(sizeof(EntryObj));
   E->data = other->data;
   E->columnNumber = other->columnNumber;
   return E;
}

// getEntryColumn()
// returns the column field in an entry struct.
int getEntryColumn(Entry E)
{
   if( E == NULL )
   {
      printf("Matrix error: calling entry's getEntryColumn() on null entry");
      exit(1);
   }
   return E->columnNumber;
}

// getEntryData()
// returns the data field in an entry struct.
double getEntryData(Entry E)
{
   if( E == NULL )
   {
      printf("Matrix error: calling entry's getEntryData() on null entry");
      exit(1);
   }
   return E->data;
}

// setData()
// changes the value in the data field of the entry.
void setData(Entry E, double x)
{
   if( E == NULL )
   {
      printf("Matrix error: calling entry's setData() on null entry");
      exit(1);
   }
   E->data = x;
}

// entryToString()
// stringifies an entry
void entryToString(Entry E, FILE* out)
{
   if( E == NULL )
   {
      printf("Matrix error: calling Entry's toString() on null entry");
      exit(1);
   }
   fprintf(out, "(%d, %f)", E->columnNumber, E->data);
}

// areEntriesEqual()
// test if entries are equivalent, their data members have the same values.
bool areEntriesEqual(Entry L, Entry R)
{
   if( (L->data == R->data) && (L->columnNumber == R->columnNumber) )
   {
      return true;
   }
   return false;
}

// End of Entry -------------------------------------------------------------------

// Matrix Definitions -------------------------------------------------------------

// Struct -------------------------------------------------------------------------

typedef struct MatrixObj
{
   int dimensions;
   List* rows;
} MatrixObj;

// Contructors --------------------------------------------------------------------

// newMatrix()
// Precondition n >= 1. 
Matrix newMatrix(int n)
{
   if( n < 1 ) 
   {
      printf("Error: Program: Sparse, module: Matrix,  precondition: Matrix()"
             "constructor called with a bad dimension.");
      exit(1);
   }
   Matrix M;
   M = malloc(sizeof(MatrixObj));
   M->dimensions = n;
   M->rows = (List *)malloc( (n + 1) * sizeof(List) );

   for( int i = 0; i <= M->dimensions; i++) // <= because I am ignoring index 0
   {
      M->rows[i] = newList();
   }
   return M;
}

// freeMatrix()
// free each list that represents a row and finally frees the memory of
// the matrixObj itsef
void freeMatrix(Matrix* pM)
{
   if(pM!=NULL && *pM!=NULL)
   {
      for( int i = 0; i <= (*pM)->dimensions; i++)
      {
         freeList( &( (*pM)->rows[i] ) );
      }
      free(*pM);
      *pM = NULL;
   }
}

// copyMatrix()
// Deep-copies a matrix.
Matrix copyMatrix(Matrix M)
{
   Matrix matrixCopy = newMatrix(M->dimensions);
   List thisRow = newList();
 
   int thisColumn;
   double thisData;

   for( int i = 1; i <= M->dimensions; i++ )
   {
      thisRow = M->rows[i];
  
      for( moveFront(thisRow); Index(thisRow)!= -1; moveNext(thisRow) )
      {
         thisColumn = getEntryColumn(get(thisRow));
         thisData = getEntryData(get(thisRow));
         changeEntry(matrixCopy, i, thisColumn, thisData);
      }
   }
   return matrixCopy;
}

// Access Functions ---------------------------------------------------------------

// getMatrixSize()
// Returns the size of the Matrix (the dimensions).
int getMatrixSize(Matrix M)
{ 
   return M->dimensions; 
}

// getNNZ()
// Returns the number of non-zero entries.
int getNNZ(Matrix M)
{
   int counter = 0;
   for( int i = 1; i <= M->dimensions; i++ )
   {
      counter += length(M->rows[i]);
   }
   return counter;
}

// areMatricesEqual()
// Returns true if two matrices are equal. False otherwise.
bool areMatricesEqual(Matrix L, Matrix R)
{
   List left = newList();
   List right = newList();

   if(  L ==  R )
   {
      return true;
   }
   if( getMatrixSize(L) != getMatrixSize(R) )
   {
      return false;
   }
   for( int i = 1; i <= L->dimensions; i++ )
   {
      left = L->rows[i];
      right = R->rows[i];

      if( length(left) != length(right))
      {
          return false;
      }
      moveFront(left);
      moveFront(right);

      while( Index(left) != -1 )
      {
         if( !( areEntriesEqual(get(left), get(right)) ) )
         {
            return false;
         }
         moveNext(left);
         moveNext(right);
      }
   }
   return true;
}

double getMatrixEntryData(Matrix M, int column, int row)
{
   List * workingList = &( M->rows[row] );
   Entry workingEntry = newEntry(0, 0.0);

   for
   ( moveFront(*workingList);
     Index(*workingList) != -1;
     moveNext(*workingList)
   ){
      workingEntry =  get(*workingList);
      if( getEntryColumn(workingEntry) == column )
      {
	 return getEntryData(workingEntry);
      }
   }
   return 0.0; // clearly an error has ocurred. maybe should return a
               // ridiculous value and test for it somewhere in the client.
}

// Manipulation procedures -------------------------------------------------

// makeZero()
// Puts the matrix back to its initial condition wehere there are no non-zero
// entries.
void makeZero(Matrix M)
{
   for( int i = 1; i <= M->dimensions; i++ )
   {
      clear(M->rows[i]);
   }
}

// changeEntry()
// pre: 1<=i<=getMatrixSize(), 1<=j<=getMatrixSize()
// changes ith row, jth column of this Matrix to x
void changeEntry(Matrix M, int i, int j, double x)
{
   if( i < 1 || i > getMatrixSize(M) || j < 1 || j > getMatrixSize(M) )
   {
      printf( "Error: Program: Sparse, module: Matrix, precondition:"
              " changeEntry() called with out of bounds arguments.");
      exit(1);
   }
   Entry E = newEntry(j, x);
   if( length(M->rows[i]) != 0.0 )
   {
      for( moveFront(M->rows[i]); Index(M->rows[i]) != -1; moveNext(M->rows[i]) )
      {
         if( getEntryColumn(get(M->rows[i])) == j )
         {
            if( x == 0.0 )
            {
               delete(M->rows[i]);
            }
            else
            {
               setData( get( M->rows[i] ), x ); 
            }
            break;
         }
         if(  getEntryColumn( get(M->rows[i]) )  > j ) 
         {
            if( x != 0.0 )
            {
               insertBefore(M->rows[i], E);
            }
            break;
         }
      }
   }
   if( Index(M->rows[i]) == -1 && x != 0 )
   {
      append(M->rows[i], E);
   }
}

// scalarMult()
// returns a new Matrix that is the scalar product of this Matrix with x
Matrix scalarMult(Matrix M, double x)
{
   Matrix resultMatrix = newMatrix(M->dimensions);
   
   List oldRow = newList();
   List resultRow = newList();

   if (x != 0)
   {
      for( int i = 1; i <= M->dimensions; i++ )
      {
         oldRow = M->rows[i];
         resultRow = resultMatrix->rows[i];

         for( moveFront(oldRow); Index(oldRow)!= -1; moveNext(oldRow) )
         {
            Entry resultEntry = newEntry
               (
		getEntryColumn( get(oldRow) ),
                getEntryData( get(oldRow) ) * x
               );
            append(resultRow, resultEntry);
         }
      }
   }
   return resultMatrix;
}

// add()
// returns a new Matrix that is the sum of this Matrix with M
// pre: getMatrixSize()==M.getMatrixSize()
Matrix add(Matrix L, Matrix R)
{
   if( getMatrixSize(L) != getMatrixSize(R) )
   {
      printf("Error: Program: Sparse, module: Matrix, precondition:"
             " add() called with mismatching dimensions.");
      exit(1);
   }
   Matrix resultMatrix = newMatrix(L->dimensions);
   List leftRow = newList();
   List rightRow = newList();

   for( int i = 1; i <= L->dimensions; i++)
   {
      leftRow = L->rows[i];
      rightRow = R->rows[i];
      resultMatrix->rows[i] = addHelper(leftRow, rightRow, true);
   }
   return resultMatrix;
}

// sub()
// returns a new Matrix that is the difference of this Matrix with M
// pre: getMatrixSize()==M.getMatrixSize()
Matrix sub(Matrix L, Matrix R)
{
   if( getMatrixSize(L) != getMatrixSize(R) )
   {
      printf("Error: Program: Sparse, module: Matrix, precondition:"
             " sub() called with mismatching dimensions.");
      exit(1);
   }
   Matrix resultMatrix = newMatrix(L->dimensions);
   List leftRow = newList();
   List rightRow = newList();

   for( int i = 1; i <= getMatrixSize(L); i++)
   {
      leftRow = L->rows[i];
      rightRow = R->rows[i];
      resultMatrix->rows[i] = addHelper(leftRow, rightRow, false);
   }
   return resultMatrix;
}

// transpose()
// returns a new Matrix that is the transpose of this Matrix 
Matrix transpose(Matrix M)
{
   Matrix transposedMatrix = newMatrix(M->dimensions);
   List currentRow = newList();

   int column = 0;
   double currentData = 0.0;

   for( int row = 0; row <= M->dimensions; row++ )
   {
      currentRow = M->rows[row];

      for( moveFront(currentRow);
           Index(currentRow) != -1;
           moveNext(currentRow)
      ){
         column = getEntryColumn(get(currentRow));
         currentData = getEntryData(get(currentRow));

         changeEntry(transposedMatrix, column, row, currentData);// index invert
      }
   }
   return transposedMatrix;
}

// mult()
// Returns a new Matrix that is the product of this Matrix with M
// pre: getMatrixSize()==M.getMatrixSize()
Matrix mult(Matrix L, Matrix R)
{
   if( getMatrixSize(L) != getMatrixSize(R) )
   {
      printf("Error: Program: Sparse, module: Matrix, precondition: mult()"
             " called with mismatching dimensions.");
      exit(1);
   }
   double entryData;
    
   Matrix resultMatrix = newMatrix(L->dimensions);
   Matrix transposedR = newMatrix(L->dimensions);

   List leftList = newList();
   List rightList = newList();

   transposedR = transpose(R);

   for( int row = 1; row <= L->dimensions; row++ )
   {
      leftList = L->rows[row];
       
      for( int column = 1; column <= L->dimensions; column++ )
      {
         rightList = transposedR->rows[column];
         entryData = dot( leftList, rightList );
         changeEntry(resultMatrix, row, column, entryData);
      }
   }
   return resultMatrix;  
}

// Other Functions ---------------------------------------------------------

// matrixToString()
// returns a text representation of the matrix.
void matrixToString(FILE * out, Matrix M)
{
   for(int i = 1; i <= M->dimensions; i++)
   {
      fprintf(out, "%d:", i);      
      if( length(M->rows[i]) != 0 )
      {
         listToString(M->rows[i], out );
      }
      fprintf(out, "\n");
   }
}

// dot()
// Takes the dot product of two lists.
double dot(List P, List Q)
{
   double returnValue = 0;
   
   int columnP = 0, columnQ = 0;

   moveFront(P);
   moveFront(Q);
   while( Index(P) != -1 && Index(Q) != -1 )
   {
      columnP = getEntryColumn(get(P));
      columnQ = getEntryColumn(get(Q));

      if( columnP == columnQ )
      {
         returnValue += getEntryData( get(P) ) * getEntryData( get(Q) );
         moveNext(P);
         moveNext(Q);
      }
      else if( columnP < columnQ )
      {
         moveNext(P);
      }
      else  /* columnQ < columnP */
      {
         moveNext(Q);
      }
   }
   return returnValue; 
}

// Helper Functions --------------------------------------------------------

// addHelper()
// helper functions for add().
List addHelper(List a, List b, bool isSum)
{
   List resultList = newList();
   Entry resultEntry = newEntry(0,0.0); 
   int columnNumberA = 0, columnNumberB = 0;
   bool areSameList = false;

   if( a == b )
   {
      areSameList = true;
   }
   else
   {
      areSameList = false;
   }
   if( length(a) == 0 && length(b) == 0 )
   {
      return resultList;
   }
   else if( length(a) == 0 ) 
   {
      for( moveFront(b); Index(b) != -1; moveNext(b) )
      {
         resultEntry->columnNumber = getEntryColumn(get(b));      
         if( isSum )
         {
            resultEntry->data = getEntryData(get(b));
         }
         else
         {
            resultEntry->data = -1 * getEntryData(get(b));
         }
         Entry NewEntry = copyEntry(resultEntry);
	 append( resultList, NewEntry );
      }
      return resultList;
   }
   else if( length(b) == 0 )
   {
      for( moveFront(a); Index(a) != -1; moveNext(a) )
      {
	 Entry NewEntry = copyEntry( get(a) );
	 append( resultList, NewEntry );
      }
      return resultList;
   }
   moveFront(a);
   moveFront(b);
   while( Index(a) != -1 && Index(b) != -1 )
   {
      columnNumberA = getEntryColumn(get(a));
      columnNumberB = getEntryColumn(get(b));

      if( columnNumberA == columnNumberB )
      {
         resultEntry->columnNumber = columnNumberA;
         if( isSum )
         {
            resultEntry->data =  getEntryData( get(a) ) + getEntryData( get(b) );
         }
         else
         {
            resultEntry->data = getEntryData( get(a) ) - getEntryData( get(b) );
         }

	 Entry NewEntry = copyEntry(resultEntry);
    	 
         if (resultEntry->data != 0.0)
         {
	    append(resultList, NewEntry);
         }
         moveNext(a);
         if ( !areSameList )
         {
	    printf("moved next.\n");
            moveNext(b);
	 }
      }
      else if( columnNumberA < columnNumberB  )
      {
         Entry NewEntry = copyEntry( get(a) );
         append(resultList, NewEntry);
         moveNext(a);
      }
      else
      {
         resultEntry->columnNumber = getEntryColumn(get(b));

	 if( isSum )
         {
            resultEntry->data = getEntryData(get(b));
         } 
         else
         {
            resultEntry->data = -1 * getEntryData( get(b) );
         }
         Entry NewEntry = copyEntry(resultEntry);
         append(resultList, NewEntry);
         moveNext(b);
      }
   }
   if( Index(a) != -1 )
   {
      do
      {
         Entry NewEntry = copyEntry(get(a));
         append( resultList, NewEntry );
         moveNext(a);
      }
      while( Index(a) != -1 );
   }
   if( Index(b) != -1) 
   {
      if( isSum )
      {
         do
         {
            Entry NewEntry = copyEntry( get(b) );
            append( resultList, NewEntry );
            moveNext( b );
         }
         while( Index(b) != -1 );
      }
      else 
      {
         do
         {
            resultEntry->data = -1 * getEntryData( get(b) );
            resultEntry->columnNumber = getEntryColumn( get(b) );

	    Entry NewEntry = copyEntry( resultEntry );
            append(resultList, NewEntry);
            moveNext(b);
         }
         while( Index(b) != -1 );
      }
   }
return resultList;
}

