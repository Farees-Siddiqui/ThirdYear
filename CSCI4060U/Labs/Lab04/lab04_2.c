#include <stdio.h>

#ifdef _OPENMP
    #include <omp.h>
#else
    #define omp_get_thread_num() 0
    #define omp_get_num_threads() 1
#endif

int fibonacci(int n) {
    if (n <= 1) {
        return n;
    }
    int x, y;
    #pragma omp task shared(x)
    x = fibonacci(n-1);
    #pragma omp task shared(y)
    y = fibonacci(n-2);
    #pragma omp taskwait
    return x + y;
}

int main() {
    int n = 10; 
    #pragma omp parallel
    {
        #pragma omp single
        {
            for (int i = 0; i < n; i++) {
                #pragma omp task
                {
                    int fib = fibonacci(i);
                    #pragma omp critical
                    printf("%d ", fib);
                }
            }
        }
    }
    return 0;
}