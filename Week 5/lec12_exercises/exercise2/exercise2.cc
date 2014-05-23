/*
 * Copyright 2011, 2013 Steven Gribble, Hal Perkins
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

// lec 12 exercise 2
//
// Using the Tracer.cc/.h file from lecture, construct a vector of
// lists of Tracers
//
//  - i.e., a vector container, where each element is a list of Tracers
//
// Observe how many copies happen when you:
//   - use the “sort” algorithm to sort the vector
//   - use the “list.sort( )” function to sort each list

#include <cstdlib>      // for EXIT_SUCCESS
#include <vector>       // for std::vector
#include <list>         // for std::list
#include <algorithm>    // for std::sort
#include <iostream>     // for std::cout, std::endl;

#include "./Tracer.h"  // for the Tracer class

using std::vector;
using std::list;
using std::sort;
using std::for_each;

int main(int argc, char **argv) {
  vector<list<Tracer> > vlp;

  // A three-list vector, with 4 tracers per list.
  for (int i = 0; i < 3; i++) {
    list<Tracer> list;
    for (int j = 0; j < 4; j++) {
      list.push_back(Tracer());
    }
    vlp.push_back(list);
  }

  std::cout << (vlp[0] < vlp[1]) << std::endl;

  // Do the sorts.

  // Sort the vector.  This means the sort algorithm is using
  // the "<" operator to compare elements of the vector.  As it turns
  // out, C++'s STL defines overloads the "<" operator for when the
  // LHS and RHS are both lists!  In other words, you can do
  // (list1 < list2)!  See this for more info; it uses a lexicographical
  // comparison:
  //
  //   http://www.cplusplus.com/reference/stl/list/operators/
  //
  //   http://www.cplusplus.com/reference/algorithm/lexicographical_compare/
  sort(vlp.begin(), vlp.end());

  // Sort each list in the vector.
  for (uint32_t i = 0; i < vlp.size(); i++)
    vlp[i].sort();

  return EXIT_SUCCESS;
}
