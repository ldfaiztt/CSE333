#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>

#define LOOPCOUNT 20000
int main(int argc, char **argv) {
  int forkcount = 0;
  struct timeval before, after;

  gettimeofday(&before, NULL);  // once to warm up call path
  gettimeofday(&before, NULL);  // once for real-sies
  while (1) {
    pid_t p = fork();
    if (p > 0) {
      // parent.
      int loc;
      p = wait(&loc);
      forkcount++;
      if (forkcount == LOOPCOUNT)
        break;
    } else {
      // child
      exit(EXIT_SUCCESS);
    }
  }
  gettimeofday(&after, NULL);

  float diff_us = (after.tv_sec - before.tv_sec) * 1000000.0;
  diff_us += (after.tv_usec - before.tv_usec);
  diff_us /= LOOPCOUNT;

  printf("microseconds per fork: %f\n", diff_us);
  return EXIT_SUCCESS;
}
