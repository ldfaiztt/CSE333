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

// lec 11 exercise 3
//
// Write a C++ function that:
// - uses new to dynamically allocate an array of strings
//    - and uses delete[ ] to free it
// - uses new to dynamically allocate an array of pointers to strings
//    - and then iterates through the array to use new to allocate a
//      string for each array entry and to assign to each array
//       element a pointer to the associated allocated string
//    - and then uses delete to delete each allocated string
//    - and then uses delete[] to delete the string pointer array
// (whew!)

#include <iostream>
#include <cstdlib>

int main(int argc, char **argv) {
  // Allocate an array of 10 strings
  std::string *s_arr = new std::string[10];

  // Append to each string in the array.
  for (int i = 0; i < 10; i++)
    s_arr[i] += "Yo!";

  // Free it
  delete[] s_arr;

  // Allocate an array of 10 string pointers.
  std::string **sptr_arr = new std::string*[10];

  // Allocate a string for each array, assign array element to it.
  for (int i = 0; i < 10; i++)
    sptr_arr[i] = new std::string("yo!");

  // Delete each allocated string.
  for (int i = 0; i < 10; i++)
    delete sptr_arr[i];

  // Delete the array of string pointers.
  delete[] sptr_arr;

  return EXIT_SUCCESS;
}
