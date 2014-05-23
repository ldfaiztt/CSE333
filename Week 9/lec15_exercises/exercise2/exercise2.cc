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

// lec 15 exercise 2

#include <iostream>
#include <stdlib.h>
#include <utility>
#include <algorithm>
#include <vector>

#include "./Shape.h"
#include "./ShapeWrapper.h"
#include "./Triangle.h"
#include "./Square.h"

void PrintOut(ShapeWrapper s) {
  std::cout << s.shape_ptr_->Print() << std::endl;
}

int main(int argc, char **argv) {
  std::pair<double,double> v1(1,1), v2(1,2), v3(2,2), v4(2,1), v5(3,3);
  ShapeWrapper sw1((Shape *) new Triangle(v1, v2, v3));
  ShapeWrapper sw2((Shape *) new Triangle(v1, v2, v4));
  ShapeWrapper sw3((Shape *) new Square(v1, v2, v3, v4));
  ShapeWrapper sw4((Shape *) new Triangle(v1, v4, v5));

  std::vector<ShapeWrapper> vs;
  vs.push_back(sw1);
  vs.push_back(sw2);
  vs.push_back(sw3);
  vs.push_back(sw4);

  std::sort(vs.begin(), vs.end());
  std::for_each(vs.begin(), vs.end(), PrintOut);

  while(vs.size() >= 1) {
    ShapeWrapper nx = vs.back();
    vs.pop_back();
    delete nx.shape_ptr_;
  }

  return EXIT_SUCCESS;  // defined in stdlib.h
}
