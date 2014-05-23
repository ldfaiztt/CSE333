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

// lec 11 exercise 1

#ifndef _LEC11_EX1_THREEDPOINT_H_
#define _LEC11_EX1_THREEDPOINT_H_

#include <iostream>

using namespace std;

// A "ThreeDPoint" is a class representing a three-dimensional point.
// Internally, a ThreeDPoint is represented with doubles for the x, y,
// and z axis values.
class ThreeDPoint {
 public:
  // Constructors; we use initialization lists to initialize.
  ThreeDPoint() : x_(0), y_(0), z_(0) { }
  ThreeDPoint(const double x, const double y, const double z)
    : x_(x), y_(y), z_(z) { }

  // Our CopyFrom function.
  ThreeDPoint &CopyFrom(const ThreeDPoint &py);

  // Accessors (inlined).
  double get_x() const { return x_; }
  double get_y() const { return y_; }
  double get_z() const { return z_; }

  // Inner product.
  double InnerProduct(const ThreeDPoint &pt) const;

  // Add, subtract operators.
  ThreeDPoint operator+(const ThreeDPoint &pt) const;
  ThreeDPoint operator-(const ThreeDPoint &pt) const;

  // Add/subtract and assign operators.
  ThreeDPoint &operator+=(const ThreeDPoint &pt);
  ThreeDPoint &operator-=(const ThreeDPoint &pt);

  // Override "<<" for std::ostream.
  friend ostream &operator<<(ostream &out, const ThreeDPoint &pt);

 private:
  // Disable the copy constructor and assignment operator.
  ThreeDPoint(const ThreeDPoint &pt);
  ThreeDPoint &operator=(const ThreeDPoint &pt);

  double x_, y_, z_;
};

#endif  // _LEC11_EX1_THREEDPOINT_H_
