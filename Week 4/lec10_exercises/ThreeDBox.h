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

// lec 10 exercise 2

#ifndef _LEC10_EX2_THREEDBOX_H_
#define _LEC10_EX2_THREEDBOX_H_

#include <iostream>
#include "ThreeDPoint.h"

using namespace std;

// A "ThreeDBox" is a class representing a three-dimensional box
// aligned with the axis with right angles.  Internally, we
// represent a ThreeDBox with two ThreeDPoint objects: a and b,
// where a.x_ <= b.x_, a.y_ <= b.y_, a.z_ <= b.z_.
class ThreeDBox {
 public:
  // Constructors; use initialization lists to initialize.
  ThreeDBox() : a_(), b_() {}
  ThreeDBox(const ThreeDPoint &a, const ThreeDPoint &b)
    : a_(a), b_(b) { }

  // Copy constructor.
  ThreeDBox(const ThreeDBox &bx);

  // Accessors (inlined).
  ThreeDPoint get_a() const { return a_; }
  ThreeDPoint get_b() const { return b_; }

  // Volume.
  double Volume() const;

  // Tests if self is inside bx.
  bool IsInside(const ThreeDBox &bx) const;

  // Assignment operator.
  ThreeDBox &operator=(const ThreeDBox &pt);

  // Override "<<" for std::ostream.
  friend ostream &operator<<(ostream &out, const ThreeDBox &pt);

 private:
  ThreeDPoint a_, b_;
};

#endif  // _LEC10_EX2_THREEDBOX_H_
