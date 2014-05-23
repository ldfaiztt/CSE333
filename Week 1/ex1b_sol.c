/*
 * Copyright 2012-13 Steven Gribble, Hal Perkins
 *
 *  This file is part of the UW CSE 333 course exercises (333exer).
 *
 *  333exer is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  333exer is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with 333exer.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>   // for printf, sscanf
#include <stdint.h>  // for uint8_t, uint64_t
#include <stdlib.h>  // for EXIT_SUCCESS / EXIT_FAILURE and exit

// Copy length elements from source to dest, placing elements
// in dest in non-decreasing order.
void CopyAndSort(uint64_t *source, uint64_t *dest, uint64_t length);

// Given that array[0..len-1] is sorted in non-decreasing order, add
// num to array in the proper place so that array[0..len] is sorted.
// precondition: num > 0.
void DoInsert(uint64_t num, uint64_t *array, uint64_t len);

// Print out the contents of array with length number of elements to stdout.
void PrintArray(uint64_t *array, uint64_t length);

#define ARRAY_SIZE 11
int main(int argc, char **argv) {
  // Create unsorted array and second array to hold sorted copy
  uint64_t unsorted[ARRAY_SIZE] = {3, 2, 5, 7, 10, 4, 1, 7, 9, 8, 6};
  uint64_t sorted[ARRAY_SIZE];

  // Copy unsorted to sorted in non-decreasing order
  CopyAndSort(unsorted, sorted, ARRAY_SIZE);

  // Print out our sorted array.
  PrintArray(sorted, ARRAY_SIZE);

  // Quit.
  return EXIT_SUCCESS;
}

void CopyAndSort(uint64_t *source, uint64_t *dest, uint64_t length) {
  // Deal with the degenerate case of a zero-length array.
  if (length == 0)
    return;

  // Insertion sort
  // Copy first element
  dest[0] = source[0];

  // Insert remaining entries in order in dest.
  for (uint64_t i = 1; i < length; i++) {
    DoInsert(source[i], dest, i);
  }
}

void DoInsert(uint64_t num, uint64_t *array, uint64_t len) {
  // pre: len > 0 && array[0..len-1] sorted in ascending order
  uint64_t i = len;
  // inv: array[0..i-1] not checked and array[i+1..len] > num.
  while (i > 0 && array[i-1] > num) {
    array[i] = array[i-1];
    i--;
  }
  // array[0..i-1] <= num && array[i+1..len] > num
  array[i] = num;
}

void PrintArray(uint64_t *array, uint64_t length) {
  for (uint64_t i = 0; i < length; i++) {
    printf("%llu%c", array[i], i == (length-1) ? '\n' : ' ');
  }
}
