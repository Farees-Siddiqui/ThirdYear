#include <stdio.h>

#ifdef _OPENMP
    #include <omp.h>
#else
    #define omp_get_thread_num() 0
    #define omp_get_num_threads() 1
#endif

static long num_steps = 1000000;
double step;
double pi;

int main() {
    double x;
    double sum = 0.0;

    #ifdef _OPENMP
        omp_set_num_threads(2);
    #endif
    #pragma omp parallel
    {
        printf("OpenMP is loaded. Using (%d threads)\n", omp_get_num_threads());
        //change in x (i.e. width of rectangle)
        step = 1.0/(double)num_steps;

        //calculate the summation of F(x)
        // (i.e. sum of rectangles)
        //in the approximation of pi
        #pragma omp for reduction(+:sum)
        for (int i=0; i < num_steps; i++) {
            //calculate height
            x = (i+0.5)*step;
            sum = sum + 4/(1.0+x*x); //sum F(x)
        }
    }
    pi = step * sum;
    printf("pi = %f\t (Thread: %d)\n", pi, omp_get_thread_num());
}