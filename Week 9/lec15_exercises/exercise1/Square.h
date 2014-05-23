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

#include <cmath>

#include "./Shape.h"
#include "./Triangle.h"

#ifndef _LEC15_EX1_SQUARE_H_
#define _LEC15_EX1_SQUARE_H_

// A "Square" is a concrete derived class of Shape representing a
// square.
class Square : Shape {
 public:
  Square(std::pair<double, double> v1,
         std::pair<double, double> v2,
         std::pair<double, double> v3,
         std::pair<double, double> v4)
    : v1_(v1), v2_(v2), v3_(v3), v4_(v4) { }

  virtual ~Square() { }

  // Return the centroid of the shape.
  virtual std::pair<double, double> Centroid() const;

  // Return the area of the shape.
  virtual double Area() const;

  // Move the shape by adding "delta" to the shape.
  virtual void Move(const std::pair<double, double> &delta);

  // Return a string with some pretty-printed shape details.
  virtual std::string Print() const;

 private:
  std::pair<double, double> v1_, v2_, v3_, v4_;
};

#endif  // _LEC15_EX1_SQUARE_H_
