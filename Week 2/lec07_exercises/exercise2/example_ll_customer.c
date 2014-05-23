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

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "ll.h"

// Lecture 7, exercise 2.
//
// Modify the linked list code from lecture 6 exercise 1 to:
// - add static declarations to any internal functions you
//   implemented in ll.h.  [I didn't have any in my soln, so
//   this was easy. ;) ]
//
// - add a header guard to ll.h.  [I already had mine in, so
//   this was also easy. :) ]
//
// - write a Makefile   [I already had one.]
//   - use google to figure out how to add rules to the Makefile
//     produce a library (linkedlist.a) that contains the linked
//     list code.  (done.)

int main(int argc, char **argv) {
  Node *list = NULL, *tmp;
  char *hi = "hello";
  char *bye = "goodbye";
  char *dynamic_string = NULL, *ret = NULL;

  // Push two elements on the list.  Note that
  // the memory that the variables 'hi' and 'bye'
  // point to is allocated and initialized to contain
  // the strings "hello" and "goodbye" when the program
  // is loaded; we don't have to worry about free()'ing
  // that memory as a result.
  list = Push(list, (void *) hi);
  list = Push(list, (void *) bye);

  // Dynamically allocate some memory for a third
  // element -- the string "yo!".  We need four
  // bytes to store this string (remember there is a
  // NULL character '\0' at the end of a string).
  dynamic_string = (char *) malloc(4*sizeof(char));
  assert(dynamic_string != NULL);
  dynamic_string[0] = 'y';
  dynamic_string[1] = 'o';
  dynamic_string[2] = '!';
  dynamic_string[3] = '\0';
  list = Push(list, (void *) dynamic_string);

  // Iterate through the list.
  tmp = list;
  while (tmp != NULL) {
    printf("Payload: '%s'\n", (char *) (tmp->element));
    tmp = tmp->next;
  }

  // Pop the first element off the list.  This
  // should be our dynamically allocated string.
  ret = Pop(list, &list);
  assert(ret == dynamic_string);

  // free the memory that we previously malloc'ed
  // to hold the "yo!" string.
  free(ret);

  // pop the other two elements off the list.
  ret = Pop(list, &list);
  assert(ret == bye);
  ret = Pop(list, &list);
  assert(ret == hi);

  return 0;
}
