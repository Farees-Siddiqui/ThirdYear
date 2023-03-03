#include <stdio.h>
#include <math.h>
#ifdef _OPENMP
    #include <omp.h>
#else
    #define omp_get_thread_num() 0
    #define omp_get_num_threads() 1
#endif

/*
@Author: Farees Siddiqui
The following slides were referenced for cutoff optimization: https://www.eidos.ic.i.u-tokyo.ac.jp/~iwasaki/files/PACT2016_slides.pdf
 */

int fib(int n) {
    if (n <= 1) {
        return n;
    } 
    if (n < 20) // Cut-off point
        return fib(n-1)+fib(n-2); 
    int x, y;
    #pragma omp task shared(x)
    x = fib(n-1);
    #pragma omp task shared(y)
    y = fib(n-2);
    #pragma omp taskwait
    return x + y;
}

int main() {
    omp_set_num_threads(8);
    #pragma omp parallel
    {
        #pragma omp single
        {
            printf("%d ", fib(30));
        }
    }
    return 0;
}

