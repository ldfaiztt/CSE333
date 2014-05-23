#include <pthread.h>
#include <unistd.h>
#include <iostream>
#include <memory>

void sleep_spin(int delay) {
  for (int i = 0; i < 4; i++) {
    std::cout << "  sleep_spin(" << delay << ") sleeping..." << std::endl;
    sleep(delay);
    std::cout << "  sleep_spin(" << delay << ") done sleeping." << std::endl;
  }
}

void *thread_start(void *arg) {
  std::unique_ptr<int> delay(reinterpret_cast<int *>(arg));
  std::cout << "[child thread] I'm alive!" << std::endl;
  std::cout << "[child thread] calling sleep_spin(" << *delay
            << ")" << std::endl;
  sleep_spin(*delay);
  std::cout << "[child thread] done." << std::endl;
  return NULL;
}

int main(int argc, char **argv) {
  // Create a child thread, passing it an (int *) as its argument.
  std::cout << "[parent thread] about to pthread_create().." << std::endl;
  pthread_t thr;
  int *argument = new int(1);
  if (pthread_create(&thr, NULL, &thread_start,
                     reinterpret_cast<void *>(argument)) != 0) {
    std::cerr << "pthread_create() failed." << std::endl;
    return EXIT_FAILURE;
  }

  // Could either (a) use pthread_join() to wait for the child to
  // terminate, or (b) call pthread_detach() to "detach" the child and
  // then we no longer care about or need to pthread_join() with it.
  // We'll do pthread_detach().
  if (pthread_detach(thr) != 0) {
    std::cerr << "pthread_detach() failed." << std::endl;
  }

  std::cout << "[parent thread] calling sleep_spin(2).." << std::endl;
  sleep_spin(2);
  std::cout << "[parent thread] done." << std::endl;

  return EXIT_SUCCESS;
}
