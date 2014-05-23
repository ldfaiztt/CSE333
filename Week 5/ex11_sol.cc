/*
 * Copyright 2012 Steven Gribble
 *
 *  This file is part of the UW CSE 333 course project exercises.
 *  (333exer).
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
 *  along with 333proj.  If not, see <http://www.gnu.org/licenses/>.
 */

/* ex11.cc: cse333 exercise 11 sample solution */

#include <algorithm>  // for std::sort
#include <cstdlib>    // for EXIT_FAILURE
#include <iostream>   // for std::{err, cin, cout, endl, istream}
#include <vector>     // for std::vector

using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::sort;
using std::vector;

// Read the next type "T" thing from input stream "in".  On error,
// execute exit(EXIT_FAILURE) after printing a helpful error message.
template <class T> T ReadValue(istream& in);

int main(int argc, char **argv) {
  vector<double> invec;

  // Read in the 10 doubles.
  cout << "Enter 10 doubles:" << endl;
  for (int i = 0; i < 10; i++) {
    double next = ReadValue<double>(cin);
    invec.push_back(next);
  }

  // Sort the vector, using the default "<" comparator on doubles.
  sort(invec.begin(), invec.end());

  // Print out the vector content.
  cout << "Your sorted doubles are:" << endl;
  for (int i = 0; i < 10; i++) {
    cout << invec[i] << endl;
  }

  // All done!
  return EXIT_SUCCESS;
}

// ReadValue implementation
template <class T> T ReadValue(istream& in) {
  T next;

  // Try do to the conversion; check on cin.good() afterwards.
  in >> next;
  if (!cin.good()) {
    cerr << "Couldn't handle input; conversion error or EOF." << endl;
    exit(EXIT_FAILURE);
  }
  return next;
}
