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

// Lecture 17 exercise 1

#include <sstream>

#include "./Circle.h"

// Return the centroid of the shape.
std::pair<double, double> Circle::Centroid() const {
  return center_;
}

// Return the area of the shape.
double Circle::Area() const {
  return PI * radius_ * radius_;
}

// Move the shape by adding "delta" to the shape.
void Circle::Move(const std::pair<double, double> &delta) {
  center_.first = center_.first + delta.first;
  center_.second = center_.second + delta.second;
}

// Return a string with some pretty-printed shape details.
std::string Circle::Print() const {
  std::stringstream retS;
  retS << "[Circle] center=(";
  retS << center_.first << "," << center_.second;
  retS << "), radius=" << radius_;
  return retS.str();
}
