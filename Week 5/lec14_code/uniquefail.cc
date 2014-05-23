#include <memory>    // for std::unique_ptr
#include <stdlib.h>  // for EXIT_SUCCESS

int main(int argc, char **argv) {
  std::unique_ptr<int> x(new int(5));

  // fail, no copy constructor
  std::unique_ptr<int> y(x);

  // succeed, z starts with NULL pointer
  std::unique_ptr<int> z;

  // fail, no assignment operator
  z = x;

  return EXIT_SUCCESS;
}
