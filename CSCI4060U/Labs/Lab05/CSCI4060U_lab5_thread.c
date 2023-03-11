// We include stdio.h for input/output functions such as printf()
#include <stdio.h>
// We include stdlib.h so we can define exit() and exit codes
#include <stdlib.h>
// We include pthreads.h so we can use the pthreads api for thread creation and management
#include <pthread.h>

// define the number of threads we want to create
#define THREADS 100000

/*
    Timing: CPU Time => 0.285s + 30.776s = 31.061s
            Real Time => 27.754s
 */


// This function does nothing, just used to test the program.
void *do_nothing(void *args) {
    int i;
    i = 0;
}

int main() {
    // here we declare the number of threads we want to create
    pthread_t threads[THREADS];
    long i;
    int error;
    
    // Use a for loop to create THREADS number of threads
    for (i = 0; i < THREADS; i++) {
        // create the thread and check the return value for errors
        error = pthread_create(&threads[i], NULL, do_nothing, NULL);
        // Log if there was an error in the thread creation and exit with a code of -1
        if (error) {
            printf("ERROR: pthread_create()\n");
            exit(-1);
        }
    }

    // Use a for loop to join the threads
    for (i = 0; i < THREADS; i++) {
        // join the thread and check the return value for errors
        error = pthread_join(threads[i], NULL);
        // Log if there was an error in the thread join and exit with a code of -1
        if (error) {
            printf("ERROR: pthread_join()\n");
            exit(-1);
        }
    }

    printf("Threads completed, and joined successfully.\n");
    // exit the main thread
    pthread_exit(NULL);


    return 0;
}