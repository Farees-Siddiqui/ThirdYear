#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> //needed for posix threads

#define NUM_THREADS 20

struct thread_data
{
    int thread_id;
    int value;
};

void *hello_world(void *threadarg);

int main()
{
    struct thread_data thread_data_array[NUM_THREADS];

    // Declare threads
    pthread_t threads[NUM_THREADS];

    // Declare thread attributes
    pthread_attr_t a;
    void *status; // used to join

    // Initialize the thread attributes
    pthread_attr_init(&a); // set a to all default attributes
    pthread_attr_setdetachstate(&a, PTHREAD_CREATE_JOINABLE);

    // Create threads
    // Have threads display a message via function call
    for (long i = 0; i < NUM_THREADS; i++)
    {
        thread_data_array[i].thread_id = i;
        thread_data_array[i].value = 10 * (int)i;
        printf("Creating thread %ld\n", i);
        /* format for creating a thread:
            int pthread_create(pthread_t *thread,
                                const pthread_attr_t *attr,
                                void *(*start_routine) (void *),
                                void *arg);
            )
        */
        int error = pthread_create(&threads[i], &a,
                                   hello_world, (void *)&thread_data_array[i]);
        if (error)
        {
            printf("ERROR: create()\n");
            exit(-1);
        }
    }

    // free attribute after using
    pthread_attr_destroy(&a);

    // After creation of thread we need to join threads to main
    for (long i = 0; i < NUM_THREADS; i++)
    {
        int error = pthread_join(threads[i], &status);
        if (error)
        {
            printf("ERROR: join()\n");
            exit(-1);
        }
    }

    printf("Threads complete and join done!\n");

    // Exit the main thread
    pthread_exit(NULL);
}

void *hello_world(void *threadarg)
{
    // Print message from thread id
    struct thread_data *my_data;
    my_data = (struct thread_data *)threadarg;
    // reminder my_data->thread_id is the same as (*my_data).thread_id
    printf("Hello world from thread %d. My value is %d\n",
           my_data->thread_id, my_data->value);
    // Exit thread id
    pthread_exit(NULL);
}
