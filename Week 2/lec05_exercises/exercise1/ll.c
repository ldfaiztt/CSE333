/*
 * Copyright 2011 Steven Gribble
 *
 *  This file is the solution to an exercise problem posed during
 *  one of the UW CSE 333 lectures (333exercises).
 *
 *  333exercises is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  333exercises is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with 333exercises.  If not, see <http://www.gnu.org/licenses/>.
 */


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

unsigned int NumElements(Node *head) {
  int count = 0;

  while (head != NULL) {
    count++;
    head = head->next;
  }
  return count;
}
