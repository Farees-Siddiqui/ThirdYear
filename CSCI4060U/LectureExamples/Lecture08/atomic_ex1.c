#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 16

float firstWork(int i);
float secondWork(int i);

void critical_example(float *x, float *y, int *index, int n);
void atomic_example(float *x, float *y, int *index, int n);

int main () {
  float x[10000];
  float y[1000000];
  int index[1000000];
  int i;

  omp_set_num_threads(NUM_THREADS);

  //initalize arrays
  for (i=0; i < 1000000; i++) {
    index[i] = i%10000;
    y[i] = 0.0;
    if (i < 10000) {
        x[i] = 0.0;
    }
  }

  //Do stuff in parallel
  atomic_example(x, y, index, 1000000);
  //critical_example(x, y, index, 1000000);

  //Print results
 /* printf("y results:\n");
  for (i=0; i < 1000000; i++) {
    printf("%f\n", y[i]);
  }
  printf("x results:\n");
  for (i=0; i < 10000; i++) {
    printf("%f\n", x[i]);
  }*/
  return 0;
}

float firstWork(int i) {
    return (1.12 * i);
}

float secondWork(int i) {
    return (1.07 * i);
}

void critical_example(float *x, float *y, int *index, int n) {
    #pragma omp parallel for shared(x, y, index, n)
    for (int i=0; i < n; i++) {
        #pragma omp critical //Don't do this please :)
        {
            x[index[i]] += firstWork(i);
        }
        y[i] += secondWork(i);
    }
}

void atomic_example(float *x, float *y, int *index, int n) {
    #pragma omp parallel for shared(x, y, index, n)
    for (int i=0; i < n; i++) {
        #pragma omp atomic update
            x[index[i]] += firstWork(i);
        y[i] += secondWork(i);
    }
}