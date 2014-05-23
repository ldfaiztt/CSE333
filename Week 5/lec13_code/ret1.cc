#include <cstdlib>
#include <iostream>

typedef struct Point_st {
  double x, y, z;
} Point;

// SHOULD WE BE USING A REFERENCE FOR WHAT IS RETURNED?
// (Answer: ?)
Point &MakePoint(const int x, const int y, const int z) {
  Point retval = {x, y, z};
  return retval;
}

int main(int argc, char **argv) {
  Point p = MakePoint(1, 2, 3);
  std::cout << p.x << "," << p.y << "," << p.z << std::endl;
  return EXIT_SUCCESS;
}
