#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "ll.h"

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
