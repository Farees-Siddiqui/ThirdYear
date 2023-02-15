#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 8

int main () {
  int i = 0;
  int j = 0;
  double result[NUM_THREADS][NUM_THREADS];

  omp_set_num_threads(NUM_THREADS);
  //This is a perfectly rectangular nested loop
  //we can parallelize both loops by using a new
  //clause called collapse
  #pragma omp parallel for collapse(2) private(i,j)
  //private means every for thread has own copy of i and j
  for (i=0; i< NUM_THREADS; i++) {
    for (j=0; j < NUM_THREADS; j++) {
        result[i][j] = i * j;
        printf("Index [%d,%d] = %f\n", i, j, result[i][j]);
    }
  }


/*sequential code
  int i = 0;
  int j = 0;
  double result[NUM_THREADS][NUM_THREADS];

  for (i=0; i< NUM_THREADS; i++) {
    for (j=0; j < NUM_THREADS; j++) {
        result[i][j] = i * j;
        printf("Index [%d,%d] = %f\n", i, j, result[i][j]);
    }
  }

  */

  return 0;
}