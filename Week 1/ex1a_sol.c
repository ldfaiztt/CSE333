/*
 * Copyright 2012, 2013 Steven Gribble, Hal Perkins
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

#include <stdio.h>   // for printf
#include <stdlib.h>  // for EXIT_SUCCESS

// Set the first element of the int array argument a to 5.
void TestArray(int a[]) {
  a[0] = 5;
}

// Set the double argument x to 123.45
void TestDouble(double x) {
  x = 123.45;
}

int main(int argc, char **argv) {
  // Test if doubles are pass-by-value or pass-by-reference
  // and print result.
  double x = 0.0;
  TestDouble(x);
  if (x == 0.0) {
    printf("double: pass-by-value\n");
  } else {
    printf("double: pass-by-reference\n");
  }

  // Test if arrays are pass-by-value or pass-by-reference
  // and print result.
  int v[5] = {0, 0, 0, 0, 0};
  TestArray(v);
  if (v[0] < 3) {
    printf("array of ints: pass-by-value\n");
  } else {
    printf("array of ints: pass-by-reference\n");
  }

  return EXIT_SUCCESS;
}
