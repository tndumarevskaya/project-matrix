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
    TestingSystem();

    return 0;
}
