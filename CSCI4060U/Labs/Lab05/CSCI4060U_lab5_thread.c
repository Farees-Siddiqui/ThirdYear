#include <stdio.h> // Included for input/output functions such as printf
#include <stdlib.h> // Included for the exit() function
#include <pthread.h> // included for the posix threading api

#define THREADS 100000

/*
  Timing: CPU Time => 0.191s + 3.277s = 3.468s
          Real Time => 6.869s
*/

// do nothing function, does nothing just for testing
void *do_nothing(void *);

int main() {
    // create a thread
    pthread_t thread;
    // status of the thread
    void *status;

    // create THREADS threads and join them using a for loop
    for (int i = 0; i < THREADS; i++) {
        // create the thread and check the error code, if there is an error print an error message and exit
        if (pthread_create(&thread, NULL, do_nothing, NULL) != 0) {
            printf("Error creating thread\n");
            exit(-1);
        }
        // join the thread and check the error code, if there is an error print an error message and exit
        if (pthread_join(thread, &status) != 0) {
            printf("Error joining thread\n");
            exit(-1);
        }
    }

    printf("All threads complete\n");
    pthread_exit(NULL);
}

void *do_nothing(void *arg) {
    int i;
    i = 0;
}