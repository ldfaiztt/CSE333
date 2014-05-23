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

// Lecture 15 exercise 2

#include "./Shape.h"

#ifndef _LEC15_EX2_SHAPEWRAPPER_H_
#define _LEC15_EX2_SHAPEWRAPPER_H_

// A "ShapeWrapper" is a wrapper class for shape that stores
// a pointer so we can embed in STL containers.
class ShapeWrapper {
 public:
  ShapeWrapper(Shape *shape_ptr) : shape_ptr_(shape_ptr) { }
  ~ShapeWrapper() { }

  bool operator<(const ShapeWrapper &rhs) const;
  Shape *shape_ptr_;
};

#endif  // _LEC15_EX2_SHAPEWRAPPER_H_
