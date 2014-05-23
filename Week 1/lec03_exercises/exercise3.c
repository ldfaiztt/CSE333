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

// Lecture 3 exercise 3

#include <stdio.h>   // needed for printf
#include <stdlib.h>  // needed for malloc, free
#include <assert.h>  // needed for assert

// Write a function that:
//
//  - accepts an (array of ints) and an (array length) as arguments
//
//  - malloc’s an (array of (int *)) of the same length
//
//  - initializes each element of the newly allocated array to point to
//    the corresponding element in the passed-in array
//
//  - returns a pointer to the newly allocated array

int **MakePointerArray(int *intarray, int arraylen) {
  int **parray;
  int   i;

  // do some sanity checking on the arguments
  assert(intarray != NULL);
  assert(arraylen > 0);

  // malloc the array, make sure we had the memory for it
  parray = (int **) malloc(arraylen*sizeof(int *));
  assert(parray != NULL);

  // initialize the array
  for (i = 0; i < arraylen; i++) {
    parray[i] = &(intarray[i]);
  }

  // return the array
  return parray;
}

int main(int argc, char **argv) {
  int **parray = NULL;
  int   intarray[2] = {1, 2};

  parray = MakePointerArray(intarray, 2);
  assert(parray != NULL);
  assert(parray[0] == &(intarray[0]));
  assert(parray[1] == &(intarray[1]));
  free(parray);

  return 0;
}
