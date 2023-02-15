#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 8

int main () {
  int i;
  double result[NUM_THREADS];
 
  #pragma omp parallel for ordered
   for (i=0; i< NUM_THREADS; i++) {
        result[i] = 56*67 + i;
        #pragma omp ordered
        {
          printf("result for iteration %d is %f\n", 
                i, result[i]);
        }
    }


 /*sequential code
    for (i=0; i< NUM_THREADS; i++) {
        result[i] = 56*67 + i;
        printf("result for iteration %d is %f\n", 
                i, result[i]);
    }
 */
  return 0;
}