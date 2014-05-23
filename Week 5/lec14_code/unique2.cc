#include <memory>    // for std::unique_ptr
#include <stdlib.h>  // for EXIT_SUCCESS

using namespace std;
typedef struct {  int a, b; } IntPair;

int main(int argc, char **argv) {
  unique_ptr<int> x(new int(5));

  // Return a pointer to the pointed-to object
  int *ptr = x.get();

  // Return a reference to the value of the pointed-to object
  int val = *x;

  // Access a field or function of a pointed-to object
  unique_ptr<IntPair> ip(new IntPair);
  ip->a = 100;

  // Deallocate the pointed-to object and reset the unique_ptr with
  // a new heap-allocated object.
  x.reset(new int(1));

  // Release responsibility for freeing the pointed-to object.
  ptr = x.release();
  delete ptr;
  return EXIT_SUCCESS;
}
