#include <cstdlib>
#include <iostream>
#include <memory>

int main(int argc, char **argv) {
  // x contains a pointer to an int and has reference count 1.
  std::shared_ptr<int> x(new int(10));

  {
    // x and y now share the same pointer to an int, and they
    // share the reference count; the count is 2.
    std::shared_ptr<int> y = x;
    std::cout << *y << std::endl;
  }
  // y fell out of scope and was destroyed.  Therefore, the
  // reference count, which was previously seen by both x and y,
  // but now is seen only by x, is decremented to 1.
  std::cout << *x << std::endl;

 return EXIT_SUCCESS;
}
