#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Matrix.h"


#define SIZE 128

int main()
{
	srand(time(NULL));
	//SuperTest();

	MATRIX matr1 = CreateRandomMatrix(0, 100, 100, 100);
	MATRIX matr2 = CreateRandomMatrix(0, 100, 100, 100);

	//PrintMatrix(matr1);
	//PrintMatrix(matr2);

	//PrintMatrix(NaiveMultiplication(matr1, matr2));
	//PrintMatrix(VinogradMultiplication(matr1,matr2));

	double start = clock(), ResultTime;

	
	MATRIX result= NaiveMultiplication(matr1, matr2);
		//SuperTest();

	time_t end = time(0);
	printf("%lf\n",(ResultTime= (clock()-start))); //CLK_TCK
	printf("%lf\n", (ResultTime = (clock() - start)/CLOCKS_PER_SEC));

	return 0;
}