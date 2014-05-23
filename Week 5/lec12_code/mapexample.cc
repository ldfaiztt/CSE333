#include <iostream>
#include <map>
#include <algorithm>

#include "Tracer.h"

using namespace std;

void PrintOut(const pair<Tracer,Tracer> &p) {
  cout << "printout [" << p.first << "," << p.second << "]" << endl;
}

int main(int argc, char **argv) {
  Tracer a, b, c, d, e, f;
  map<Tracer,Tracer> table;
  map<Tracer,Tracer>::iterator it;

  table.insert(pair<Tracer,Tracer>(a, b));
  table[c] = d;
  table[e] = f;

  cout << "table[e]:" << table[e] << endl;
  it = table.find(c);
  cout << "PrintOut(*it), where it = table.find(c)" << endl;
  PrintOut(*it);

  cout << "iterating:" << endl;
  for_each(table.begin(), table.end(), &PrintOut);

  return 0;
}
