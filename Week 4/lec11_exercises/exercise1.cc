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

// lec 11 exercise 1
//
// Modify your 3D Point class from lec10 exercise 1
// - disable the copy constructor and assignment operator
// - attempt to use copy & assign in code, and see what error
//   the compiler generates
// - write a CopyFrom() member function and try using it instead

#include <cstdlib>
#include "ThreeDPoint.h"

int main(int argc, char **argv) {
  ThreeDPoint a(5,6,7), b(1.0, 2.0, 3.0);

  // This should produce a compiler error, since we disabled the
  // copy constructor.

  // ThreeDPoint c(b);

  // So should this, since we disabled the assignment operator.

  // ThreeDPoint d;
  // d = a;

  // But, this should work.
  ThreeDPoint e;
  e.CopyFrom(a);

  cout << a << " " << b << " " << e << endl;
  cout << b.InnerProduct(e) << endl;

  return EXIT_SUCCESS;
}
