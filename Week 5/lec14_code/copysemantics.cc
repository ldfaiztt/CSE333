#include <iostream>
#include <string>

std::string ReturnFoo(void) {
  std::string x("foo");
  return x;  // the return makes a copy
}

int main(int argc, char **argv) {
  std::string a("hello");
  std::string b(a);  // copies a to b

  // Copy return value into b.
  b = ReturnFoo();

  return EXIT_SUCCESS;
}
