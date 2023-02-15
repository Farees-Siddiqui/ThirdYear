#include <stdio.h>
#include <omp.h>

int main (void)
{
    int i = 10;
    omp_set_num_threads(4);

    #pragma omp parallel firstprivate(i)
    {
        printf("thread %d: i = %d\n", omp_get_thread_num(), i);
        i = 1000 + omp_get_thread_num();
    }

    printf("i = %d\n", i);
    int a = 7, b = 5;

    return 0;
}