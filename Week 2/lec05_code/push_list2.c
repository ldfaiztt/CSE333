#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct node_st {
  int element;
  struct node_st *next;
} Node;

// version 2: add new node with payload e to
// front of list with first node head
void Push(Node **head, int e) {
  Node *n = (Node *) malloc(sizeof(Node));

  assert(n != NULL);  // crashes if false
  n->element = e;
  n->next = *head;

  *head = n;
}

int main(int argc, char **argv) {
  Node *list = NULL;

  Push(&list, 1);
  Push(&list, 2);

  return 0;
}
