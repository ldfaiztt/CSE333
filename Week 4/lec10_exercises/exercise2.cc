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

// lec 10 exercise 2
//
// Write a C++ program that:
//
// - has a class representing a 3-dimensional box
//
//   - uses your exercise 1 class representing 3d points to store
//     the coordinates of the vertices that define it
//
//   - assume the box has right-angles only and its faces are
//     parallel to the axes, so you need two vertices to define it
//
// - has methods to:
//
//   - test if one box is inside another box
//
//   - return the volume of a box
//
//   - handles “<<“, “=”, and a copy constructor
//
//   - uses “const” in all the right places

#include <cstdlib>

#include "ThreeDPoint.h"
#include "ThreeDBox.h"

int main(int argc, char **argv) {
  ThreeDPoint a(1,1,1), b(1,1,2), c(2,2,2), d(2,4,6);
  ThreeDBox empty(a, a), flat(a, b), small(a,c), big(a,d);
  ThreeDBox test = empty;

  cout << empty << endl;
  cout << flat << endl;
  cout << small << endl;
  cout << big << endl;

  cout << empty.Volume() << " " << flat.Volume() << " ";
  cout << small.Volume() << " " << big.Volume() << endl;

  cout << test << endl;
  test = big;
  cout << test << endl;

  cout << big.IsInside(small) << " ";
  cout << small.IsInside(big) << " ";
  cout << empty.IsInside(empty) << endl;

  return EXIT_SUCCESS;
}
