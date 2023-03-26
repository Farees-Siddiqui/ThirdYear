#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> //needed for posix threads

#define NUM_THREADS 20

void *hello_world(void *id);

int main()
{
    // Declare threads
    pthread_t threads[NUM_THREADS];

    // Create threads
    // Have threads display a message via function call
    for (long i = 0; i < NUM_THREADS; i++)
    {
        printf("Creating thread %ld\n", i);
        /* format for creating a thread:
            int pthread_create(pthread_t *thread,
                                const pthread_attr_t *attr,
                                void *(*start_routine) (void *),
                                void *arg);
            )
        */
        int error = pthread_create(&threads[i], NULL,
                                   hello_world, (void *)i);
        if (error)
        {
            printf("ERROR\n");
            exit(-1);
        }
    }

    // Exit the main thread
    pthread_exit(NULL);
}

void *hello_world(void *id)
{
    // Print message from thread id
    int thread_id;
    thread_id = (long)id;
    printf("Hello world from thread %ld\n", thread_id);
    // Exit thread id
    pthread_exit(NULL);
}
