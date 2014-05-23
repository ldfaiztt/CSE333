/*
 * Copyright 2013 Chun-Wei Chen
 * 1267040
 * mijc0517@cs
 * 07/05/13
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "vector.h"

/*
 * Print the elements in the vector on a line.
 */
static void PrintIntVector(vector_t v);

#define INITIAL_SIZE 4
#define FINAL_SIZE 10

// test vector's functions
int main(int argc, char **argv) {
  size_t i;
  vector_t v = VectorCreate(INITIAL_SIZE);

  if (v == NULL)
    return EXIT_FAILURE;

  for (i = 0; i < FINAL_SIZE; ++i) {
    int *x = (int*)malloc(sizeof(int));
    if (x == NULL)
      return EXIT_FAILURE;

    *x = FINAL_SIZE - i;
    element_t old;

    // set the value to the position i in the vector
    // terminate the program if VectorSet failed
    if (!(VectorSet(v, i, x, &old)))
      return EXIT_FAILURE;
  }

  PrintIntVector(v);

  // free the values stored in the vector
  for (i = 0; i < VectorLength(v); ++i)
    free(VectorGet(v, i));
  // free the vector
  VectorFree(v);

  return EXIT_SUCCESS;
}

static void PrintIntVector(vector_t v) {
  size_t i;
  size_t length;

  assert(v != NULL);

  length = VectorLength(v);

  if (length > 0) {
    printf("[%d", *((int*)VectorGet(v, 0)));
    for (i = 1; i < VectorLength(v); ++i)
      printf(",%d", *((int*)VectorGet(v, i)));
    printf("]\n");
  }
}
