#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Matrix.h"



MATRIX CreateRandomMatrix(int LeftBorder, int RightBorder, int n, int m)
{

	MATRIX matr;
	matr.n = n;
	matr.m = m;

	matr.mas = (int**)malloc(n * sizeof(int*));

	for (int i = 0; i < n; i++)
		matr.mas[i] = (int*)malloc(m * sizeof(int));

	//srand(rand());
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			matr.mas[i][j] = LeftBorder + rand() % (RightBorder - LeftBorder);

	return matr;
}

bool MultiplicationCheck(MATRIX a, MATRIX b)
{
	if (a.m == b.n)
		return 1;
	else
		return 0;
}

void PrintMatrix(MATRIX matr)
{
	for (int i = 0; i < matr.n; i++)
	{
		for (int j = 0; j < matr.m; j++)
			printf("%d  ", matr.mas[i][j]);
		printf("\n");
	}

	printf("\n\n");
}

MATRIX Summation(MATRIX a, MATRIX b)
{
	MATRIX result;
	result.n = a.n;
	result.m = b.m;

	result.mas = (int**)malloc(result.n * sizeof(int*));

	for (int i = 0; i < result.n; i++)
		result.mas[i] = (int*)malloc(result.m * sizeof(int));


	if (a.n != b.n || a.m != b.m)
	{
		printf("Summation ERROR");

	}

	for (int i = 0; i < result.n; i++)
		for (int j = 0; j < result.m; j++)
			result.mas[i][j] = a.mas[i][j] + b.mas[i][j];

	return result;
}

MATRIX Subtraction(MATRIX a, MATRIX b)
{
	MATRIX result;
	result.n = a.n;
	result.m = b.m;

	result.mas = (int**)malloc(result.n * sizeof(int*));

	for (int i = 0; i < result.n; i++)
		result.mas[i] = (int*)malloc(result.m * sizeof(int));


	if (a.n != b.n || a.m != b.m)
	{
		printf("Subtration ERROR");
		
	}

	for (int i = 0; i < result.n; i++)
		for (int j = 0; j < result.m; j++)
			result.mas[i][j] = a.mas[i][j] - b.mas[i][j];

	return result;
}

MATRIX SetMemory( int N, int M)
{
	MATRIX a;
	a.n = N;
	a.m = M;
	a.mas = (int**)malloc(N * sizeof(int*));
	for (int i = 0; i < N; i++)
		a.mas[i] = (int*)malloc(M * sizeof(int));
	return a;
}

void FreeMemory(MATRIX math)
{
	for (int i = 0; i < math.n; ++i)
		free(math.mas[i]);
	free(math.mas);

};

MATRIX Transposion(MATRIX matr)
{
	MATRIX transmatr = SetMemory(matr.m, matr.n);

	for (int i = 0; i < transmatr.n; i++)
		for (int j = 0; j < transmatr.m; j++)
			transmatr.mas[i][j] = matr.mas[j][i];

	return transmatr;
}

MATRIX NaiveMultiplication(MATRIX matr1, MATRIX matr2)
{
	if (!MultiplicationCheck(matr1, matr2))
	{
		printf("Multiplication ERROR");
		//////
	}

	MATRIX result;
	result.n = matr1.n;
	result.m = matr2.m;

	result.mas = (int**)malloc(result.n * sizeof(int*));

	for (int i = 0; i < result.n; i++)
		result.mas[i] = (int*)malloc(result.m * sizeof(int));

	for (int i = 0; i < result.n; i++)
		for (int j = 0; j < result.m; j++)
		{
			result.mas[i][j] = 0;
			for (int k = 0; k < matr1.m; k++)
				result.mas[i][j] = result.mas[i][j] + matr1.mas[i][k] * matr2.mas[k][j];
		}
	return result;
}

MATRIX SimpleDnCMultiplication(MATRIX a, MATRIX b)
{
	if (a.n <= 1) 
		return NaiveMultiplication(a, b);

	int N = a.n / 2;

	MATRIX a11 = SetMemory(N, N);
	MATRIX a12 = SetMemory(N, N);
	MATRIX a21 = SetMemory(N, N);
	MATRIX a22 = SetMemory(N, N);

	MATRIX b11 = SetMemory(N, N);
	MATRIX b12 = SetMemory(N, N);
	MATRIX b21 = SetMemory(N, N);
	MATRIX b22 = SetMemory(N, N);

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			a11.mas[i][j] = a.mas[i][j];
			b11.mas[i][j] = b.mas[i][j];
			a12.mas[i][j] = a.mas[i][j + N];
			b12.mas[i][j] = b.mas[i][j + N];
			a21.mas[i][j] = a.mas[i + N][j];
			b21.mas[i][j] = b.mas[i + N][j];
			a22.mas[i][j] = a.mas[i + N][j + N];
			b22.mas[i][j] = b.mas[i + N][j + N];

		}

	MATRIX c11 = SetMemory(N, N);
	MATRIX c12 = SetMemory(N, N);
	MATRIX c21 = SetMemory(N, N);
	MATRIX c22 = SetMemory(N, N);

	c11 = Summation(SimpleDnCMultiplication(a11, b11), SimpleDnCMultiplication(a12, b21));
	c12 = Summation(SimpleDnCMultiplication(a11, b12), SimpleDnCMultiplication(a12, b22));
	c21 = Summation(SimpleDnCMultiplication(a21, b11), SimpleDnCMultiplication(a22, b21));
	c22 = Summation(SimpleDnCMultiplication(a21, b12), SimpleDnCMultiplication(a22, b22));

	FreeMemory(a11);
	FreeMemory(a12);
	FreeMemory(a21);
	FreeMemory(a22);
	FreeMemory(b11);
	FreeMemory(b12);
	FreeMemory(b21);
	FreeMemory(b22);

	MATRIX result = SetMemory(N * 2, N * 2);

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			result.mas[i][j] = c11.mas[i][j];
			result.mas[i][j + N] = c12.mas[i][j];
			result.mas[i + N][j] = c21.mas[i][j];
			result.mas[i + N][j + N] = c22.mas[i][j];
		}

	FreeMemory(c11);
	FreeMemory(c12);
	FreeMemory(c21);
	FreeMemory(c22);

	return result;
}

