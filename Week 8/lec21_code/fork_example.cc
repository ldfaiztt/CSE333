#include <unistd.h>
#include <sys/wait.h>
#include <iostream>

int main(int argc, char **argv) {
  std::cout << "[parent] about to fork.." << std::endl;
  sleep(10);

  pid_t cpid = fork();
  if (cpid == 0) {
    // child
    std::cout << "[child] I'm alive!" << std::endl;
    sleep(10);
    std::cout << "[child] exiting...becoming a zombie." << std::endl;
    return EXIT_SUCCESS;
  } else if (cpid < 0) {
    // parent -- fork failed
    std::cerr << "[parent] fork failed :(" << std::endl;
    return EXIT_FAILURE;
  }

  // parent -- fork succeeded
  int stat_loc;
  std::cout << "[parent] My child lives!" << std::endl;
  sleep(30);

  std::cout << "[parent] Waiting for my child to die..." << std::endl;
  waitpid(cpid, &stat_loc, 0);

  std::cout << "[parent] My child has died." << std::endl;
  sleep(10);
  return EXIT_SUCCESS;
}
