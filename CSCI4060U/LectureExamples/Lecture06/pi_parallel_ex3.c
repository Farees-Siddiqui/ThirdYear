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
  int thread_count;
  
  //change in x (i.e., width of the rectange)
  step = 1.0/(double)num_steps;

  omp_set_num_threads(NUM_THREADS);
  #pragma omp parallel
  { 
    int thread_id;
    int t_count;
    double x;

    t_count = omp_get_num_threads();
    thread_id = omp_get_thread_num();

    if ((thread_id) == 0){
        thread_count = t_count;
    }

    //calculate the summation of F(x)
    //(i.e., sum of the rectangles)
    //(i.e., the approximation of pi)
    double sum = 0.0;
    for (int i = thread_id; i < num_steps; i = i + t_count) {
      x = (i+0.5)*step;
      sum = sum + 4/(1.0+x*x);
    }
    #pragma omp critical
    {
        pi += step * sum;  //putting this in a critical block
                            //ensures only one thread at a time
                            //can access pi
    }    
    
  }
  printf("pi = %f\n", pi);
}