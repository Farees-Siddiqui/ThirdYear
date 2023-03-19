#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

struct thread_data
{
    int thread_id;
    int available_seats;
};

int tickets_sold = 0;               // shared data
pthread_mutex_t mutex_tickets_sold; // mutal exclusion variable for total

void *ticket_agent(void *threadarg);

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("[ERROR] Incorrect Usage\n[Usage] <number of agents> <number of seats> <percent overselling>\n");
        return -1;
    }

    int num_agents = atoi(argv[1]);
    int num_seats = atoi(argv[2]);
    double percent_overselling = atof(argv[3]);

    int total_seats = num_seats + (num_seats * (percent_overselling / 100));

    pthread_t agents[num_agents];
    struct thread_data thread_data_array[num_agents];
    pthread_attr_t a;

    pthread_mutex_init(&mutex_tickets_sold, NULL);

    pthread_attr_init(&a);
    pthread_attr_setdetachstate(&a, PTHREAD_CREATE_JOINABLE);

    for (long i = 0; i < num_agents; i++) {
        // Initialize data for current thread
        thread_data_array[i].thread_id = i;
        thread_data_array[i].available_seats = total_seats - tickets_sold;

        printf("Creating thread %ld\n", i);
        int error = pthread_create(&agents[i], &a, ticket_agent, (void *)&thread_data_array[i]);
        if (error) {
            printf("ERROR: pthread_create() in thread %ld\n", i);
            exit(-1);
        }
    }

    pthread_attr_destroy(&a);
    // after creation need to join threads
    for (long i = 0; i < num_agents; i++) {
        void *status;
        int error = pthread_join(agents[i], &status);
        if (error) {
            printf("ERROR: pthread_join() in thread %ld\n", i);
            exit(-1);
        }
    }
    return 0;
}

void *ticket_agent(void *threadarg) {
    struct thread_data *my_data;
    my_data = (struct thread_data *)threadarg;

    int success_rate = my_data->thread_id % 2 == 0 ? 45 : 30; // calculate success rate based on thread_id

    while (tickets_sold < my_data->available_seats) {
        pthread_mutex_lock(&mutex_tickets_sold); // lock mutex before accessing shared data
        if (tickets_sold >= my_data->available_seats) {
            pthread_mutex_unlock(&mutex_tickets_sold); // unlock mutex before exiting loop
            break;
        }
        int success = rand() % 100 < success_rate; // determine if transaction is successful
        int num_tickets = rand() % 4 + 1;          // generate random number of tickets sold
        if (success) {
            tickets_sold += num_tickets; // update shared data
            printf("Ticket agent %d: Successful transaction - %d tickets sold\n", my_data->thread_id, num_tickets);
        }
        else {
            printf("Ticket agent %d: Unsuccessful transaction\n", my_data->thread_id);
        }
        pthread_mutex_unlock(&mutex_tickets_sold); // unlock mutex after updating shared data
    }

    pthread_exit(NULL);
}
