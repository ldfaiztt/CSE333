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

// Lecture 3 exercise 1

#include <stdio.h>

int foo(int *bar, int **baz) {
  *bar = 5;
  *(bar+1) = 6;
  *baz = bar+2;
  return *((*baz)+1);
}

int main(int argc, char **argv) {
  int arr[4] = {1, 2, 3, 4};
  int *ptr;

  arr[0] = foo(&(arr[0]), &ptr);
  printf("%d %d %d %d %d\n",
         arr[0], arr[1], arr[2], arr[3], *ptr);
  return 0;
}
