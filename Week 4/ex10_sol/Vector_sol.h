/*
 * Copyright 2013 Hal Perkins
 *
 *  This file is part of the UW CSE 333 course project exercises.
 *
 *  This is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This software is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

/* Vector.h - definition of 3D vector class
 * CSE 333 exercise 10 sample solution.
 */

#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
using namespace std;

// A Vector represents a vector in 3-space.
class Vector {
 public:
  // constructors:

  // Default: construct the vector (0,0,0)
  Vector()
    : x_(0.0), y_(0.0), z_(0.0) { }

  // Construct the vector (x,y,z)
  Vector(const double x, const double y, const double z)
    : x_(x), y_(y), z_(z) { }

  // Copy constructor
  Vector(const Vector &v)
    : x_(v.x_), y_(v.y_), z_(v.z_) { }

  // Assignment for Vectors
  Vector &operator=(const Vector &rhs);

  // addition and subtraction: produce a new Vector that results from
  // element-wise addition or subtraction of this with other
  Vector operator+(const Vector &other);
  Vector operator-(const Vector &other);

  // dot-product: if this is (a,b,c) and other is (x,y,z),
  // return ax+by+cz
  double operator*(const Vector &other);

  // scalar multiplication: if this is (a,b,c), return (ak,bk,ck)
  Vector operator*(const double k);

  // Stream output: define << for Vectors
  friend ostream & operator<<(ostream &out, const Vector &v);

 private:
  // The representation of a Vector is three doubles giving
  // the x, y, and z magnitudes.
  double x_, y_, z_;
};

#endif
