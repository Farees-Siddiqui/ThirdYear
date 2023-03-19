#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 10000

struct thread_data {
    int thread_id;
    int value;
};

struct thread_data thread_data_array[NUM_THREADS];

int total; //shared data
pthread_mutex_t mutex_total; //mutal exclusion variable for total

void *total_update(void *threadarg);

int main() {
    //Declare the threads
    pthread_t threads[NUM_THREADS];
    //Declare the thread attributes
    pthread_attr_t a;

    //Initialize mutex dynamically with default attributes
    pthread_mutex_init(&mutex_total, NULL);

    //Initialize the thread attribute to default values
    pthread_attr_init(&a); 
    pthread_attr_setdetachstate(&a, PTHREAD_CREATE_JOINABLE);

    //Create the threads
    for (long i=0; i < NUM_THREADS; i++) {
        //Initialize data for current thread
        thread_data_array[i].thread_id = i;
        thread_data_array[i].value = 10 * (int)i;
        
        printf("Creating thread %d\n", i);
        int error = pthread_create(&threads[i], &a, 
                                   total_update, (void *) &thread_data_array[i]);
        if (error) {
            printf("ERROR: pthread_create() in thread %d\n", i);
            exit(-1);
        }
    }

    pthread_attr_destroy(&a);
    //after creation need to join threads
    for (long i=0; i < NUM_THREADS; i++) {
        void *status;
        int error = pthread_join(threads[i], &status);
        if (error) {
            printf("ERROR: pthread_join() in thread %d\n", i);
            exit(-1);
        }
    }

    //Output final results after all threads complete
    printf("All threads complete\n");
    printf("Total = %d\n", total);

    //destroy mutex
    pthread_mutex_destroy(&mutex_total);

    //exit main thread
    pthread_exit(NULL);

}

void *total_update(void *threadarg) {
    struct thread_data *my_data;
    my_data = (struct thread_data*) threadarg;
   
    printf("Requesting lock in thread %d\n", my_data->thread_id);
    pthread_mutex_lock(&mutex_total); //acquire lock and block if unavailable
    printf("Acquring mutex in thread%d\n", my_data->thread_id);
    total += my_data->value; //shared variable read and write!
    printf("Releasing mutex in thread%d\n", my_data->thread_id);
    pthread_mutex_unlock(&mutex_total); //release the lock for other threads to use
    printf("*******Do other work*******\n");

    pthread_exit(NULL);
}