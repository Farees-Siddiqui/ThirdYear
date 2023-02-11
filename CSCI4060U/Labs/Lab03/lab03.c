#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#ifdef _OPENMP
    #include <omp.h>
#else
    #define omp_get_thread_num() 0
    #define omp_get_num_threads() 1
#endif

#define THREADS 8
#define QUEUE_SIZE 10

struct Queue {
    int head;
    int tail;
    int size;
    double data[QUEUE_SIZE];
}Queue;

void decimal_to_dms(double decimal_degrees, int thread_id);
void enqueue(struct Queue* q, double element);
double dequeue(struct Queue* q);
void init_queue(struct Queue* q); 
void load_file();

int main(int argc, char *argv[]) {
    omp_set_num_threads(THREADS);
    
    // queue with 10 numbers prints nothing??
    // print_queue(&q);
    load_file();
    
    return 0;
}

void load_file() {
    // pragma omp parallel here?
    // %lf is for double
    FILE *longitude_file = fopen("longitude.csv", "r");
    FILE *latitude_file = fopen("latitude.csv", "r");
    struct Queue longitude_q;
    struct Queue latitude_q;
    int i;


    init_queue(&latitude_q);
    init_queue(&longitude_q);

    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num(); 
        double longitude_val;
        double latitude_val;

        // runs longitude calc on even threads and latitude calcs on odd threads
        if(thread_id % 2 == 0) {
            // longitude
            while(fscanf(longitude_file, "%lf", &longitude_val) != EOF) {
                #pragma omp critical
                {
                    enqueue(&longitude_q, longitude_val);
                    decimal_to_dms(dequeue(&longitude_q), thread_id);
                    
                    // printf("Thread: [%d] | Decimal Values (Long): [%lf]\n", thread_id, longitude_val);

                }
            }
        } else if (thread_id % 2 == 1) {
            // latitude
            while(fscanf(latitude_file, "%lf", &latitude_val) != EOF) {
                #pragma omp critical
                {
                    enqueue(&latitude_q, latitude_val);
                    decimal_to_dms(dequeue(&latitude_q), thread_id);

                    // printf("Thread: [%d] | Decimal Values (Lat): [%lf]\n", thread_id, latitude_val);
                }
            }
        }
    }
}


void decimal_to_dms(double decimal_degrees, int thread_id) {
    int degrees = (int)decimal_degrees;
    int minutes = (int)((decimal_degrees - degrees) * 60);
    double seconds = (((decimal_degrees - degrees) * 60) - minutes) * 60;
    seconds = (int)(seconds + 0.5);
    printf("[Thread: %d]\t%lf converted to [%d %d %f]\n", thread_id, decimal_degrees,degrees, minutes, seconds);
}

void enqueue(struct Queue* q, double element) {
    if (q->size == QUEUE_SIZE) {
        // printf("Queue is full\n");
        return;
    }
    q->data[q->tail] = element;
    q->tail = (q->tail + 1) % QUEUE_SIZE;
    q->size++;
}

double dequeue(struct Queue* q) {
    if (q->size == 0) {
        // printf("Queue is empty\n");
        return -1;
    }
    double element = q->data[q->head];
    q->head = (q->head + 1) % QUEUE_SIZE;
    q->size--;
    return element;
}

void init_queue(struct Queue* q) {
    q->head = 0;
    q->tail = 0;
    q->size = 0;
}