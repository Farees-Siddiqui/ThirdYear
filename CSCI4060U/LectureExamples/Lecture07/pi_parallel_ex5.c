#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 8
//Padding is necessary to account for cache line size (likely 64 bytes)
//We use this to avoid copies back and forth between cores/threads
//i.e., due to updating of adjacent array elements
static long num_steps = 1000000; //num rectangles
double step;

int main () {
  double pi = 0.0; //shared variable accessed by all threads
                    //in a critical region
  double sum = 0.0;
  int thread_count;
  
  //change in x (i.e., width of the rectange)
  step = 1.0/(double)num_steps;

  omp_set_num_threads(NUM_THREADS);
  #pragma omp parallel
  { 
    double x;

    //calculate the summation of F(x)
    //(i.e., sum of the rectangles)
    //(i.e., the approximation of pi)
    #pragma omp for reduction (+:sum)
    for (int i = 0; i < num_steps; i++) {
      x = (i+0.5)*step;
      sum = sum + 4/(1.0+x*x);
    } 
    
  }
  pi = step * sum;
  printf("pi = %f\n", pi);
}