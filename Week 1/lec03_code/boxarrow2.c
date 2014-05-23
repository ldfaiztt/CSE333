#include <stdio.h>

int main(int argc, char **argv) {
  int x = 1;
  int arr[3] = {2, 3, 4};
  int *p = &arr[1];
  int **dp = &p;

  *(*dp) += 1;
  p += 1;
  *(*dp) += 1;

  printf("x: %d\n", x);
  printf("arr[0]: %d\n", arr[0]);
  printf("arr[1]: %d\n", arr[1]);
  printf("arr[2]: %d\n", arr[2]);
  return 0;
}
