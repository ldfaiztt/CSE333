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
 * vector.c - implementation of an expandable vector of pointers
 * CSE 333 12sp exercise 5 sample solution.
 */

#include <assert.h>      // for assert
#include <stdbool.h>     // for bool
#include <stdlib.h>      // for malloc, free

#include "vector.h"      // definitions of vector type

// Local function:

// Return a newly allocated array with newLen elements.  Copy
// min(newLen,oldLen) elements from arry into the new array, and set
// any remaining elements in the new array to NULL.  Return NULL if
// allocation of new array fails.
// pre: arry != NULL and newLen > 0
static element_t *ResizeArray(element_t *arry, size_t oldLen, size_t newLen);


// Functions declared in vector.h

vector_t VectorCreate(size_t n) {
  assert(n > 0);

  // allocate vector data structure and array.
  // return NULL if either fails.
  vector_t v = (vector_t)malloc(sizeof(struct vector_t));
  if (v == NULL)
    return NULL;
  v->arry = (element_t*)malloc(n*sizeof(element_t));
  if (v->arry == NULL)
    return NULL;

  // save length in vector struct and initialize array elements to NULL
  v->length = n;
  for (size_t i = 0; i < n; ++i)
    v->arry[i] = NULL;

  // return pointer to new vector
  return v;
}

void VectorFree(vector_t v) {
  assert(v != NULL);
  free(v->arry);
  free(v);
}

bool VectorSet(vector_t v, size_t index, element_t e, element_t *prev) {
  assert(v != NULL);

  if (index >= v->length) {
    // need to increase array size.
    // attempt to allocate new array and return false if failure.
    size_t newLength = index+1;
    element_t *newArry = ResizeArray(v->arry, v->length, newLength);
    if (newArry == NULL)
      return false;

    // allocation successfull - free old array and replace with new one
    free(v->arry);
    v->arry = newArry;
    v->length = newLength;
  }

  // copy previous value at location index to caller, then store new
  // value and return success.
  // (note: if array was expanded, "previous value" will be NULL)
  *prev = v->arry[index];
  v->arry[index] = e;

  return true;
}

element_t VectorGet(vector_t v, size_t index) {
  assert(v != NULL);
  assert(index < v->length);

  return v->arry[index];
}

size_t VectorLength(vector_t v) {
  assert(v != NULL);
  return v->length;
}


// local function

static element_t *ResizeArray(element_t *arry, size_t oldLen, size_t newLen) {
  assert(arry != NULL);
  assert(newLen > 0);

  size_t i;
  size_t copyLen = oldLen > newLen ? newLen : oldLen;
  element_t *newArry;

  // Attempt to allocate new array of requested size
  newArry = (element_t*)malloc(newLen*sizeof(element_t));

  // Return NULL if allocation fails
  if (newArry == NULL)
    return NULL;

  // Copy all elements that will fit to new array
  for (i = 0; i < copyLen; ++i)
    newArry[i] = arry[i];

  // Initialize rest of new array (if any) to NULL.
  for (i = copyLen; i < newLen; ++i)
    newArry[i] = NULL;

  // return pointer to new array
  return newArry;
}

