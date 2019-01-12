#ifndef _MATRIX_H_INCLUDE_
#define _MATRIX_H_INCLUDE_

#include <stdbool.h>
#include "EntryList.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// Entry type -----------------------------------------------------------------

// Exported type --------------------------------------------------------------

typedef struct ListObj* List;
typedef struct EntryObj* Entry;

// Contructors and destructors ------------------------------------------------

// newEntry()
// creates a new entry object.
// preconditions: 
Entry newEntry(int columnNumber, double data); // changed int to object.

// copyEntry()
// Deep-copies a new entry object.
// preconditions: 
Entry copyEntry(Entry other);

// Access Functions -----------------------------------------------------------
// getEntryColumn()
// returns the column field in an entry struct.
int getEntryColumn(Entry E);

// getEntryData()
// returns the data field in an entry struct.
double getEntryData(Entry E);

// Manipulation procedures -------------------------------------------------

// setData()
// changes the value in the data field of the entry.
void setData(Entry E, double x);

// entryToString()
// stringifies an entry
void entryToString(Entry E, FILE* file);

// Matrix type ----------------------------------------------------------------

// Exported type --------------------------------------------------------------

typedef struct MatrixObj* Matrix;

// Contructors and destructors ------------------------------------------------

// newMatrix()
// creates a new Matrix object.
// Precondition n >= 1.
Matrix newMatrix(int n);

// freeMatrix()
// free each list that represents a row and finally frees the memory of
// the matrixObj itsef
void freeMatrix(Matrix* pM);

// copyMatrix()
// Deep-copies a matrix.
Matrix copyMatrix(Matrix M);

// Access Functions -----------------------------------------------------------

// getMatrixSize()
// Returns the size of the Matrix (the dimensions).
int getMatrixSize(Matrix M);

// getNNZ()
// Returns the number of non-zero entries.
int getNNZ(Matrix M);

// matrixEquals()
// Returns true if two matrices are equal. False otherwise. ?
bool matrixEquals(Matrix L, Matrix R);

// getMatrixEntryData()
// returns the data in an Entry when given column and row as arguments.
double getMatrixEntryData(Matrix M, int column, int row);

// Manipulation procedures -------------------------------------------------

// makeZero()
// Puts the matrix back to its initial condition wehere there are no non-zero
// entries.
void makeZero(Matrix M);

// changeEntry()
// changes ith row, jth column of this Matrix to x
// pre: 1<=i<=getMatrixSize(), 1<=j<=getMatrixSize()
void changeEntry(Matrix M, int i, int j, double x);

// scalarMult()
// returns a new Matrix that is the scalar product of this Matrix with x
Matrix scalarMult(Matrix M, double x);

// add()	 
// returns a new Matrix that is the sum of this Matrix with M
// pre: getMatrixSize()==M.getMatrixSize()
Matrix add(Matrix L, Matrix R);

// sub()
// returns a new Matrix that is the difference of this Matrix with M
// pre: getMatrixSize()==M.getMatrixSize()
Matrix sub(Matrix L, Matrix R);

// transpose()
// returns a new Matrix that is the transpose of this Matrix 
Matrix transpose();
    
// mult()
// returns a new Matrix that is the product of this Matrix with M
// pre: getMatrixSize()==M.getMatrixSize()
Matrix mult(Matrix L, Matrix R);

// Other Functions ---------------------------------------------------------

// matrixToString()
// returns a text representation of the matrix.
void matrixToString(FILE * out, Matrix M);

// dot()
// Takes the dot product of two lists.
double dot(List P, List Q);
   
// Helper Functions --------------------------------------------------------

// addHelper()
// helper functions for add().
List addHelper(List a, List b, bool isSum);

#endif
