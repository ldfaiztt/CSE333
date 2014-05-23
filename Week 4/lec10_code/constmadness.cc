#include <iostream>
#include <cstdlib>

int main(int argc, char **argv) {
  int x = 5;          // x is an int
  const int y = 6;    // y is a (const int)
  y++;      // compiler error

  const int *z = &y;  // z is a (variable pointer) to a (const int)
  *z += 1;  // compiler error
  z++;      // ok

  int *const w = &x;   // w is a (const pointer) to a (variable int)
  *w += 1;  // ok
  w++;      // compiler error

  const int *const v = &x;  // v is a (const pointer) to a (const int)
  *v += 1;  // compiler error
  v++;      // compiler error
  
  return EXIT_SUCCESS;
}
