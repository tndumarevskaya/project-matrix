#define _CRT_SECURE_NO_WARNINGS
#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


MATRIX allocatedMemory(int m, int n)
{
	MATRIX math;
	math.matr = (int**)malloc(m * sizeof(int*));
	for (int i = 0; i < m; ++i)
		math.matr[i] = (int*)malloc(n * sizeof(int));
	math.m = m;
	math.n = n;
	return math;
};

MATRIX freeMemory(MATRIX math)
{
	for (int i = 0; i < math.m; ++i)
		free(math.matr[i]);
	free(math.matr);
	return math;
};

MATRIX createMatrix(MATRIX math)
{
	for (int i = 0; i < math.m; ++i)
	{
		for (int j = 0; j < math.n; ++j)
			math.matr[i][j] = rand() % 100;
	}
	return math;
};

void printMatrix(MATRIX math)
{
	for (int i = 0; i < math.n; ++i)
	{
		for (int j = 0; j < math.m; ++j)
		{
			printf("%d ", math.matr[i][j]);
		}
		printf("\n");
	}
};

MATRIX naive(MATRIX a, MATRIX b, MATRIX c)
{
	for (int i = 0; i < a.m; ++i)
	{
		for (int j = 0; j < b.n; ++j)
		{
			c.matr[i][j] = 0;
			for (int k = 0; k < a.n; ++k)
				c.matr[i][j] += a.matr[i][k] * b.matr[k][j];
		}
	}
	return c;
};


MATRIX sumMatrix(MATRIX a, MATRIX b, MATRIX c)
{
	for (int i = 0; i < a.m; ++i)
	{
		for (int j = 0; j < b.n; ++j)
			c.matr[i][j] = a.matr[i][j] + b.matr[i][j];
	}
	return c;
};

MATRIX subMatrix(MATRIX a, MATRIX b, MATRIX c)
{
	for (int i = 0; i < a.m; ++i)
	{
		for (int j = 0; j < b.n; ++j)
			c.matr[i][j] = a.matr[i][j] - b.matr[i][j];
	}
	return c;
};

MATRIX dncSimple(MATRIX a, MATRIX b)
{	
	MATRIX c;
	c = allocatedMemory(a.m, a.n);
	if (a.m == 1)
	{
		c.matr[0][0] = a.matr[0][0] * b.matr[0][0];
		return c;
	}

	int n = a.m / 2;

	MATRIX a11, a12, a21, a22, b11, b12, b21, b22;

	a11 = allocatedMemory(n, n);
	a12 = allocatedMemory(n, n);
	a21 = allocatedMemory(n, n);
	a22 = allocatedMemory(n, n);
	b11 = allocatedMemory(n, n);
	b12 = allocatedMemory(n, n);
	b21 = allocatedMemory(n, n);
	b22 = allocatedMemory(n, n);

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			a11.matr[i][j] = a.matr[i][j];
			b11.matr[i][j] = b.matr[i][j];
			a12.matr[i][j] = a.matr[i][j + n];
			b12.matr[i][j] = b.matr[i][j + n];
			a21.matr[i][j] = a.matr[i + n][j];
			b21.matr[i][j] = b.matr[i + n][j];
			a22.matr[i][j] = a.matr[i + n][j + n];
			b22.matr[i][j] = b.matr[i + n][j + n];
		}
	}

	MATRIX c11, c12, c21, c22;

	c11 = allocatedMemory(n, n);
	c12 = allocatedMemory(n, n);
	c21 = allocatedMemory(n, n);
	c22 = allocatedMemory(n, n);

	c11 = sumMatrix(dncSimple(a11, b11), dncSimple(a12, b21), c11);
	c12 = sumMatrix(dncSimple(a11, b12), dncSimple(a12, b22), c12);
	c21 = sumMatrix(dncSimple(a21, b11), dncSimple(a22, b21), c21);
	c22 = sumMatrix(dncSimple(a21, b12), dncSimple(a22, b22), c22);

	a11 = freeMemory(a11);
	a12 = freeMemory(a12);
	a21 = freeMemory(a21);
	a22 = freeMemory(a22);
	b11 = freeMemory(b11);
	b12 = freeMemory(b12);
	b21 = freeMemory(b21);
	b22 = freeMemory(b22);

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			c.matr[i][j] = c11.matr[i][j];
			c.matr[i][j + n] = c12.matr[i][j];
			c.matr[i + n][j] = c21.matr[i][j];
			c.matr[i + n][j + n] = c22.matr[i][j];
		}
	}

	c11 = freeMemory(c11);
	c12 = freeMemory(c12);
	c21 = freeMemory(c21);
	c22 = freeMemory(c22);

	return c;
};



