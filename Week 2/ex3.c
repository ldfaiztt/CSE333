/*
 * Copyright 2013 Chun-Wei Chen
 * 1267040
 * mijc0517@cs
 * 07/01/13
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct point3d_st {
  int16_t x;  // x coordinate
  int16_t y;  // y coordinate
  int16_t z;  // z coordinate
} Point3d;

// Allocates the space for a new Point3d and return the pointer
// to that Point3d with given x, y, z value.
// Returns NULL if failing to allocate space for Point3d.
Point3d *AllocatePoint3d(int16_t x, int16_t y, int16_t z);

int main(int argc, char **argv) {
  // try AllocatePoint3d()
  Point3d *point3d_ptr = AllocatePoint3d(1, 3, 5);

  if (point3d_ptr == NULL) {
    printf("AllocatePoint3d() failed to allocate space for a new Point3d.\n");
    return EXIT_FAILURE;
  }

  // check if x field has the expected value
  if (point3d_ptr->x != 1) {
    printf("Point3d's x field has wrong value.\n");
    return EXIT_FAILURE;
  }

  // check if y field has the expected value
  if (point3d_ptr->y != 3) {
    printf("Point3d's y field has wrong value.\n");
    return EXIT_FAILURE;
  }

  // check if z field has the expected value
  if (point3d_ptr->z != 5) {
    printf("Point3d's z field has wrong value.\n");
    return EXIT_FAILURE;
  }

  printf("AllocatePoint3d() works fine.\n");

  // free the pointer after checking AllocatePoint3d() works properly
  free(point3d_ptr);
  return EXIT_SUCCESS;
}

Point3d *AllocatePoint3d(int16_t x, int16_t y, int16_t z) {
  // allocate space for a new Point3d
  Point3d *ptr = (Point3d *) malloc(sizeof(Point3d));

  // assign given x, y, z value to the new Point3d
  // if success to allocate space
  if (ptr != NULL) {
    ptr->x = x;
    ptr->y = y;
    ptr->z = z;
  }

  // return the pointer to the Point3d, or NULL if fail to allocate space
  return ptr;
}
