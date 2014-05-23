#include <cstdlib>
#include <iostream>

// SHOULD WE BE USING REFERENCES FOR ARGUMENTS "a" AND "b"?
// (Answer: ?)
int LeastCommonMultiple(const int &a, const int &b) {
  for (int n=1; ; n++) {
    if ((n % a == 0) && (n % b == 0))
      return n;
  }
}

int main(int argc, char **argv) {
  int x = 12, y = 14;

  int lcm = LeastCommonMultiple(x, y);
  std::cout << "LCM(" << x << "," << y << ") is " << lcm << std::endl;
  return EXIT_SUCCESS;
}
