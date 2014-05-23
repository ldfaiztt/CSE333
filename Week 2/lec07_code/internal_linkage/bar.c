#include <stdio.h>

// A global variable, defined and initialized here in foo.c.
// By including the "static" storage class specifier, we are
// telling the compiler that "counter" should use internal
// linkage: this means that other modules cannot "see" our
// counter variable.
static int counter = 100;

void bar(void) {
  counter++;
  printf("(bar): incremented counter is %d\n", counter);
}
