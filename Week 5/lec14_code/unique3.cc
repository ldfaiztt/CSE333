#include <memory>    // for std::unique_ptr
#include <iostream>  // for std::cout, std::endl
#include <stdlib.h>  // for EXIT_SUCCESS

using namespace std;

int main(int argc, char **argv) {
  unique_ptr<int> x(new int(5));
  cout << "x: " << x.get() << endl;

  unique_ptr<int> y(x.release());  // y takes ownership, x abdicates it
  cout << "x: " << x.get() << endl;
  cout << "y: " << y.get() << endl;

  unique_ptr<int> z(new int(10));

  // z delete's its old pointer and takes ownership of y's pointer.
  // y abdicates its ownership.
  z.reset(y.release());

  return EXIT_SUCCESS;
}
