#include <stdio.h>
#include <math.h>
#include <omp.h>

#define QUEUE_LENGTH 10

void decimal_to_dms(double decimal_degrees) {
    int degrees = (int)decimal_degrees;
    int minutes = (int)((decimal_degrees - degrees) * 60);
    double seconds = (((decimal_degrees - degrees) * 60) - minutes) * 60;
    printf("%.2f° converted to %d° %d' %.2f\"\n", decimal_degrees, degrees, minutes, seconds);
}

void enqueue(double queue[QUEUE_LENGTH], double value) {
    static int tail = 0;
    queue[tail % QUEUE_LENGTH] = value;
    tail++;
}

double dequeue(double queue[QUEUE_LENGTH]) {
    static int head = 0;
    head++;
    return queue[(head - 1) % QUEUE_LENGTH];
}

int main() {
    double latitude_queue[QUEUE_LENGTH] = {0};
    double longitude_queue[QUEUE_LENGTH] = {0};
    
    FILE *latitude_file = fopen("latitude.csv", "r");
    FILE *longitude_file = fopen("longitude.csv", "r");
    
    double latitude, longitude;
    int i = 0;
    #pragma omp parallel private(latitude, longitude)
    {
        #pragma omp sections
        {
            #pragma omp section
            {
                while (fscanf(latitude_file, "%lf", &latitude) != EOF) {
                    #pragma omp critical
                    enqueue(latitude_queue, latitude);
                }
            }
            #pragma omp section
            {
                while (fscanf(longitude_file, "%lf", &longitude) != EOF) {
                    #pragma omp critical
                    enqueue(longitude_queue, longitude);
                }
            }
        }
        
        #pragma omp for schedule(static)
        for (i = 0; i < QUEUE_LENGTH; i++) {
            double latitude_value, longitude_value;
            #pragma omp critical
            latitude_value = dequeue(latitude_queue);
            #pragma omp critical
            longitude_value = dequeue(longitude_queue);
            
            decimal_to_dms(latitude_value);
            decimal_to_dms(longitude_value);
        }
    }
    
    fclose(latitude_file);
    fclose(longitude_file);
    
    return 0;
}