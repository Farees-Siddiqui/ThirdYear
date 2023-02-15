#include <stdio.h>
#include <omp.h>

void output(int ID);

int main() {
    //OpenMP usually takes the form of...
    //#pragma omp <construct> [<clause> ...]

    omp_set_num_threads(32);
    #pragma omp parallel
    {
        int threadID = omp_get_thread_num();
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