#include <stdio.h>
#ifdef _OPENMP
    #include <omp.h>
#else
    #define omp_get_num_threads() 1
    #define omp_get_thread_num() 0
#endif

void output(int ID);

int main() {
    //OpenMP usually takes the form of...
    //#pragma omp <construct> [<clause> ...]

    #ifdef _OPENMP
        omp_set_num_threads(32);
    #endif
    #pragma omp parallel
    {
        int threadID = omp_get_thread_num();
        if (threadID < omp_get_num_threads()/2) {
            for (int i=0; i < 100000000; i++) {
               //do nothing :)
            }
        }
        output(threadID);
    }
    printf("Program complete.\n");
    return 0;
}

void output(int ID) {
    printf("hello (thread %d)\n", ID);
    #pragma omp barrier
    //the barrier causes all threads to wait
    //until all other threads have caught up
    //before proceeding
    printf("good bye (thread %d)\n", ID);
}