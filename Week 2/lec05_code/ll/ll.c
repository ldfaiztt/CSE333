#include <stdio.h>    // for NULL
#include <stdlib.h>   // for malloc(), free()
#include <assert.h>   // for assert()

#include "ll.h"

Node *Push(Node *head, void *element) {
  Node *newnode;

  // allocate the new node
  newnode = (Node *) malloc(sizeof(Node));
  assert(newnode != NULL);

  // initialize the new node
  newnode->element = element;
  newnode->next = head;

  return newnode;
}

void *Pop(Node *old_head, Node **new_head) {
  void *tmp;

  // Corner case: trying to Pop from an empty list.
  // Indicate failure by returning NULL.
  if (old_head == NULL)
    return NULL;

  // There's something in the list; let's save
  // what we need to return in a temporary variable.
  tmp = old_head->element;

  // Let's return (through the return parameter)
  // the new head of the list.
  *new_head = old_head->next;

  // Free up the old head.  Before doing that, we'll
  // defensively set its fields to NULL.  Why?
  // if there is some kind of pointer bug elsewhere,
  // this increases the chance it will manifest as
  // a (fail-stop) segmentation fault.
  old_head->element = NULL;
  old_head->next = NULL;
  free(old_head);

  // Return the payload we previously stashed in tmp.
  return tmp;
}
