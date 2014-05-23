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

// Lecture 15 exercise 1

#include <sstream>
#include <math.h>

#include "./Triangle.h"

// Return the centroid of the shape.
std::pair<double, double> Triangle::Centroid() const {
  std::pair<double, double> retval(
     (v1_.first + v2_.first + v3_.first)/3.0,
     (v1_.second + v2_.second + v3_.second)/3.0);
  return retval;
}

// Return the area of the shape.
double Triangle::Area() const {
  double a =
    sqrt(pow((v1_.first - v2_.first), 2) +
         pow((v1_.second - v2_.second), 2));
  double b = 
    sqrt(pow((v1_.first - v3_.first), 2) +
         pow((v1_.second - v3_.second), 2));
  double c = 
    sqrt(pow((v2_.first - v3_.first), 2) +
         pow((v2_.second - v3_.second), 2));
  double s = (a + b + c) / 2;
  double res = sqrt(s*(s-a)*(s-b)*(s-c));
  return res;
}

// Move the shape by adding "delta" to the shape.
void Triangle::Move(const std::pair<double, double> &delta) {
  v1_.first = v1_.first + delta.first;
  v2_.first = v2_.first + delta.first;
  v3_.first = v3_.first + delta.first;
  v1_.second = v1_.second + delta.second;
  v2_.second = v2_.second + delta.second;
  v3_.second = v3_.second + delta.second;
}

// Return a string with some pretty-printed shape details.
std::string Triangle::Print() const {
  std::stringstream retS;
  retS << "[Triangle] v1=(" << v1_.first << "," << v1_.second << "), ";
  retS << "v2=(" << v2_.first << "," << v2_.second << "), ";
  retS << "v3=(" << v3_.first << "," << v3_.second << ")";
  return retS.str();
}
