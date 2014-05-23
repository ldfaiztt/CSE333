#include <stdio.h>

void copyarray(int src[], int dst[], int size);

int main(int argc, char **argv) {
  int numbers[5] = {1, 3, 4, 7, 4};
  int numcopy[5];
  int i;

  copyarray(numbers, numcopy, 5);
  for (i = 0; i < 5; i++) {
    printf("numbers [%d]: %d;  numcopy[%d]: %d\n",
           i, numbers[i], i, numcopy[i]);
  }
  return 0;
}

void copyarray(int src[], int dst[], int size) {
  int i;

  for (i = 0; i < size; i++) {
    dst[i] = src[i];
  }
}
