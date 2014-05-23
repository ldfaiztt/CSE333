#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct node_st {
  int element;
  struct node_st *next;
} Node, *NodePtr, **NodePtrPtr;

// version 3: add new node with payload e to
// front of list with first node head
// (same as version 2 but with fancier typedefs)
void Push(NodePtrPtr head, int e) {
  NodePtr n = (NodePtr) malloc(sizeof(Node));

  assert(n != NULL);  // crashes if false
  n->element = e;
  n->next = *head;

  *head = n;
}

int main(int argc, char **argv) {
  NodePtr list = NULL;

  Push(&list, 1);
  Push(&list, 2);

  return 0;
}
