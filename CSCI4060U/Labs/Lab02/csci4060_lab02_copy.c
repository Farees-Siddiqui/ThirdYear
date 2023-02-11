#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <stdbool.h>

#ifdef _OPENMP
    #include <omp.h>
#else
    #define omp_get_thread_num() 0
    #define omp_get_num_threads() 1
#endif

#define MAXCHAR 1024
#define THREADS 8

/*
Threads: 1, Time: 0.0146s
Threads: 2, Time: 0.0142s
Threads: 4, Time: 0.0084s
Threads: 8, Time: 0.0091s
*/

const char* parse_file(char* line, int field);
int compare_floats(const void *a, const void *b);


int main(int argc, char *argv[]){
    FILE *fp;
    char row[MAXCHAR];

    int i;
    float gpa;
    float max = -1;
    const int num_files = 8;
    char *files[8];
    float max_gpas[8];
    char *students[8];

    files[0] = "CSCI4060U_Lab02_data/1.csv";
    files[1] = "CSCI4060U_Lab02_data/2.csv";
    files[2] = "CSCI4060U_Lab02_data/3.csv";
    files[3] = "CSCI4060U_Lab02_data/4.csv";
    files[4] = "CSCI4060U_Lab02_data/5.csv";
    files[5] = "CSCI4060U_Lab02_data/6.csv";
    files[6] = "CSCI4060U_Lab02_data/7.csv";
    files[7] = "CSCI4060U_Lab02_data/8.csv";

    #ifdef _OPENMP
        omp_set_num_threads(THREADS);
    #endif

    #pragma omp parallel
    {
        #pragma omp for
        for (i = 0; i < num_files; i++) {
            char row[MAXCHAR];
            FILE *fp = fopen(files[i], "r");
            if (fp == NULL){
                printf("Could not open file %s", files[i]);
                continue;
            }
            float max = -1;
            while (fgets(row, MAXCHAR, fp) != NULL){
                char *tmp = strdup(row);
                gpa = atof(parse_file(tmp, 3));
                if (gpa > max)
                    max = gpa;
                // free(tmp);
            }
            fclose(fp);
            max_gpas[i] = max;
        }
        #pragma omp barrier

        #pragma omp single
        {
            qsort(max_gpas, num_files, sizeof(float), &compare_floats);
        }
    }

    for (int i = 0; i < num_files; i++)
        printf("Max GPA: %f\t" , max_gpas[i]);

    return 0;
}  

const char* parse_file(char* line, int field){
    char *pos;
    if ((pos=strchr(line, '\n')) != NULL)
        *pos = '\0';
    const char* tok;
    int count;
    tok = strtok(line, ",");
    for (count = 1; tok != NULL; count++) {
        if (count == field)
            return tok;
        tok = strtok(NULL, ",");
    }
    return NULL;
} 

int compare_floats(const void *a, const void *b) {
    float fa = *(const float*) a;
    float fb = *(const float*) b;
    return (fa < fb) - (fa > fb);
}