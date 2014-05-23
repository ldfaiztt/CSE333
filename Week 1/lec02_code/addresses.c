#include <stdio.h>

int foo(int x) {
  return x+1;
}

int main(int argc, char **argv) {
  int x, y;
  int a[2];

  printf("x     is at %p\n", &x);
  printf("y     is at %p\n", &y);
  printf("a[0]  is at %p\n", &a[0]);
  printf("a[1]  is at %p\n", &a[1]);
  printf("foo   is at %p\n", &foo);
  printf("main  is at %p\n", &main);

  return 0;
}
