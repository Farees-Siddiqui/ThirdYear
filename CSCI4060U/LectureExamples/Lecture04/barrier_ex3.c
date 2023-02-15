#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#ifdef _OPENMP
    #include <omp.h>
#else
    #define omp_get_num_threads() 1
    #define omp_get_thread_num() 0
#endif

int calcGrade(int i);
int calcOtherAvg(int i, int *g);


int main() {
    //OpenMP usually takes the form of...
    //#pragma omp <construct> [<clause> ...]

    #ifdef _OPENMP
        omp_set_num_threads(32);
    #endif

    int Grades[omp_get_num_threads()];

    #pragma omp parallel 
    {
        int threadID = omp_get_thread_num();
        Grades[threadID] = calcGrade(threadID);
        printf("Student %d\tGrade %d\n", threadID, Grades[threadID]);
    }
    printf("Program complete.\n");
    return 0;
}

int calcGrade(int i) {
    srand(time(NULL));
    return (rand()%101);
}

int calcOtherAvg(int i, int *g) {
    return 0;
}