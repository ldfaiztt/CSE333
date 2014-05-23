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

#include <utility>   // for std::pair
#include <string>    // for std::string
#include <iostream>  // for std::ostream

#ifndef _LEC15_EX1_SHAPE_H_
#define _LEC15_EX1_SHAPE_H_

const double PI = 3.141592653589793238462643383279502884;

// A "Shape" is an abstract class representing some kind of
// two-dimensional shape.
class Shape {
 public:
  Shape() { }
  // Make the destructor virtual; this is good hygiene, since it
  // guarantees that the full class hierarchy below Shape has virtual
  // destructors.
  virtual ~Shape() { }

  // Return the centroid of the shape.  A centroid is a pair, where
  // .first() is the x-coordinate and .second is the y-coordinate.
  virtual std::pair<double, double> Centroid() const = 0;

  // Return the area of the shape.
  virtual double Area() const = 0;

  // Move the shape by adding "delta" to the shape.
  virtual void Move(const std::pair<double, double> &delta) = 0;

  // Return a string with some pretty-printed shape details.
  virtual std::string Print() const = 0;
};

std::ostream &operator<<(std::ostream &out,
                         const std::pair<double,double> &p);

#endif  // _LEC15_EX1_SHAPE_H_
