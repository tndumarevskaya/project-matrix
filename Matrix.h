#ifndef MATRIX_H
#define MATRIX_H

typedef struct matrix
{
	int n;
	int m;

	int** mas;

}MATRIX;


void CreateRandomMatrix(MATRIX* matr,int LeftBorder, int RightBorder, int n, int m );


MATRIX* Summation(MATRIX* a, MATRIX* b, MATRIX* result);
MATRIX* Subtraction(MATRIX* a, MATRIX* b, MATRIX* result);
void SetMemory(MATRIX* a, int N, int M);
void FreeMemory(MATRIX* math);
void PrintMatrix(MATRIX* matr);

MATRIX* NaiveMultiplication(MATRIX* matr1, MATRIX* matr2, MATRIX* result);
MATRIX* SimpleDnCMultiplication(MATRIX* a, MATRIX* b, MATRIX* result);

#endif MATRIX_H