MATRIX StrassenMultiplication(MATRIX a, MATRIX b)
{
	if (a.n <= 64) 
		return NaiveMultiplication(a, b);

	int N = a.n/2;

	MATRIX a11 = SetMemory(N, N); 
	MATRIX a12 = SetMemory(N, N);
	MATRIX a21 = SetMemory(N, N);
	MATRIX a22 = SetMemory(N, N);

	MATRIX b11 = SetMemory(N, N);
	MATRIX b12 = SetMemory(N, N);
	MATRIX b21 = SetMemory(N, N);
	MATRIX b22 = SetMemory(N, N);

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			a11.mas[i][j] = a.mas[i][j];
			b11.mas[i][j] = b.mas[i][j];
			a12.mas[i][j] = a.mas[i][j+N];
			b12.mas[i][j] = b.mas[i][j+N];
			a21.mas[i][j] = a.mas[i+N][j];
			b21.mas[i][j] = b.mas[i+N][j];
			a22.mas[i][j] = a.mas[i + N][j+N];
			b22.mas[i][j] = b.mas[i + N][j+N];

		}


	MATRIX p1 = SetMemory(N, N);
	MATRIX p2 = SetMemory(N, N);
	MATRIX p3 = SetMemory(N, N);
	MATRIX p4 = SetMemory(N, N);
	MATRIX p5 = SetMemory(N, N);
	MATRIX p6 = SetMemory(N, N);
	MATRIX p7 = SetMemory(N, N);

	p1 = StrassenMultiplication(Summation(a11, a22), Summation(b11, b22));
	p2 = StrassenMultiplication(Summation(a21, a22), b11);
	p3 = StrassenMultiplication(a11, Subtraction(b12,b22));
	p4 = StrassenMultiplication(a22, Subtraction(b21, b11));
	p5 = StrassenMultiplication(Summation(a11, a12), b22);
	p6 = StrassenMultiplication(Subtraction(a21, a11), Summation(b11, b12));
	p7 = StrassenMultiplication(Subtraction(a12, a22), Summation(b21, b22));

	FreeMemory(a11);
	FreeMemory(a12);
	FreeMemory(a21);
	FreeMemory(a22);
	FreeMemory(b11);
	FreeMemory(b12);
	FreeMemory(b21);
	FreeMemory(b22);


	MATRIX c11 = SetMemory(N, N);
	MATRIX c12 = SetMemory(N, N);
	MATRIX c21 = SetMemory(N, N);
	MATRIX c22 = SetMemory(N, N);

	c11 = Summation(Subtraction(p4, p5), Summation(p1, p7));
	c12 = Summation(p3, p5);
	c21 = Summation(p2, p4);
	c22 = Summation(Subtraction(p1, p2), Summation(p3, p6));

	FreeMemory(p1);
	FreeMemory(p2);
	FreeMemory(p3);
	FreeMemory(p4);
	FreeMemory(p5);
	FreeMemory(p6);
	FreeMemory(p7);

	MATRIX result = SetMemory(N*2, N*2);

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			result.mas[i][j] = c11.mas[i][j];
			result.mas[i][j + N] = c12.mas[i][j];
			result.mas[i + N][j] = c21.mas[i][j];
			result.mas[i + N][j + N] = c22.mas[i][j];
		}

	FreeMemory(c11);
	FreeMemory(c12);
	FreeMemory(c21);
	FreeMemory(c22);


	return result;
}

void SuperTest()
{
#define TESTS 20
#define TESTSIZE 16
	for (int k = 0; k < TESTS; k++)
	{
		//сюда нужно добавить генерацию рандомных диапазонов значений для матриц и генерацию рандомных размеров матриц
		MATRIX matr1 = CreateRandomMatrix(0, 100, TESTSIZE, TESTSIZE);
		MATRIX matr2 = CreateRandomMatrix(0, 100, TESTSIZE, TESTSIZE);

		MATRIX naive = NaiveMultiplication(matr1, matr2);
		MATRIX DnC = SimpleDnCMultiplication(matr1, matr2);
		MATRIX Strassen = StrassenMultiplication(matr1, matr2);
		for (int i = 0; i < TESTSIZE; i++)
			for (int j = 0; j < TESTSIZE; j++)
				if (naive.mas[i][j] != DnC.mas[i][j] || naive.mas[i][j] != Strassen.mas[i][j] || DnC.mas[i][j] != Strassen.mas[i][j])
					printf("TEST %d FAILED", k);

		FreeMemory(matr1);
		FreeMemory(matr2);
		FreeMemory(naive);
		FreeMemory(DnC);
		FreeMemory(Strassen);
	}
}


