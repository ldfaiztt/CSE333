#include <iostream>
#include <cstdlib>

void CalcArea(const int &width, const int &height, int *area) {
  *area = width * height;
}

int main(int argc, char **argv) {
  int w = 10, h = 20, a;

  CalcArea(w, h, &a);
  return EXIT_SUCCESS;
}
