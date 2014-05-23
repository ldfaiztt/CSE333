#include <iostream>
#include <cstdlib>

// C++ supports strings as objects!  The std::string class and its methods
// are defined in the string.h C++ standard library header.
#include <string>

// The "using" keyword introduces part of a namespace, or an entire
// namespace, into the current declarative region.  So, the following
// would essentially import all names defined within the "std"
// namespace into the current namespace:
//
//   using namespace std;
//
// From that moment until the end of the current scope, you can
// refer to names in std without prefixing them with "std::".
//
// Alternatively, if you wanted to introduce a specific name into
// the current region without importing the entire namespace, you
// can say something like:
//
//   using std::cout;
//
// Then you can use "cout" without prefixing it with "std::".
using namespace std;

int main(int argc, char **argv) {
  // Here, we're intantiating a new instance of the class std::string,
  // and we're passing a C-style string ("Hello, World!") as an
  // argument to a constructor method.  The new string object instance
  // is stack-allocated, so when main() returns, the instance will be
  // de-allocated (and its destructor will be invoked).  The
  // constructor makes a private copy of the C-style string.
  string hello("Hello, World!");

  // Now, instead of passing a C-style string to the ostream object
  // instance std::cout's method for handling the "<<" operator, we're
  // passing (a reference to) the hello object instance.  It turns out
  // that the string.h header has declared a function that overloads
  // "<<" and accepts (a reference to) a string object as its RHS
  // argument, so this is what's invoked, rather than a method of the
  // ostream object.
  cout << hello << endl;
  return EXIT_SUCCESS;
}
