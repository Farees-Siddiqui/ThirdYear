#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 200

struct thread_data {
    int thread_id;
    int value;
};q

struct thread_data thread_data_array[NUM_THREADS];
int total; //shared data
pthread_mutex_t mutex_total; //mutual exclusion variable for total

void *total_update(void *threadarg);

int main(){
    //Declare the threads
    pthread_t threads[NUM_THREADS];
    //Declare the thread attributes
    pthread_attr_t a;
    
    //Initialize mutex dynamically with default attributes
    pthread_mutex_init(&mutex_total, NULL);
    //Initialize thread attributes to default values
    pthread_attr_init(&a);
    //Set thread attributes to be joinable
    pthread_attr_setdetachstate(&a, PTHREAD_CREATE_JOINABLE);
    
    //Create the threads
    for (long i=0; i < NUM_THREADS; i++){
        thread_data_array[i].thread_id = i;
        thread_data_array[i].value = 10 * (int) i;
        printf("Creating thread %ld\n", i);
        int error = pthread_create(&threads[i], &a, total_update, (void *) &thread_data_array[i]);

        if (error){
            printf("ERROR; return code from pthread_create() is %d\n", i);
            exit(-1);
        }
    }
    pthread_attr_destroy(&a);
    // after creation need to join threads
    for (long i=0; i < NUM_THREADS; i++){
        void *status;
        int error = pthread_join(threads[i], &status);
        if (error){
            printf("ERROR; return code from pthread_join() is %d\n", i);
            exit(-1);
        }
    }
    //output final results 
    printf("All threads complete\n");
    printf("Total = %d\n", total);
    //destroy mutex
    pthread_mutex_destroy(&mutex_total);
    //exit main thread
    pthread_exit(NULL);

}

void *total_update(void *threadarg){
    struct thread_data *my_data;
    int try_error; //error code for try_lock
    int other_work = 0;
    my_data = (struct thread_data *) threadarg;
    printf("Requesting lock in thread %d\n",my_data->thread_id);
    while(try_error != 0) {
        try_error = pthread_mutex_trylock(&mutex_total); // acquire lock if available
        if (try_error != 0){
            printf("ERROR: try_lock in thread() %d\n", my_data->thread_id);
        } else {
            printf("Acquiring mutex in thread %d\n", my_data->thread_id);
            total += my_data->value; // shared variable read and write!
            printf("Releasing mutex in thread %d\n", my_data->thread_id);
            pthread_mutex_unlock(&mutex_total); // unlock the mutex
        }
        if (other_work == 0){
            other_work = 1;
            printf("**********Do other work**********\n");
        }
    }
    pthread_exit(NULL);
}