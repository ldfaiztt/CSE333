#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>

#define NUM_THREADS     5   /* number of threads to create */

/* Sleep for a small amount of time */
void RandomSleep() {
  useconds_t how_long = (useconds_t)(random()%100000);
  usleep(how_long);
}

/* Thread worker code */
void *TaskCode(void *argument) {
  int tid;

  RandomSleep();

  tid = *((int *) argument);
  printf("Hello World! It's me, thread %d!\n", tid);

  RandomSleep();

  /* optionally: insert more useful stuff here */

  return NULL;
}

/* create NUM_THREADS threads and wait for them to terminate */
int main(void) {
  pthread_t threads[NUM_THREADS];
  int thread_args[NUM_THREADS];
  int rc, i;

  /* create all threads */
  for (i = 0; i < NUM_THREADS; ++i) {
    thread_args[i] = i;
    printf("In main: creating thread %d\n", i);
    rc = pthread_create(&threads[i], NULL, TaskCode, (void *) &thread_args[i]);
    assert(0 == rc);
    RandomSleep();
  }

  /* wait for all threads to complete */
  for (i = 0; i < NUM_THREADS; ++i) {
    rc = pthread_join(threads[i], NULL);
    assert(0 == rc);
  }

  exit(EXIT_SUCCESS);
}
