/* 
Farees Siddiqui - 100 780 513
Circualr Queue Implementation: https://www.dremendo.com/c-programming-tutorial/c-circular-queue#:~:text=A%20Circular%20Queue%20in%20C,array%20implementation%20of%20a%20Queue.
used above website as reference 
Time Values for Different number of threads
   1 threads: 6.7ms +- 0.6ms
   2 threads: 5.8ms +- 0.4ms
   4 threads: 5.9ms +- 0.5ms
   8 threads: 6.4ms +- 0.4ms
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#ifdef _OPENMP
    #include <omp.h>
#else 
    #define omp_get_num_threads() 1
    #define omp_get_thread_num() 0
#endif

#define THREADS 2
#define QUEUE_SIZE 10

struct Queue {
    int head;
    int tail;
    int size;
    double data[QUEUE_SIZE];
}Queue;

void decimal_to_dms(double decimal_degrees, int thread_id, bool lat);
void enqueue(struct Queue* q, double element);
void init_queue(struct Queue* q);
void print_queue(struct Queue* q); 
void load_file_and_process_data();
double dequeue(struct Queue* q);
bool is_full(struct Queue* q);


int main(int argc, char* argv[]) {
    omp_set_num_threads(THREADS);
    load_file_and_process_data();
    return 0;
}

void decimal_to_dms(double decimal_degrees, int thread_id, bool lat) {
    int degrees = (int)decimal_degrees;
    int minutes = (int)((decimal_degrees - degrees) * 60);
    double seconds = (((decimal_degrees - degrees) * 60) - minutes) * 60;
    seconds = (int)(seconds + 0.5);
    char* dir = "";

    if (lat) {
        if (degrees > -1) {
            dir = "N";
        } else {
            dir = "S";
        }
    } else {
        if (degrees > -1) {
            dir = "E";
        } else {
            dir = "W";
        }
    }

    printf("[Thread: %d]\t%lf converted to [%d %d %f %s]\n", thread_id, decimal_degrees,degrees, minutes, seconds, dir);
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

// write a function that returns a boolean to check if the queue is full 
bool is_full(struct Queue* q) {
    if (q->size == QUEUE_SIZE) {
        return true;
    }
    return false;
}
// write a function that prints the queue
void print_queue(struct Queue* q) {
    int i;
    printf("Queue: [ ");
    for (i = 0; i < QUEUE_SIZE; i++) {
        printf("%lf ", q->data[i]);
    }
    printf("]\n");
}

void load_file_and_process_data() {
    char* files[2] = {"latitude.csv", "longitude.csv"};
    int tot = 0;
    #pragma omp parallel for
    for (int i = 0; i < 2; i++) {
        struct Queue q;
        init_queue(&q);
        double val;
        int count = 0;
        FILE* fp = fopen(files[i], "r");
        printf("----------------Start of: %s----------------\n", files[i]);
        while (fscanf(fp, "%lf", &val) != EOF) {
            // crit section
            count++;
            tot += count;
            #pragma omp critical
            {
                enqueue(&q, val);
                if (is_full(&q)) {
                    while (q.size > 0) {
                        if (strcmp(files[i],"longitude.csv") == 0) {
                            decimal_to_dms(dequeue(&q), omp_get_thread_num(), false);
                        } else {
                            decimal_to_dms(dequeue(&q), omp_get_thread_num(), true);
                        }
                    }
                } 
            }
        }
        printf("----------------End of: %s----------------\n[Count: %d]\n", files[i], count);
    }
}