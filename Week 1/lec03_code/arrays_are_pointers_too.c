#include <stdio.h>

int main(int argc, char **argv) {
  int a[5] = {10, 20, 30, 40, 50};
  int* p1 = &a[3];   // refers to a's fourth element
  int* p2 = &a[0];   // refers to a's first element
  int* p3 = a;       // refers to a's first element too

  *p1 = 100;
  *p2 = 200;
  p1[1] = 300;
  p2[1] = 400;
  p3[2] = 500;

  printf("[%d, %d, %d, %d, %d]\n", a[0], a[1], a[2], a[3], a[4]);

  return 0;
}
