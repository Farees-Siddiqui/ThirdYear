#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 8

int main () {
  int i;
  double result[NUM_THREADS];
  double results2[NUM_THREADS];

  omp_set_num_threads(NUM_THREADS);

  #pragma omp parallel 
  {
    #pragma omp for nowait
    for (i=0; i< NUM_THREADS; i++) {
        printf("LOOP 1: start of iteration %d\n", i);        
        result[i] = 56*67*(i+1);
        printf("LOOP 1: result for iteration %d is %f\n", 
                i, result[i]);
    }
    //There is an implict barrier after a parallel for loop
    //It can be removed by using a nowait clause in the first loop
    #pragma omp for
    for (i=0; i< NUM_THREADS; i++) {
        printf("LOOP 2: start of iteration %d\n", i);        
        result[i] = 6*6*(i);
        printf("LOOP 2: result for iteration %d is %f\n", 
                i, result[i]);
    }
  }
  return 0;
}