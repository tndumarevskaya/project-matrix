#define _CRT_SECURE_NO_WARNINGS
#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	srand(time(0));
	MATRIX a, b;
	int n, m;

	puts("enter m, n:");
	scanf("%d%d", &m, &n);

	a = allocatedMemory(m, n);
	b = allocatedMemory(m, n);
	a = createMatrix(a);
	b = createMatrix(b);

	printMatrix(a);
	printf("\n");
	printMatrix(b);
	printf("\n");

	MATRIX c;
	c = allocatedMemory(a.m, a.n);
	c = naive(a, b, c);
	c.m = m;
	c.n = n;
	printMatrix(c);

	printf("\n");
	printf("\n");

	MATRIX c1;
	c1 = allocatedMemory(a.m, a.n);
	c1.m = m;
	c1.n = n;
	c1 = dncSimple(a, b);
	printMatrix(c1);

	printf("\n");
	printf("\n");


	MATRIX c2;
	c2 = allocatedMemory(a.m, a.n);
	c2.m = m;
	c2.n = n;
	c2 = Strassena(a, b);
	printMatrix(c2);

	Compare(c, c1, c2);

	freeMemory(a);
	freeMemory(b);
	freeMemory(c);
	freeMemory(c1);
	freeMemory(c2);

	return 0;
}