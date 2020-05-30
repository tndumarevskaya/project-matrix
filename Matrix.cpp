#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Matrix.h"

void SetMemory(MATRIX* a, int N, int M)
{
	
	a->n = N;
	a->m = M;
	a->mas = (int**)malloc(N * sizeof(int*));
	for (int i = 0; i < N; i++)
		a->mas[i] = (int*)malloc(M * sizeof(int));
	
}

void PrintMatrix(MATRIX* matr)
{
	for (int i = 0; i < matr->n; i++)
	{
		for (int j = 0; j < matr->m; j++)
			printf("%d  ", matr->mas[i][j]);
		printf("\n");
	}

	printf("\n\n");
}

void CreateRandomMatrix(MATRIX* matr,int LeftBorder, int RightBorder, int n, int m)
{
	SetMemory(matr, n,m);

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			matr->mas[i][j] = LeftBorder + rand() % (RightBorder - LeftBorder);

}


MATRIX* Summation(MATRIX* a, MATRIX* b, MATRIX* result)
{
	
	result->n = a->n;
	result->m = b->m;

	SetMemory(result,a-> n, b->m);

	for (int i = 0; i < result->n; i++)
		for (int j = 0; j < result->m; j++)
			result->mas[i][j] = a->mas[i][j] + b->mas[i][j];

	return result;
}

MATRIX* Subtraction(MATRIX* a, MATRIX* b, MATRIX* result)
{
	result->n = a->n;
	result->m = b->m;

	SetMemory(result, a->n, b->m);

	for (int i = 0; i < result->n; i++)
		for (int j = 0; j < result->m; j++)
			result->mas[i][j] = a->mas[i][j] - b->mas[i][j];

	return result;
}

void FreeMemory(MATRIX* matr)
{
	for (int i = 0; i < matr->n; ++i)
		free(matr->mas[i]);
	free(matr->mas);
}




MATRIX* NaiveMultiplication(MATRIX* a, MATRIX* b, MATRIX* result)
{
	SetMemory(result, a->n, b->m);

	for (int i = 0; i < result->n; i++)
		for (int j = 0; j < result->m; j++)
		{
			result->mas[i][j] = 0;
			for (int k = 0; k < a->m; k++)
				result->mas[i][j] = result->mas[i][j] + a->mas[i][k] * b->mas[k][j];
		}
	return result;
}

MATRIX* SimpleDnCMultiplication(MATRIX* a, MATRIX* b, MATRIX* result)
{
	if (a->n <= 1) ///128
		return NaiveMultiplication(a, b, result);


	SetMemory(result, a->n, b->m);
	int N = a->n / 2;

	MATRIX a11;
	MATRIX a12;
	MATRIX a21;
	MATRIX a22;

	MATRIX b11;
	MATRIX b12;
	MATRIX b21;
	MATRIX b22;

	SetMemory(&a11, N, N);
	SetMemory(&a12, N, N);
	SetMemory(&a21, N, N);
	SetMemory(&a22, N, N);

	SetMemory(&b11, N, N);
	SetMemory(&b12, N, N);
	SetMemory(&b21, N, N);
	SetMemory(&b22, N, N);

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			a11.mas[i][j] = a->mas[i][j];
			b11.mas[i][j] = b->mas[i][j];
			a12.mas[i][j] = a->mas[i][j + N];
			b12.mas[i][j] = b->mas[i][j + N];
			a21.mas[i][j] = a->mas[i + N][j];
			b21.mas[i][j] = b->mas[i + N][j];
			a22.mas[i][j] = a->mas[i + N][j + N];
			b22.mas[i][j] = b->mas[i + N][j + N];

		}

	MATRIX c11; SetMemory(&c11,N, N);
	MATRIX c12; SetMemory(&c12,N, N);
	MATRIX c21; SetMemory(&c21,N, N);
	MATRIX c22; SetMemory(&c22,N, N);

	MATRIX dop11_1;
	MATRIX dop11_2;
	MATRIX dop12_1;
	MATRIX dop12_2;
	MATRIX dop21_1;
	MATRIX dop21_2;
	MATRIX dop22_1;
	MATRIX dop22_2;

	 Summation(SimpleDnCMultiplication(&a11, &b11, &dop11_1), SimpleDnCMultiplication(&a12, &b21,&dop11_2 ), &c11);
	 Summation(SimpleDnCMultiplication(&a11, &b12,&dop12_1), SimpleDnCMultiplication(&a12, &b22,&dop12_2), &c12);
	 Summation(SimpleDnCMultiplication(&a21, &b11,&dop21_1), SimpleDnCMultiplication(&a22, &b21,&dop21_2),&c21);
	 Summation(SimpleDnCMultiplication(&a21, &b12,&dop22_1), SimpleDnCMultiplication(&a22, &b22,&dop22_2), &c22);


	 FreeMemory(&dop11_1);
	 FreeMemory(&dop11_2);
	 FreeMemory(&dop12_1);
	 FreeMemory(&dop12_2);
	 FreeMemory(&dop21_1);
	 FreeMemory(&dop21_2);
	 FreeMemory(&dop22_1);
	 FreeMemory(&dop22_2);


	FreeMemory(&a11);
	FreeMemory(&a12);
	FreeMemory(&a21);
	FreeMemory(&a22);
	FreeMemory(&b11);
	FreeMemory(&b12);
	FreeMemory(&b21);
	FreeMemory(&b22);


	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			result->mas[i][j] = c11.mas[i][j];
			result->mas[i][j + N] = c12.mas[i][j];
			result->mas[i + N][j] = c21.mas[i][j];
			result->mas[i + N][j + N] = c22.mas[i][j];
		}

	FreeMemory(&c11);
	FreeMemory(&c12);
	FreeMemory(&c21);
	FreeMemory(&c22);

	return result;
}
