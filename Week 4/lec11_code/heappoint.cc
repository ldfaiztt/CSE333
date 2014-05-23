#include <iostream>
#include "Point.h"

using namespace std;

int *AllocateInt(int x) {
  int *heapy_int = new int;
  *heapy_int = x;
  return heapy_int;
}

Point *AllocatePoint(int x, int y) {
  Point *heapy_point = new Point(1,2);
  return heapy_point;
}

int main(int argc, char **argv){
  Point *x = AllocatePoint(1, 2);
  int *y = AllocateInt(3);

  cout << "x's x_ coordinate: " << x->get_x() << endl;
  cout << "distance between x and self: " << x->Distance(*x) << endl;
  cout << "y: " << y << ", *y: " << *y << endl;

  delete x;
  delete y;

  return 0;
}
