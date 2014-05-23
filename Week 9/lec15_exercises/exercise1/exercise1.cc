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

// lec 15 exercise 1

#include <iostream>
#include <stdlib.h>

#include "./Shape.h"
#include "./Circle.h"
#include "./Triangle.h"
#include "./Square.h"

int main(int argc, char **argv) {
  std::cout.precision(10);

  Circle c(std::pair<double, double>(5, 5), 10);
  std::cout << c.Print() << std::endl;
  std::cout << "  area: " << c.Area() << std::endl;
  std::cout << "  centroid: " << c.Centroid() << std::endl;
  c.Move(std::pair<double, double>(1,2));
  std::cout << "  post-move centroid: " << c.Centroid() << std::endl;

  Triangle t(std::pair<double, double>(5, 5),
             std::pair<double, double>(7, 5),
             std::pair<double, double>(6, 6));
  std::cout << t.Print() << std::endl;
  std::cout << "  area: " << t.Area() << std::endl;
  std::cout << "  centroid: " << t.Centroid() << std::endl;
  t.Move(std::pair<double, double>(1,2));
  std::cout << "  post-move centroid: " << t.Centroid() << std::endl;

  Square s(std::pair<double, double>(5, 5),
           std::pair<double, double>(6, 5),
           std::pair<double, double>(6, 6),
           std::pair<double, double>(5, 6));
  std::cout << s.Print() << std::endl;
  std::cout << "  area: " << s.Area() << std::endl;
  std::cout << "  centroid: " << s.Centroid() << std::endl;
  s.Move(std::pair<double, double>(1,2));
  std::cout << "  post-move centroid: " << s.Centroid() << std::endl;

  return EXIT_SUCCESS;  // defined in stdlib.h
}