MATRIX Strassena(MATRIX a, MATRIX b)
{
	int n = a.m / 2;
	MATRIX c;
	c = allocatedMemory(a.m, b.n);

	if (a.m <= 64)
		return naive(a, b, c);

	MATRIX a11, a12, a21, a22, b11, b12, b21, b22;

	a11 = allocatedMemory(n, n);
	a12 = allocatedMemory(n, n);
	a21 = allocatedMemory(n, n);
	a22 = allocatedMemory(n, n);
	b11 = allocatedMemory(n, n);
	b12 = allocatedMemory(n, n);
	b21 = allocatedMemory(n, n);
	b22 = allocatedMemory(n, n);

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			a11.matr[i][j] = a.matr[i][j];
			b11.matr[i][j] = b.matr[i][j];
			a12.matr[i][j] = a.matr[i][j + n];
			b12.matr[i][j] = b.matr[i][j + n];
			a21.matr[i][j] = a.matr[i + n][j];
			b21.matr[i][j] = b.matr[i + n][j];
			a22.matr[i][j] = a.matr[i + n][j + n];
			b22.matr[i][j] = b.matr[i + n][j + n];
		}
	}

	MATRIX p1, p2, p3, p4, p5, p6, p7;

	p1 = allocatedMemory(n, n);
	p2 = allocatedMemory(n, n);
	p3 = allocatedMemory(n, n);
	p4 = allocatedMemory(n, n);
	p5 = allocatedMemory(n, n);
	p6 = allocatedMemory(n, n);
	p7 = allocatedMemory(n, n);

	p1 = Strassena(sumMatrix(a11, a22, p1), sumMatrix(b11, b22, p1));
	p2 = Strassena(sumMatrix(a21, a22, p2), b11);
	p3 = Strassena(a11, subMatrix(b12, b22, p3));
	p4 = Strassena(a22, subMatrix(b21, b11, p4));
	p5 = Strassena(sumMatrix(a11, a12, p5), b22);
	p6 = Strassena(subMatrix(a21, a11, p6), sumMatrix(b11, b12, p6));
	p7 = Strassena(subMatrix(a12, a21, p7), sumMatrix(b21, b22, p7));

	MATRIX c11, c12, c21, c22;

	c11 = allocatedMemory(n, n);
	c12 = allocatedMemory(n, n);
	c21 = allocatedMemory(n, n);
	c22 = allocatedMemory(n, n);

	c11 = sumMatrix(sumMatrix(p1, p4, c11), subMatrix(p7, p5, c11), c11);
	c12 = sumMatrix(p3, p5, c12);
	c21 = sumMatrix(p2, p4, c21);
	c22 = sumMatrix(subMatrix(p1, p2, c22), sumMatrix(p3, p6, c22), c22);

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			c.matr[i][j] = c11.matr[i][j];
			c.matr[i][j + n] = c12.matr[i][j];
			c.matr[i + n][j] = c21.matr[i][j];
			c.matr[i + n][j + n] = c22.matr[i][j];
		}
	}

	a11 = freeMemory(a11);
	a12 = freeMemory(a12);
	a21 = freeMemory(a21);
	a22 = freeMemory(a22);
	b11 = freeMemory(b11);
	b12 = freeMemory(b12);
	b21 = freeMemory(b21);
	b22 = freeMemory(b22);
	c11 = freeMemory(c11);
	c12 = freeMemory(c12);
	c21 = freeMemory(c21);
	c22 = freeMemory(c22);
	p1 = freeMemory(p1);
	p2 = freeMemory(p2);
	p3 = freeMemory(p3);
	p4 = freeMemory(p4);
	p5 = freeMemory(p5);
	p6 = freeMemory(p6);
	p7 = freeMemory(p7);

	return c;
}

void Compare(MATRIX c, MATRIX c1, MATRIX c2)
{
	int f = 0;
	for (int i = 0; i < c.n; i++)
	{
		for (int j = 0; j < c.m; j++)
		{
			if (c.matr[i][j] != c1.matr[i][j] || c.matr[i][j] != c2.matr[i][j] || c1.matr[i][j] != c2.matr[i][j])
			{
				printf("fail");
				f = 1;
				return;
			}
		}
	}

	if (f == 0)
		printf("true");
}