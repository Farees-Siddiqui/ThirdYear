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


void print_queue(struct Queue *q) {
    for (int i = q->head; i < q->tail; i++) {
        printf("%lf\n", q->data[i]);
    }
}

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
    FILE *files[2] = {longitude_file, latitude_file};
    int i;

    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num(); 
        double val;

        #pragma omp for 
        for (int i = 0; i < 2; i++) {
            struct Queue q;
            init_queue(&q);
            while(fscanf(files[i], "%lf", &val) != EOF) {
                #pragma omp critical
                {
                    if (q.size == 10) {
                        decimal_to_dms(dequeue(&q), omp_get_thread_num());
                    } else {
                        enqueue(&q, val);
                    }
                }
            }
            fclose(longitude_file);
            fclose(latitude_file);

            #pragma omp critical
            {
                while (q.size > 0) {
                    decimal_to_dms(dequeue(&q), omp_get_thread_num());
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