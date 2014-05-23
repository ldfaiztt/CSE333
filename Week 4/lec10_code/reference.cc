#include <iostream>
#include <cstdlib>

using namespace std;

int main(int argc, char **argv) {
  int x = 5, y = 10;
  int &z = x;  // binds the name "z" to variable x

  z += 1;  // sets z (and thus x) to 6
  x += 1;  // sets x (and thus z) to 7

  z = y;   // sets z (and thus x) to 10 (the value of y)
  z += 1;  // sets z (and thus x) to 11

  cout << "x: " << x << "; y: " << y << "; z: " << z << endl;
  return EXIT_SUCCESS;
}
