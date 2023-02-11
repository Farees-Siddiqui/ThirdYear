/*
Threads: 1, Time: 0.013s
Threads: 2, Time: 0.010s
Threads: 4, Time: 0.009s
Threads: 8, Time: 0.009s
*/

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

struct student {
  char* name;
  char* surname;
  char* fullname;
  float gpa;
};

char* get_nth_element(const char* str, int n) {
  int count = 0;
  const char* start = str;
  const char* end = str;

  while (*end != '\0') {
    if (*end == ',') {
      count++;
      if (count == n) {
        break;
      }
      start = end + 1;
    }
    end++;
  }

  int length = end - start;
  char* result = (char*) malloc((length + 1) * sizeof(char));
  memcpy(result, start, length);
  result[length] = '\0';
  return result;
}

int compare_student(const void *a, const void *b) {
    const struct student *sa = (const struct student *)a;
    const struct student *sb = (const struct student *)b;
    
    // return 1 if a > b, -1 if a < b, 0 if a == b
    if (sa->gpa > sb->gpa) {
        return -1;
    } else if (sa->gpa < sb->gpa) {
        return 1;
    } else {
        return 0;
    }
}

int main(int argc, char *argv[]){
    FILE *fp;
    char row[MAXCHAR];

    int i;
    float gpa;
    float max = -1;
    const int num_files = 8;
    char *files[8];
    float max_gpas[8];
    char *max_student[8];

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
                gpa = atof(get_nth_element(tmp, 3));
                if (gpa > max) {
                    max = gpa;
                    max_student[i] = (char*)strdup(row);
                }
                free(tmp);
            }
            fclose(fp);
            max_gpas[i] = max;
        }
        #pragma omp barrier
    }


    struct student *students = (struct student*) malloc(8 * sizeof(struct student));

    for (int i = 0; i < 8; i++) {
        students[i].name = get_nth_element(max_student[i], 1);
        students[i].surname = get_nth_element(max_student[i], 2);
        students[i].gpa = atof(get_nth_element(max_student[i], 3));
    }

    qsort(students, 8, sizeof(struct student), compare_student);

    for (int i = 0; i < 8; i++) {
        printf("%s %s:\t \t[%.2f]\n", students[i].name, students[i].surname, students[i].gpa);
    }
    
}