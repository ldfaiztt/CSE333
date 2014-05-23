#include <iostream>
#include <vector>
#include <algorithm>

#include "Tracer.h"

using namespace std;

void PrintOut(const Tracer &p) {
  cout << "  printout: " << p << endl;
}

int main(int argc, char **argv) {
  Tracer a, b, c;
  vector<Tracer> vec;

  vec.push_back(c);
  vec.push_back(a);
  vec.push_back(b);

  cout << "sort:" << endl;
  sort(vec.begin(), vec.end());
  cout << "done sort!" << endl;
  for_each(vec.begin(), vec.end(), &PrintOut);

  return 0;
}
