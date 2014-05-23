#include <stdlib.h>

// allocate/copy a new array from a[]
int *copy(int a[], int size) {
  int i, *a2;

  a2 = malloc(size * sizeof(int));
  if (a2 == NULL) {
    // out of memory
    return NULL;
  }

  // do the copy
  for (i = 0; i < size; i++)
    a2[i] = a[i];

  return a2;
}

int main(int argc, char **argv) {
  int nums[4] = {1,2,3,4};
  int *ncopy = copy(nums, 4);

  // make sure copy succeeded by checking for NULL return
  if (ncopy == NULL) {
    // out of memory
    return -1;
  }
  // .. do something with the array here ..

  // when you're done, free up the memory
  free(ncopy);

  return 0;
}
