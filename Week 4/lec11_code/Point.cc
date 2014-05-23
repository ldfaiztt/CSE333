#include <iostream>
#include <cmath>

#include "Point.h"

Point::Point(const int x, const int y) : x_(x), y_(y) {
  std::cout << "Calling point's constructor" << std::endl;
}

void Point::CopyFrom(const Point &copy_from_me) {
  x_ = copy_from_me.x_;
  y_ = copy_from_me.y_;
}

double Point::Distance(const Point &p) const {
  double distance = (x_ - p.x_) * (x_ - p.x_);
  distance += (y_ - p.y_) * (y_ - p.y_);
  return sqrt(distance);
}

void Point::SetLocation(const int x, const int y) {
  x_ = x;
  y_ = y;
}
