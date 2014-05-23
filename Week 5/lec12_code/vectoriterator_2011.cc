#include <iostream>
#include <vector>

#include "Tracer.h"

using namespace std;

int main(int argc, char **argv) {
  Tracer a, b, c;
  vector<Tracer> vec;

  vec.push_back(a);
  vec.push_back(b);
  vec.push_back(c);

  cout << "Iterating:" << endl;
  // "auto" is a C++11 feature, and therefore is not yet
  // available on all compilers
  for (auto &p : vec) {
    cout << p << endl;
  }
  cout << "Done iterating!" << endl;
  return 0;
}
