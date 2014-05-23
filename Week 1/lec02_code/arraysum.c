#include <stdio.h>

int sumAll(int a[], int size);

int main(int argc, char **argv) {
  int numbers[5] = {3, 4, 1, 7, 4};
  int sum = sumAll(numbers, 5);
  printf("sum is: %d\n", sum);
  return 0;
}

int sumAll(int a[], int size) {
  int i, sum = 0;
  
  for (i = 0; i <= size; i++) {   //  CAN YOU SPOT THE BUG?
    sum += a[i];
  }
  return sum;
}
