/*
 * Copyright 2013 Chun-Wei Chen
 * 1267040
 * mijc0517@cs
 * 06/26/13
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define SIZE 11

/*
 * Insert the elements of src in acsending order into dst.
 */
void CopyAndSort(uint64_t *src, uint64_t *dst, uint64_t len);

/*
 * Helper function to do the insertion sort.
 */
void insertion_sort(uint64_t num, uint64_t *arr, uint64_t len);

int main(int argc, char **argv) {
  uint64_t unsorted[SIZE] = {3, 2, 5, 7, 10, 4, 1, 7, 9, 8, 6};
  uint64_t sorted[SIZE];

  CopyAndSort(unsorted, sorted, SIZE);

  // print out the element in sorted
  for (uint64_t i = 0; i < SIZE - 1; i++)
    printf("%lu ", sorted[i]);
  printf("%lu\n", sorted[SIZE - 1]);

  return EXIT_SUCCESS;
}

void CopyAndSort(uint64_t *src, uint64_t *dst, uint64_t len) {
  // check if the length of the array passed in is less than 0
  if (len < 0) {
    printf("ERROR: length of the array must be >= 0.\n");
    exit(EXIT_FAILURE);
  }

  // no need to copy and sort if the array is empty
  if (len == 0)
    return;

  // insert the elements in ascending order into dst
  for (uint64_t i = 0; i < len; i++)
    insertion_sort(src[i], dst, i);
}

void insertion_sort(uint64_t num, uint64_t *arr, uint64_t len) {
  uint64_t idx = len;

  // find the right place to put num to make the array be in ascending order
  while (idx > 0 && arr[idx - 1] > num) {
    arr[idx] = arr[idx - 1];
    idx--;
  }

  // put the num into the place just found
  arr[idx] = num;
}
