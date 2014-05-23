#include <pthread.h>
#include <unistd.h>
#include <iostream>

static unsigned int total_count = 0;
static pthread_mutex_t count_lock = PTHREAD_MUTEX_INITIALIZER;

// Increment total_count arg times.
void *thread_start(void *arg) {
  unsigned int *loops = reinterpret_cast<unsigned int *>(arg);
  for (unsigned int i = 0; i < *loops; i++) {
    pthread_mutex_lock(&count_lock);
    total_count++;
    pthread_mutex_unlock(&count_lock);
  }
  delete loops;
  return NULL;
}

static const unsigned int kNumThreads = 100;

int main(int argc, char **argv) {
  // Create kNumThreads threads, dispatching each to thread_start().
  pthread_t thr_array[kNumThreads];
  for (unsigned int i = 0; i < kNumThreads; i++) {
    unsigned int *argument = new unsigned int(i);

    if (pthread_create(&thr_array[i],
                       NULL,
                       &thread_start,
                       reinterpret_cast<void *>(argument)) != 0) {
      std::cerr << "pthread_create() failed." << std::endl;
      return EXIT_FAILURE;
    }
  }

  // Join with all the threads we created (i.e., wait for each to die).
  for (unsigned int i = 0; i < kNumThreads; i++) {
    void *res;
    if (pthread_join(thr_array[i], &res) != 0) {
      std::cerr << "pthread_join() failed." << std::endl;
    }
  }

  // Print out the final count.
  std::cout << "total count is: " << total_count << std::endl;

  return EXIT_SUCCESS;
}
