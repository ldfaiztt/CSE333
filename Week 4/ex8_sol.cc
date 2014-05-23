/*
 * Copyright 2012, 2013 Steven Gribble, Hal Perkins
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

#include <inttypes.h>
#include <cstdlib>
#include <iostream>    // cpplint complains about streams, but ok for us

// This statement tells the compiler that we want to import all names
// from the "std" namespace into our global namespace.  After this
// statement, we can refer to names like "cout" instead of using the
// more verbose "std::cout".  cpplint will complain about it, but it's
// ok for what we're doing.

using namespace std;

// = "test_factor is a factor of num"
bool isfactor(uint64_t num, uint64_t test_factor) {
  // sanity check
  if (test_factor > num)
    return false;

  // test for "is it a factor?" (relies on truncating integer division)
  return (((num / test_factor) * test_factor) == num);
}

int main(int argc, char **argv) {
  uint64_t num;

  // Prompt the user for a number and read it into num.
  cout << "Which positive integer would you like me to factorize? ";
  cin >> num;

  // Stop if invalid input (optional - we had not covered this
  // before this exercise was due)
  if (!cin) {
    cerr << "Input is not a valid positive integer" << endl;
    return EXIT_FAILURE;
  }


  // Can't handle 0.  Error if entered.
  if (num == 0) {
    cerr << "Cannot factorize 0" << endl;
    return EXIT_FAILURE;
  }

  // Loop testing successive numbers for being a factor
  // and print out each one discovered.
  for (uint64_t i = 1; i <= num; i++) {
    if (isfactor(num, i)) {
      cout << (i == 1 ? "" : " ") << i;
    }
  }

  // Finish with an endline.
  cout << endl;
  return EXIT_SUCCESS;
}
