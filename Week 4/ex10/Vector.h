/*
 * Copyright 2013 Chun-Wei Chen
 * 1267040
 * mijc0517@cs
 * 07/19/13
 */

#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <iostream>

class Vector {
 public:
  // default constructor, initializes a Vector to (0,0,0)
  Vector();
  // initializes a Vector to (x,y,z)
  Vector(const double x, const double y, const double z);
  // copy constructor
  Vector(const Vector &other);

  // returns a new vector that is equal to this vector + v
  Vector operator+(const Vector &v) const;
  // returns a new vector that is equal to this vector - v
  Vector operator-(const Vector &v) const;
  // returns the dot product of this vector and v
  double operator*(const Vector &v) const;
  // returns a new vector that is equal to k * this vecotr
  Vector operator*(const double k) const;
  // override "=" operator
  Vector &operator=(const Vector &v);

  // string representation of the vector
  friend std::ostream &operator<<(std::ostream &out, const Vector &v);

 private:
  double x_;  // x coordinate of the vector
  double y_;  // y coordinate of the vector
  double z_;  // z coordinate of the vector
};

#endif
