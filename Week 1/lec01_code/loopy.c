#include <stdio.h>

int main(int argc, char **argv) {
  int i;

  for (i = 0; i < 100; i++) {
    if (i % 10 == 0) {
      printf("i: %d\n", i);
    }
  }
  return 0;
}
