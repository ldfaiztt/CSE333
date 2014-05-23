#include <cstdlib>
#include <iostream>

#include "./ToyPtr.h"

int main(int argc, char **argv) {
  // Create a dumb pointer.
  int *leak = new int(5);

  // Create a "smart" pointer.  (OK, it's still pretty dumb.)
  ToyPtr<int> notleak(new int(6));

  // Use them.
  std::cout << "*leak: " << *leak << std::endl;
  std::cout << "*notleak: " << *notleak << std::endl;

  // Return, leaking "leak" but not "notleak".
  return EXIT_SUCCESS;
}
