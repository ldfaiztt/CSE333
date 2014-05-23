#include <cmath>
#include <cstdlib>
#include <iostream>

#include "./ThreeDPoint.h"

// SHOULD WE BE USING REFERENCES FOR ARGUMENTS "a" AND "b"?
// (Answer: ?)
double Distance(const ThreeDPoint &a, const ThreeDPoint &b) {
  double dist = pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2);
  return sqrt(dist);
}

int main(int argc, char **argv) {
  ThreeDPoint a(1,2,3), b(4,5,6);

  int dist = Distance(a, b);
  std::cout << "Distance(a,b) is " << dist << std::endl;
  return EXIT_SUCCESS;
}
