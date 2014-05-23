#include <iostream>
#include <vector>

#include "Tracer.h"

using namespace std;

int main(int argc, char **argv) {
  Tracer a, b, c;
  vector<Tracer> vec;

  cout << "vec.push_back " << a << endl;
  vec.push_back(a);
  cout << "vec.push_back " << b << endl;
  vec.push_back(b);
  cout << "vec.push_back " << c << endl;
  vec.push_back(c);

  cout << "vec[0]" << endl;
  cout << vec[0] << endl;

  cout << "vec[2]" << endl;
  cout << vec[2] << endl;

  return 0;
}
