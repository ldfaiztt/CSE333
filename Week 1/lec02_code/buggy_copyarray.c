#include <stdio.h>

int *copyarray(int src[], int size);

int main(int argc, char **argv) {
  int numbers[5] = {1, 3, 4, 7, 4};
  int numcopy[5] = copyarray(numbers, 5);  // no -- buggy
  int i;

  for (i = 0; i < 5; i++) {
    printf("numbers [%d]: %d;  numcopy[%d]: %d\n",
           i, numbers[i], i, numcopy[i]);
  }
  return 0;
}

int *copyarray(int src[], int size) {
  int i, dst[size];  // OK in C99

  for (i = 0; i < size; i++) {
    dst[i] = src[i];
  }
  return dst;  // no -- buggy
}
