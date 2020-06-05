#ifndef MATRIX_H
#define MATRIX_H

typedef struct matrix {
	int n;
	int m;
	int** matr;
}MATRIX;

MATRIX allocatedMemory(int m, int n);
MATRIX freeMemory(MATRIX math);
MATRIX createMatrix(MATRIX math);
void printMatrix(MATRIX c);
MATRIX sumMatrix(MATRIX a, MATRIX b, MATRIX c);
MATRIX subMatrix(MATRIX a, MATRIX b, MATRIX c);
MATRIX naive(MATRIX a, MATRIX b, MATRIX c);
MATRIX dncSimple(MATRIX a, MATRIX b);
MATRIX Strassena(MATRIX a, MATRIX b);
void Compare(MATRIX c, MATRIX c1, MATRIX c2);

#endif