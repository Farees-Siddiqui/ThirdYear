#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

#define NUM_THREADS 2

struct stock_data {
   char name_id;
   float price;
   int count;
};

struct stock_data stock_A = {'A', 250.00, 1000};

pthread_mutex_t stock_A_mutex; //mutal exclusion variable for total
pthread_cond_t stock_A_buy_cond;


void *stock_broker(void *s);
void *stock_exchange(void *s);

int main() {
    //Declare the threads
    pthread_t threads[NUM_THREADS];
    //Declare the thread attributes
    pthread_attr_t a;

    //Initialize mutex and condition variable
    pthread_mutex_init(&stock_A_mutex, NULL);
    pthread_cond_init(&stock_A_buy_cond, NULL);

    //Initialize the thread attribute to default values
    pthread_attr_init(&a); 
    pthread_attr_setdetachstate(&a, PTHREAD_CREATE_JOINABLE);

    //Create the stock exchange thread
    int error = pthread_create(&threads[0], &a, 
                    stock_exchange, NULL);
    if (error) {
        printf("ERROR: pthread_create() stock exchange\n");
        exit(-1);
    }

    //Create the stock broker thread
    error = pthread_create(&threads[1], &a, 
                    stock_broker, NULL);
    if (error) {
        printf("ERROR: pthread_create() stock broker\n");
        exit(-1);
    }

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

    //destroy variables
    pthread_attr_destroy(&a);
    pthread_mutex_destroy(&stock_A_mutex);
    pthread_cond_destroy(&stock_A_buy_cond);

    //exit main thread
    pthread_exit(NULL);
}

void *stock_broker(void *threadarg) {
    pthread_mutex_lock(&stock_A_mutex);
    printf("Broker: waiting for signal to buy...\n");
    pthread_cond_wait(&stock_A_buy_cond, &stock_A_mutex);
    printf("Condition met -- buying stock\n");
    stock_A.count -= 10;
    pthread_mutex_unlock(&stock_A_mutex);
    pthread_exit(NULL);
}

void *stock_exchange(void *threadarg) {
    printf("Opening bell (ring, ring)\n");
    srand(time(NULL));
    for (int time_unit=0; time_unit < 5; time_unit++) {
        printf("TIME = %d\n", time_unit);
        pthread_mutex_lock(&stock_A_mutex);
        stock_A.price += (rand()%20-17.65);
        if (stock_A.price < 0.01) {
            stock_A.price = 0.01;
        }
        printf("Stock price: $%0.2f\n", stock_A.price);
        if (stock_A.price <= 225.00) {
            printf("signal stock price condition <= $225.00\n");
            pthread_cond_signal(&stock_A_buy_cond);
        }
        pthread_mutex_unlock(&stock_A_mutex);
        sleep(1);
    }
    printf("Closing bell (ring, ring)\n");

    pthread_exit(NULL);
}
