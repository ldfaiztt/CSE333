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

// Lecture 3 exercise 2

#include <stdio.h>  // needed for printf

// Write a program that prints out whether the computer it is running
// on is little endian or big endian.

int main(int argc, char **argv) {
  int x = 1;
  char *charptr = (char *) &x;

  if (*charptr == 1) {
    printf("little endian\n");
  } else {
    printf("big endian\n");
  }

  return 0;
}
