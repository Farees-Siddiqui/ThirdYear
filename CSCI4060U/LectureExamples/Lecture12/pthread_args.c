#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5

struct thread_data
{
  int thread_id;
  int value;
};

struct thread_data thread_data_array[NUM_THREADS];

void *hello_world(void *threadarg);

int main()
{
  // Declaring threads
  pthread_t threads[NUM_THREADS];
  long i;
  int error;

  // Creating threads
  for (i = 0; i < NUM_THREADS; i++)
  {
    thread_data_array[i].thread_id = i;
    thread_data_array[i].value = 10 * (int)i;
    printf("Creating thread %ld\n", i);
    // pthread definition:
    //   int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
    //                     void *(*start_routine) (void *), void *arg);

    error = pthread_create(&threads[i], NULL, hello_world,
                           (void *)&thread_data_array[i]);
    if (error)
    {
      printf("ERROR %d\n", error);
      exit(-1);
    }
  }
  // exit main thread
  pthread_exit(NULL);
}

void *hello_world(void *threadarg)
{
  struct thread_data *my_data;
  my_data = (struct thread_data *)threadarg;
  printf("Hello world from thread %d! My value is %d\n",
         my_data->thread_id, my_data->value);
  pthread_exit(NULL);
}
