/*
 * Copyright 2012, 2013 Steven Gribble, Hal Perkins
 *
 *  This file is part of the UW CSE 333 course project exercises.
 *
 *  This is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This software is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * ex5.c - test program for an expandable vector of pointers
 * CSE 333 13sp exercise 5 sample solution.
 */

#include <assert.h>        // for assert
#include <stdbool.h>       // for bool
#include <stdio.h>         // for printf
#include <stdlib.h>        // for EXIT_...

#include "vector.h"

// Local function

// Print all elements of vector v on stdout as [v1,v2,...,vn]
// Assumes that all elements in v contain a pointer to an int
static void PrintIntVector(vector_t v);

// Initial and final size of test vector
#define INIT_VEC_SIZE 4
#define FINAL_VEC_SIZE 10

// Create a small test vector then fill it with new ints containing 0
// through 9 and print the result.  This is hardly an exhaustive test, but
// it is a corrected version of the test that was in the original code.
int main(int argc, char *argv[]) {
  size_t i;

  // allocate initial vector and exit if failure
  vector_t v = VectorCreate(INIT_VEC_SIZE);
  if (v == NULL)
    return EXIT_FAILURE;

  // store new int objects in locations 0-9 so that vector[i] holds int i.
  // exit if any step fails.
  for (i = 0; i < FINAL_VEC_SIZE; ++i) {
    int *x = (int*)malloc(sizeof(int));
    if (x == NULL)
      return EXIT_FAILURE;
    *x = i;
    element_t old;
    bool ok = VectorSet(v, i, x, &old);
    if (!ok)
      return EXIT_FAILURE;
  }

  // print final value of vector
  PrintIntVector(v);

  // Free int heap variables stored in the vector.  (ok even if
  // VectorGet returns NULL since free does nothing in that case)
  for (i = 0; i < VectorLength(v); ++i)
    free(VectorGet(v, i));

  // free the vector data structure
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
