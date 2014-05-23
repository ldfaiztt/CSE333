#include <cmath>

#include "SimplePoint.h"

double SimplePoint::Distance(const SimplePoint &p) const {
  double distance = (x_ - p.x_) * (x_ - p.x_);
  distance += (y_ - p.y_) * (y_ - p.y_);
  return sqrt(distance);
}

void SimplePoint::SetLocation(const int x, const int y) {
  x_ = x;
  y_ = y;
}

int main(int argc, char **argv) {
  SimplePoint x;     // invokes synthesized default constructor.
  SimplePoint y(x);  // invokes synthesized copy constructor.
  y = x;             // invokes synthesized assignment operator.
  return 0;
}
