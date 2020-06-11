#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Matrix.h"


#define SIZE 2

int main()
{
	srand(time(NULL));


	TestCorrect();
	TestingSystem();
	//TestNaiveAndVinograd();
	return 0;
}