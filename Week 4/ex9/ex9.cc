/*
 * Copyright 2013 Chun-Wei Chen
 * 1267040
 * mijc0517@cs
 * 07/17/13
 */

#include <iostream>
#include <cstdlib>

#include "./IntPair.h"

// Gets the values stored in ip and then sets
// each of its values to be original value plus 1.
void Test(IntPair ip);

int main(int argc, char **argv) {
  IntPair p(7, 17);
  Test(p);

  int p_x, p_y;
  p.Get(&p_x, &p_y);

  // test whether class instances are passed by value or passed by reference
  if (p_x == 7 && p_y == 17)
    std::cout << "Is pass by value" << std::endl;
  else
    std::cout << "Is pass by reference" << std::endl;

  return EXIT_SUCCESS;
}

void Test(IntPair ip) {
  int ip_x, ip_y;
  ip.Get(&ip_x, &ip_y);
  ip.Set(ip_x + 1, ip_y + 1);
}
