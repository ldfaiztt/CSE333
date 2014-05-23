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

// lec 14 exercise 1

#include <boost/shared_ptr.hpp>
#include <stdlib.h>
#include <iostream>
#include <vector>

#include "./Triple.h"

using namespace lec14;
using namespace boost;

typedef Triple<shared_ptr<int>, shared_ptr<int>, shared_ptr<int> > TripleInt;

int main(int argc, char **argv) {
  // Construct the triples.
  TripleInt t1(shared_ptr<int>(new int(5)),
               shared_ptr<int>(new int(10)),
               shared_ptr<int>(new int(15)));

  TripleInt t2(shared_ptr<int>(new int(10)),
               shared_ptr<int>(new int(20)),
               shared_ptr<int>(new int(30)));

  TripleInt t3(shared_ptr<int>(new int(15)),
               shared_ptr<int>(new int(30)),
               shared_ptr<int>(new int(45)));

  // Construct the vector, push the triples into it.
  std::vector<TripleInt> vec;
  vec.push_back(t1);
  vec.push_back(t2);
  vec.push_back(t3);

  // Reverse the elements of the vector.
  for (unsigned int i = 0; i < vec.size() / 2; i++) {
    TripleInt tmp = vec[i];
    vec[i] = vec[vec.size() - i - 1];
    vec[vec.size() - i - 1] = tmp;
  }

  for (unsigned int i = 0; i < vec.size(); i++) {
    std::cout << "vec[" << i << "]: ";
    std::cout << *(vec[i].first_);
    std::cout << " " << *(vec[i].second_);
    std::cout << " " << *(vec[i].third_) << std::endl;;
  }

  return EXIT_SUCCESS;
}
