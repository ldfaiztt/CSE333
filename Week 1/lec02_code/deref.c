#include <stdio.h>

int main(int argc, char **argv) {
  int x = 42;   
  int *p;       // p is a pointer to an integer
  p = &x;       // p now contains the address of x

  printf("x  is %d\n", x);
  *p = 99;
  printf("x  is %d\n", x);
  
  return 0;
}
