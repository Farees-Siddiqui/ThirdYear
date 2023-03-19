#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS 100

int main (int argc, char* argv[]) {
    if (argc != 4) {
        printf("[ERROR] Incorrect Usage\n[Usage] <number of agents> <number of seats> <percent overselling>\n");
        return -1;
    }

    int num_agents = atoi(argv[1]);
    int num_seats = atoi(argv[2]);
    double percent_overselling = atof(argv[3]);

    int total_seats = num_seats + (num_seats * (percent_overselling/100));

    printf("Number of agents: %d \t Number of seats: %d \t Percent overselling: %f \n", num_agents, num_seats, percent_overselling);
    printf("Total seats: %d \n", total_seats);
    return 0;
}