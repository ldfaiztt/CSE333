#include <iostream>
#include <list>
#include <algorithm>

#include "Tracer.h"

using namespace std;

void PrintOut(const Tracer &p) {
  cout << "  printout: " << p << endl;
}
int main(int argc, char **argv) {
  Tracer a, b, c;
  list<Tracer> lst;

  lst.push_back(c);
  lst.push_back(a);
  lst.push_back(b);

  cout << "sort:" << endl;
  lst.sort();
  cout << "done sort!" << endl;
  for_each(lst.begin(), lst.end(), &PrintOut);

  return 0;
}
