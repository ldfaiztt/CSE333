#include <stdio.h>

int main(int argc, char **argv) {
  int x = 1;
  int *p = &x;

  printf("&x: %p;  p: %p;  &p: %p\n",
         &x, p, &p);
  return 0;
}
