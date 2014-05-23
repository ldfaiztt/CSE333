/*
 * Copyright 2012 Steven Gribble
 *
 *  This file is part of the UW CSE 333 course project sequence
 *  (333proj).
 *
 *  333proj is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  333proj is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with 333proj.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>

#include "Assert333.h"
#include "LinkedList.h"

// the payload type we'll add
typedef struct {
  int num;
} ExamplePayload, *ExamplePayloadPtr;

// prototype of our payload free function
void ExamplePayloadFree(void *payload);

// prototype of our payload comparator function
int ExamplePayloadComparator(void *p1, void *p2);

// our main function; here, we demonstrate how to use some
// of the linked list functions.
int main(int argc, char **argv) {
  ExamplePayloadPtr payload;
  LinkedList list;
  LLIter iter;
  int i;

  // allocate a list
  list = AllocateLinkedList();
  Assert333(list != NULL);

  // insert 100 elements
  for (i = 0; i < 100; i++) {
    payload = (ExamplePayloadPtr) malloc(sizeof(ExamplePayload));
    Assert333(payload != NULL);
    payload->num = i;
    Assert333(PushLinkedList(list, (void *) payload) == 1);

    // make sure our list total is correct
    Assert333(NumElementsInLinkedList(list) == i+1);
  }

  // sort the list in descending order
  SortLinkedList(list, 0, &ExamplePayloadComparator);

  // pop off the first element
  Assert333(PopLinkedList(list, (void **) &payload) == 1);
  Assert333(payload->num == 99);
  Assert333(NumElementsInLinkedList(list) == 99);
  free(payload);

  // slice off the last element
  Assert333(SliceLinkedList(list, (void **) &payload) == 1);
  Assert333(payload->num == 0);
  Assert333(NumElementsInLinkedList(list) == 98);
  free(payload);

  // make an iterator from the head
  iter = LLMakeIterator(list, 0);
  Assert333(iter != NULL);

  // peek at the current iterator payload
  LLIteratorGetPayload(iter, (void **) &payload);
  Assert333(payload->num == 98);

  // move the iterator, peek at next payload
  Assert333(LLIteratorNext(iter) == 1);
  LLIteratorGetPayload(iter, (void **) &payload);
  Assert333(payload->num == 97);

  // free the iterator
  LLIteratorFree(iter);

  // free the linked list
  FreeLinkedList(list, &ExamplePayloadFree);
  return 0;
}


void ExamplePayloadFree(void *payload) {
  Assert333(payload != NULL);
  free(payload);
}

// prototype of our payload comparator function
int ExamplePayloadComparator(void *p1, void *p2) {
  int i1, i2;
  Assert333(p1 != NULL);
  Assert333(p2 != NULL);

  i1 = ((ExamplePayloadPtr) p1)->num;
  i2 = ((ExamplePayloadPtr) p2)->num;

  if (i1 > i2)
    return 1;
  if (i1 < i2)
    return -1;
  return 0;
}
