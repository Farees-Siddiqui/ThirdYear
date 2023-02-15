#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 8

int main () {
  int i;
  double result[NUM_THREADS];
  omp_set_num_threads(NUM_THREADS);
  int x = 8;

    #pragma omp parallel for if (x > 4)
     for (i=0; i< NUM_THREADS; i++) {
        result[i] = 56*67 + i;
        printf("[thread: %d]result for iteration %d is %f\n", omp_get_thread_num(), i, result[i]);
     }
  return 0;
}