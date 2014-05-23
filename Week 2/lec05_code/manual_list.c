#include <stdio.h>

typedef struct node_st {
  int element;
  struct node_st *next;
} Node;

int main(int argc, char **argv) {
  Node n1, n2;

  n1.element = 1;
  n1.next = &n2;
  n2.element = 2;
  n2.next = NULL;
  return 0;
}
