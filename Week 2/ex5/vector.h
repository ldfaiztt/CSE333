/*
 * Copyright 2013 Chun-Wei Chen
 * 1267040
 * mijc0517@cs
 * 07/05/13
 */

#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <stdbool.h>
#include <stddef.h>

// Type of vector's element
typedef void* element_t;

// Type of vector
typedef struct vector_t {
  size_t length;
  element_t *arry;
} *vector_t;

/*
 * Creates a new vector with length n and all its elements are set to NULL.
 * Returns a pointer to the vector, or NULL if fail to allocate space for
 * the vector.
 * n must be greater than 0.
 */
vector_t VectorCreate(size_t n);

/*
 * Frees the memory allocated for the v. Doesn't free the items stored
 * in v.
 * v != NULL.
 */
void VectorFree(vector_t v);

/*
 * Sets position index in the vector v to be e and stores the value
 * previously stored in that position in *prev. If index >= 
 * vector's length, increase the vector's length to (index + 1) and
 * set newly created elements to NULL. Returns true if set 
 * successfully; false otherwise.
 * v != NULL and index must be greater than or equal to 0.
 */
bool VectorSet(vector_t v, size_t index, element_t e, element_t *prev);

/*
 * Returns the element at the given position index in the vector v.
 * v != NULL && index must be less than the vector length.
 */
element_t VectorGet(vector_t v, size_t index);

/*
 * Returns the length of v.
 * v != NULL.
 */
size_t VectorLength(vector_t v);

#endif
