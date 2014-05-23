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

/* Vector.cc - implementation of class Vector
 * CSE 333 exercise 10 sample solution.
 */

#include <iostream>
using namespace std;

#include "Vector.h"

// addition: return element-wise sum of this + other
Vector Vector::operator+(const Vector &other) {
  return Vector(x_ + other.x_, y_ + other.y_, z_ + other.z_);
}

// subtraction: return element-wise difference of this - other
Vector Vector::operator-(const Vector &other) {
  return Vector(x_ - other.x_, y_ - other.y_, z_ - other.z_);
}

// dot-product: if this is (a,b,c) and other is (x,y,z),
// return ax+by+cz
double Vector::operator*(const Vector &other) {
  return x_*other.x_ + y_*other.y_ + z_*other.z_;
}

// scalar multiplication: if this is (a,b,c), return (ak,bk,ck)
Vector Vector::operator*(const double k) {
  return Vector(x_ * k, y_ * k, z_ * k);
}

// Vector assignment
Vector &Vector::operator=(const Vector &rhs) {
  // replace state of this with values from rhs; do nothing if
  // self-asignment. (Even though in this particular case there would
  // be no harm, it's best to check for self-assignments and do
  // nothing if detected.)
  if (this != &rhs) {
    x_ = rhs.x_;
    y_ = rhs.y_;
    z_ = rhs.z_;
  }
  // return reference to lhs of assignment
  return *this;
}


// Stream output: << for Vectors
ostream & operator<<(ostream &out, const Vector &v) {
  out << "(" << v.x_ << "," << v.y_ << "," << v.z_ << ")";
  return out;
}
