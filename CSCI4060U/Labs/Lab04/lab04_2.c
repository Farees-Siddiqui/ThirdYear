#include <stdio.h>
#include <math.h>
#ifdef _OPENMP
    #include <omp.h>
#else
    #define omp_get_thread_num() 0
    #define omp_get_num_threads() 1
#endif

int fib(int n) {
    if (n <= 1) {
        return n;
    } 
    if (n < 20) // Called as child tasks can be thought of as a cutoff point
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
    omp_set_num_threads(4);
    #pragma omp parallel
    {
        #pragma omp single
        {
            printf("%d ", fib(30));
        }
    }
    return 0;
}

