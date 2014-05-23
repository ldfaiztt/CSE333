/*
 * Copyright 2013 Chun-Wei Chen
 * 1267040
 * mijc0517@cs
 * 07/19/13
 */

#include <iostream>

#include "./Vector.h"

Vector::Vector() {
  x_ = y_ = z_ = 0;
}

Vector::Vector(const double x, const double y, const double z)
  : x_(x), y_(y), z_(z) {
}

Vector::Vector(const Vector &other) {
  x_ = other.x_;
  y_ = other.y_;
  z_ = other.z_;
}

Vector Vector::operator+(const Vector &v) const {
  Vector w;
  w.x_ = this->x_ + v.x_;
  w.y_ = this->y_ + v.y_;
  w.z_ = this->z_ + v.z_;
  return w;
}

Vector Vector::operator-(const Vector &v) const {
  Vector w;
  w.x_ = this->x_ - v.x_;
  w.y_ = this->y_ - v.y_;
  w.z_ = this->z_ - v.z_;
  return w;
}

double Vector::operator*(const Vector &v) const {
  return ((this->x_ * v.x_) + (this->y_ * v.y_) + (this->z_ * v.z_));
}

Vector Vector::operator*(double k) const {
  Vector w;
  w.x_ = this->x_ * k;
  w.y_ = this->y_ * k;
  w.z_ = this->z_ * k;
  return w;
}

Vector &Vector::operator=(const Vector &v) {
  if (this != &v) {
    this->x_ = v.x_;
    this->y_ = v.y_;
    this->z_ = v.z_;
  }
  return *this;
}

std::ostream &operator<<(std::ostream &out, const Vector &v) {
  out << "(" << v.x_ << "," << v.y_ << "," << v.z_ << ")";
  return out;
}
