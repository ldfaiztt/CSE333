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

#include "ThreeDPoint.h"

using namespace std;


// CopyFrom.
ThreeDPoint &ThreeDPoint::CopyFrom(const ThreeDPoint &py) {
  x_ = py.x_;
  y_ = py.y_;
  z_ = py.z_;
  return *this;
}

// Inner product.
double ThreeDPoint::InnerProduct(const ThreeDPoint &pt) const {
  double retval = 0.0;

  retval += (x_ * pt.x_);
  retval += (y_ * pt.y_);
  retval += (z_ * pt.z_);
  return retval;
}

// Arithmetic operators.
ThreeDPoint ThreeDPoint::operator+(const ThreeDPoint &pt) const {
  ThreeDPoint retval;

  retval.x_ = x_ + pt.x_;
  retval.y_ = y_ + pt.y_;
  retval.z_ = z_ + pt.z_;
  return retval;
}

ThreeDPoint ThreeDPoint::operator-(const ThreeDPoint &pt) const {
  ThreeDPoint retval;

  retval.x_ = x_ - pt.x_;
  retval.y_ = y_ - pt.y_;
  retval.z_ = z_ - pt.z_;
  return retval;
}

// Arithmetic + assign operators.
ThreeDPoint &ThreeDPoint::operator+=(const ThreeDPoint &pt) {
  x_ += pt.x_;
  y_ += pt.y_;
  z_ += pt.z_;
  return *this;
}

ThreeDPoint &ThreeDPoint::operator-=(const ThreeDPoint &pt) {
  x_ -= pt.x_;
  y_ -= pt.y_;
  z_ -= pt.z_;
  return *this;
}

// Override "<<" for std::ostream.  Note that this is not a member
// function of ThreeDPoint, but a global non-member function.  The
// "friend" is there so we can directly access pt's x_, y_, z_
// private variables.
ostream &operator<<(ostream &out, const ThreeDPoint &pt) {
  out << "(" << pt.x_ << "," << pt.y_ << "," << pt.z_ << ")";
  return out;
}
