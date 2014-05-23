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

#include <stdio.h>    // for printf
#include <stdlib.h>   // for EXIT_SUCCESS, malloc, free
#include <stdint.h>   // for int16_t

typedef struct point3d {
  int16_t x, y, z;   // the x, y, and z coordinates
} Point3d;

// Allocate and return a pointer to a new Point3d in the heap
// with fields initialized to the given x, y, and z values.  If
// allocation fails, returns NULL.
Point3d *AllocatePoint3d(int16_t x, int16_t y, int16_t z);

int main(int argc, char **argv) {
  // Try to allocate a triple.
  Point3d *pt = AllocatePoint3d(1, 2, 3);
  if (pt == NULL) {
    fprintf(stderr, "AllocatePoint3d() failed.\n");
    return EXIT_FAILURE;
  }

  // Check that the triple fields have proper values
  if (pt->x != 1 || pt->y != 2 || pt->z != 3) {
    fprintf(stderr, "One or more point fields have wrong value\n");
    return EXIT_FAILURE;
  }

  // It worked!  Clean up by freeing the allocated memory.
  free(pt);
  return EXIT_SUCCESS;
}

Point3d *AllocatePoint3d(int16_t x, int16_t y, int16_t z) {
  Point3d *retval = (Point3d *) malloc(sizeof(Point3d));
  if (retval == NULL) {
    // out of memory
    return NULL;
  }

  // Assign values to retval's fields.
  retval->x = x;
  retval->y = y;
  retval->z = z;

  // Return (a pointer to) the allocated triple.
  return retval;
}
