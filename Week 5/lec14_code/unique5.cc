#include <memory>    // for std::unique_ptr
#include <stdlib.h>  // for EXIT_SUCCESS

using namespace std;

int main(int argc, char **argv) {
  // x is a unique_ptr storing an array of 5 ints
  unique_ptr<int[]> x(new int[5]);

  x[0] = 1;
  x[2] = 2;
  
  return EXIT_SUCCESS;
}
