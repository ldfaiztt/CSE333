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

// Lecture 4 exercise 2

// Implement AllocSet( ), FreeSet( )
// - AllocSet( ) needs to use malloc twice:
//   - once to allocate a new ComplexSet
//   -  once to allocate the “points” field inside it
//
// - FreeSet( ) needs to use free twice

#include <stdio.h>   // needed for printf()
#include <assert.h>  // needed for assert()
#include <stdlib.h>  // needed for malloc()

typedef struct complex_st {
  double real;  // real component
  double imag;  // imaginary component
} Complex;

typedef struct complex_set_st {
  int      num_points_in_set;
  Complex *points;             // an array of Complex
} ComplexSet;

// here are the prototypes we need to implement
ComplexSet *AllocSet(Complex c_arr[], int size);
void FreeSet(ComplexSet *set);

int main(int argc, char **argv) {
  Complex arr[5];
  ComplexSet *x;

  x = AllocSet(arr, 5);
  assert(x->num_points_in_set == 5);
  FreeSet(x);

  return 0;
}

ComplexSet *AllocSet(Complex c_arr[], int size) {
  ComplexSet *newset;
  Complex    *pointarray;
  int i;

  assert(size > 0);

  // malloc a new ComplexSet
  newset = (ComplexSet *) malloc(sizeof(ComplexSet));
  if (newset == NULL)
    return NULL;

  // malloc the new pointarray
  pointarray = (Complex *) malloc(size*sizeof(Complex));
  if (pointarray == NULL) {
    // sneaky case: free the malloc'ed ComplexSet if we fail!
    free(newset);
    return NULL;
  }

  // initialize the fields
  newset->points = pointarray;
  for (i = 0; i < size; i++) {
    pointarray[i] = c_arr[i];
  }
  newset->num_points_in_set = size;
  return newset;
}

void FreeSet(ComplexSet *set) {
  // do some sanity checks
  assert(set != NULL);
  assert(set->points != NULL);

  // free the point array within the structure
  free(set->points);
  // good hygiene to set it to NULL after freeing
  set->points = NULL;
  // free the ComplexSet itself
  free(set);
}
