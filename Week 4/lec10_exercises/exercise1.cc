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

// lec 10 exercise 1
//
// Write a C++ program that:
// - has a class representing a 3-dimensional point
// - has methods to:
//   - return the inner product of two points
//   - handles “<<“, “+”, “-”, “+=”, “-=”, “=”, and copy constructors
//   - uses “const” in all the right places

#include <cstdlib>
#include "ThreeDPoint.h"

int main(int argc, char **argv) {
  ThreeDPoint a, b(1.0, 2.0, 3.0), c(b), d = c, e;

  b += a;
  c += b;
  d -= c;
  e = d + (a + b + c - d);
  a = c - (b + b);
  a = a;

  cout << a << " " << b << " " << c << " " << d << " " << e << endl;
  cout << b.InnerProduct(e) << endl;

  return EXIT_SUCCESS;
}
