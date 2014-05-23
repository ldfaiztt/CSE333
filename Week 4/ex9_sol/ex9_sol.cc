/*
 * Copyright 2012 Steven Gribble, Hal Perkins
 *
 *  This file is part of the UW CSE 333 course project exercises.
 *
 *  This is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This software is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

/* ex9.cc
 * CSE 333 exercise 9 sample solution.
 */

#include <cstdlib>
#include <iostream>

#include "./IntPair.h"

// Call the setter to modify z's internal state by
// adding 1 to each variable in the IntPair parameter z.
void Test(IntPair z) {
  int aval, bval;

  z.Get(&aval, &bval);
  z.Set(aval+1, bval+1);
}

int main(int argc, char **argv) {
  // Instantiate a new IntPair, then call Test to see if it changes
  // the contents of the pair
  IntPair a(0, 1);
  Test(a);

  // Use the accessor to get the a,b values from "a", and see if
  // they have changed or not.
  int aval, bval;
  a.Get(&aval, &bval);
  if ((aval != 0) || (bval != 1)) {
    std::cout << "Is pass by reference" << std::endl;
  } else {
    std::cout << "Is pass by value" << std::endl;
  }

  // Done!
  return EXIT_SUCCESS;
}
