// C++'s iostream declares stream objects cin, cout, etc.,
// but within the 'std' namespace.  Note that you don't
// need the .h when you're #including headers from the
// C++ standard library, but you do need them when including
// a local header (e.g.: #include "ll.h")
#include <iostream>

// We want to include C's header file stdlib.h to use the EXIT_SUCCESS
// preprocessor symbol.  To include a C standard library header foo.h
// in a C++ program, you use #include <cfoo>
#include <cstdlib>

int main(int argc, char **argv) {
  // "std::cout" means "the symbol 'cout' scoped to the 'std'
  // namespace.  'cout' happens to be an object instance of type
  // 'ostream' whose job is to write to the console.
  //
  // "<<" is an operator.  Objects of type 'ostream' have overloaded
  // this operator, meaning they have defined methods that are invoked
  // whenever an 'ostream' is on the left-hand-side of the "<<"
  // operator.  'ostream' uses C++'s static polymorphism to define
  // multiple methods that handle the "<<" operator; each method
  // takes one argument of a specific type.  So, there is a method
  // that handles the "<<" operator that accepts a C-style string
  // (i.e., a const char *).
  //
  // "Hello, World!" is a C-style string.
  //
  // The expression (std::cout << "Hello, World!") is evaluated
  // first; it invokes the method in the 'std::cout' object of
  // class 'ostream' that overloads the '<<' operator, passing it
  // a pointer to the memory location that contains the C-style
  // string "Hello, World!".  This method writes the string to
  // console, then returns a reference to the "std::cout" argument
  // as its return value.
  //
  // So, that return value will be the left-hand-side of the
  // next expression evaluated, namely (return-val-from-"<<" << endl).
  //
  // "endl" is a 'manipulator' function defined in "std".  This
  // function operates on an ostream to flush the stream and
  // write a newline character.  'std::cout' has a method
  // that is invoked when the '<<' operator is invoked on an ostream
  // and the right-hand-side is a manipulator function pointer.
  std::cout << "Hello, World!" << std::endl;
  return EXIT_SUCCESS;
}
