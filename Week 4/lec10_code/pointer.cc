#include <iostream>
#include <cstdlib>

using namespace std;

int main(int argc, char **argv) {
  int x = 5, y = 10;
  int *z = &x;

  *z += 1;  // sets *z (and therefore x) to 6
  x += 1;   // sets x (and therefore *z) to 7

  z = &y;   // sets z to the address of y
  *z += 1;  // sets *z (and therefore y) to 11

  cout << "x: " << x << "; y: " << y << "; z: " << z << endl;
  return EXIT_SUCCESS;
}
