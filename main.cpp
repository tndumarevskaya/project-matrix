#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Matrix.h"
#include <omp.h>

#define SIZE 2

int main() {
    //omp_set_num_threads(6); //number of threads

    srand(time(NULL));
    //SuperTest();

    //MATRIX matr1 = CreateRandomMatrix(0, 2, SIZE, SIZE);
    //MATRIX matr2 = CreateRandomMatrix(0, 2, SIZE, SIZE);
    //PrintMatrix(matr1);
    //PrintMatrix(matr2);

    //PrintMatrix(StrassenMultiplication(matr1,matr2));

    //printf("%lf", AlgorithmTime(matr1, matr2, 3));


    //SuperTest();
    TestingSystem();

    return 0;
}
