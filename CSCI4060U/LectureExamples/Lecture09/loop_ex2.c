#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 8

int main () {
  int i;
  double result[NUM_THREADS];
  omp_set_num_threads(NUM_THREADS);

  #pragma omp parallel 
  {
    int thread_id = omp_get_thread_num();
    #pragma omp for
    for (i=0; i< NUM_THREADS; i++) {
        result[i] = 56*67*(i+1); //first rewrite the below code so that loop
                                //iterations are independent
        /*if (i != 0) {
            result[i] = 56*67 + result[i-1];

        } else {
            result[i] = 56*67;
        }*/
        printf("result for thread %d, iteration %d is %f\n", 
                thread_id, i, result[i]);
    }
  }
  return 0;
}