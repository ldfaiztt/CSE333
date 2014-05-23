#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void leak(int bytes) {
  char *buf = malloc(bytes);
  assert(buf != NULL);
}

int main(int argc, char **argv) {
  while(1) {
    leak(100000);
  }
}
