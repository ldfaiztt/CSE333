#include <iostream>
#include <string>

#include "Pair.h"

int main(int argc, char **argv) {
  Pair<std::string> ps;
  std::string x("foo"), y("bar");
  
  ps.set_first(x);
  ps.set_second(y);
  ps.Reverse();
  std::cout << ps.get_first() << std::endl;

  return 0;
}
