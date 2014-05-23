/*
 * Copyright 2013 Chun-Wei Chen
 * 1267040
 * mijc0517@cs
 * 07/05/13
 */

#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

#include "vector.h"

/*
 * Returns a newly allocated array with length newLen. If newLen <= oldLen
 * then the returned array will contain only newLen elements from the
 * original array; otherwise, the returned array will be padded with 
 * NULL elements.
 * array != NULL, oldLen and newLen must be greater than 0
 */
static element_t *ResizeArray(element_t *arry, size_t oldLen, size_t newLen);

vector_t VectorCreate(size_t n) {
  // check if size n passed in is greater than 0
  assert(n > 0);

  // allocate space for the vector
  vector_t v = (vector_t)malloc(sizeof(struct vector_t));
  // return NULL if fail to allocate space for the vector
  if (v == NULL)
    return NULL;

  // allocate space for the array of the vector
  v->arry = (element_t*)malloc(n*sizeof(element_t));
  // return NULL if fail to allocate space for the array of the vector
  if (v->arry == NULL)
    return NULL;

  // store the length in the vector
  v->length = n;
  // set elements of array to NULL
  for (size_t i = 0; i < n; i++)
    v->arry[i] = NULL;

  return v;
}

void VectorFree(vector_t v) {
  // check if vector v passed in is not NULL
  assert(v != NULL);

  free(v->arry);
  free(v);
}

bool VectorSet(vector_t v, size_t index, element_t e, element_t *prev) {
  // check if the inputs are valid
  assert(v != NULL);
  assert(index >= 0);

  if (index >= v->length) {
    size_t newLength = index+1;

    element_t *newArry = ResizeArray(v->arry, v->length, newLength);
    // return false if fail to allocate space for newArry
    if (newArry == NULL)
      return false;

    // free the original array
    free(v->arry);

    v->arry = newArry;
    v->length = newLength;
  }

  // copy the previous value at the location index and store
  // the new value e to that location
  *prev = v->arry[index];
  v->arry[index] = e;

  return true;
}

element_t VectorGet(vector_t v, size_t index) {
  // check if vector v passed in is not NULL
  assert(v != NULL);

  return v->arry[index];
}

size_t VectorLength(vector_t v) {
  // check if vector v passed in is not NULL
  assert(v != NULL);

  return v->length;
}

static element_t *ResizeArray(element_t *arry, size_t oldLen, size_t newLen) {
  // check if the inputs are valid
  assert(arry != NULL);
  assert(oldLen > 0);
  assert(newLen > 0);

  size_t i;
  size_t copyLen = oldLen > newLen ? newLen : oldLen;
  element_t *newArry;

  // allocate new array with size newLen
  newArry = (element_t*)malloc(newLen*sizeof(element_t));

  // return NULL if fail to allocate space for the new array
  if (newArry == NULL)
    return NULL;

  // copy copyLen elements from original array to new array
  for (i = 0; i < copyLen; ++i)
    newArry[i] = arry[i];

  // initialize rest of new array to NULL
  for (i = copyLen; i < newLen; ++i)
    newArry[i] = NULL;

  return newArry;
}
