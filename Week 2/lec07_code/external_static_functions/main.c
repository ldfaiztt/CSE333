#include <stdio.h>

extern int bar(int);

int main(int argc, char **argv) {
  printf("%d\n", bar(5));
  return 0;
}
