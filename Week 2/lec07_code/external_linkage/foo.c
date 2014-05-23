#include <stdio.h>

// A global variable, defined and initialized here in foo.c.
int counter = 1;

int main(int argc, char **argv) {
  printf("(main): pre-bar, counter is %d\n", counter);
  bar();
  printf("(main): post-bar, counter is %d\n", counter);
  return 0;
}
