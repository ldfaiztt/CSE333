#include <stdio.h>

// A global variable, defined and initialized here in foo.c.
// By including the "static" storage class specifier, we are
// telling the compiler that "counter" should use internal
// linkage: this means that other modules cannot "see" our
// counter variable.
static int counter = 1;

int main(int argc, char **argv) {
  printf("(main): pre-bar, counter is %d\n", counter);
  bar();
  printf("(main): post-bar, counter is %d\n", counter);
  return 0;
}
