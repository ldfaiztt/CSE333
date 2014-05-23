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

#ifndef VECTOR_H
#define VECTOR_H

/*
 * vector.h - interface to an expandable vector of pointers.  A
 * vector_t stores an ordered sequence of pointers of any type
 * (element_t which is void*).  Elements may be stored at any
 * non-negative index location and the vector automatically expands if
 * needed to include that location.  Entries in the vector are
 * automatically initialized to NULL if not set otherwise.
 *
 * CSE 333 13sp exercise 5 sample solution.
 */

#include <stddef.h>     // for size_t
#include <stdbool.h>    // for bool

// type of vector elements
typedef void* element_t;

// vector representation
typedef struct vector_t {
  size_t length;         //  length of arry
  element_t *arry;       //  data items - entries are NULL if not set otherwise
} *vector_t;

// Create a new vector with initial length n whose elements are
// initialized to NULL.  Return a pointer to the newly created vector
// or return NULL if an error occurs.
// pre: n > 0
vector_t VectorCreate(size_t n);

// Free the memory allocated for v.  Does not free any individual items
// stored in v - that is the client's responsibility.
// pre: v != NULL
void VectorFree(vector_t v);

// Store value e in location index of vector v and store in *prev
// the value that was previously in that location.  If index >=
// the current vector length, increase the length of the vector to
// index+1 and store NULL in any other newly created elements.
// Return true if successful and false if not.
// pre: v != NULL
bool VectorSet(vector_t v, size_t index, element_t e, element_t *prev);

// Return the element in the vector at position given by index.
// pre: v != NULL and index < VectorLength(v)
element_t VectorGet(vector_t v, size_t index);

// Return the current length of v.
// pre: v != NULL.
size_t VectorLength(vector_t v);

#endif
