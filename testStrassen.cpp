#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Matrix.h"

#define SIZE 512

int main()
{
	srand(time(NULL));
	

	MATRIX matr1;
	MATRIX matr2;
	CreateRandomMatrix(&matr1, 0, 10, SIZE, SIZE);
	CreateRandomMatrix(&matr2, 0, 10, SIZE, SIZE);
	
	double start = clock();
	MATRIX result;
	PrintMatrix(SimpleDnCMultiplication(&matr1, &matr2, &result));
	printf("%.3lf", (clock() - start )/ CLOCKS_PER_SEC);

	//FreeMemory(&result);
	//PrintMatrix(NaiveMultiplication(&matr1, &matr2, &result));

	return 0;
}