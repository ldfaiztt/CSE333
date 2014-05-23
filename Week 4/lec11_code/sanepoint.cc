#include "Point.h"

using namespace std;

int main(int argc, char **argv) {
  Point x(1, 2);
  Point y(3, 4);

  x.CopyFrom(y);

  Point z(x);  // compiler error, copy constructor is disabled.
  x = y;       // compiler error, assignment operator is disabled.
  return 0;
}
