#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 8

float firstWork(int i);
float secondWork(int i);

void atomic_example(float *x, float *y, int *index, int n);
void critical_example(float *x, float *y, int *index, int n);

int main() {
  float x[1000];
  float y[10000];
  int index[10000];
  int i;

  omp_set_num_threads(NUM_THREADS);

  //initialize arrays
  for (i=0; i < 10000; i++) {
    index[i] = i%1000;
    y[i] = 0.0;
  }

  for (i=0; i < 1000; i++) {
    x[i]= 0.0;
  }

  //Do stuff
  //atomic_example(x, y, index, 10000);
  critical_example(x, y, index, 10000);


  //Print results
  printf("Y RESULTS:" );
  for (i=0; i < 10000; i++) {
    printf("%f\n", y[i]);
  }
  printf("X RESULTS:" );
  for (i=0; i < 1000; i++) {
    printf("%f\n", x[i]);
  }

  return 0;
}

float firstWork(int i) {
  return (1.12 * i);
}

float secondWork(int i){
  return (1.07 * i);
}

void critical_example(float *x, float *y, int *index, int n) {
  #pragma omp parallel for shared(x, y, index, n)
  for (int i=0; i <n; i++) {
    #pragma omp critical
    {
      x[index[i]] += firstWork(i);
    }
    y[i] += secondWork(i);
  }
}


void atomic_example(float *x, float *y, int *index, int n) {
  #pragma omp parallel for shared(x, y, index, n)
  for (int i=0; i <n; i++) {
    #pragma omp atomic update
      x[index[i]] += firstWork(i);
    y[i] += secondWork(i);
  }
}
