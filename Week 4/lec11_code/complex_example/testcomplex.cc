#include <iostream>
#include <sstream>

#include "Complex.h"

int main(int argc, char **argv) {
  // Invokes the constructors for a,b.
  complex::Complex a(1,1), b(2,2);
  complex::Complex c = b;  // Invokes the copy constructor for c.

  // Invokes the "+" operator; our implementation of the "+" operator
  // allocates a "temp" variable, so a constructor for it is invoked.
  // g++ has an optimization called "return by value optimization";
  // since we're assigning the return value from "+" to the variable
  // "d", instead of allocating "temp" in the stack frame of "+",
  // it instead uses the space allocated for "d" to hold temp's
  // contents, avoiding an extra copy constructor / allocation.
  complex::Complex d = a + b;
  std::cout << "[address of d:] " << &d << std::endl;

  a = d;   // Invokes the "=" operator on a with argument d.
  b += a;  // Invokes the "+=" operator on b with argument a.

  // Invokes the "<<" operator with args (cout, c), then (cout, endl).
  std::cout << c << std::endl;

  std::stringstream str("(10 + 11i)");

  // Invokes the ">>" operator with args (str, d).
  str >> d;

  // Invokes the "<<" operator with args (cout, d), then (cout, endl).
  std::cout << d << std::endl;

  return 0;
}
