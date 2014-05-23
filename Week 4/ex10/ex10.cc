/*
 * Copyright 2013 Chun-Wei Chen
 * 1267040
 * mijc0517@cs
 * 07/19/13
 */

#include <iostream>

#include "./Vector.h"

int main(int argc, char **argv) {
  // test default constructor and the constructor with 3 arguments
  Vector u, v(1, 2, 3), w(-5, 4, -3);
  std::cout << "Vector u: " << u << std::endl;
  std::cout << "Vector v: " << v << std::endl;
  std::cout << "Vector w: " << w << std::endl;

  // test copy constructor
  Vector u_copy(u), v_copy(v), w_copy(w);
  std::cout << "copy of Vector u: " << u_copy << std::endl;
  std::cout << "copy of Vector v: " << v_copy << std::endl;
  std::cout << "copy of Vector w: " << w_copy << std::endl;

  // test "+" operator between two Vectors
  Vector u_plus_v = u + v;
  Vector v_plus_u = v + u;
  Vector v_plus_v = v + v;
  Vector v_plus_w = v + w;
  Vector w_plus_v = w + v;
  std::cout << "u + v = " << u_plus_v << std::endl;
  std::cout << "v + u = " << v_plus_u << std::endl;
  std::cout << "v + v = " << v_plus_v << std::endl;
  std::cout << "v + w = " << v_plus_w << std::endl;
  std::cout << "w + v = " << w_plus_v << std::endl;

  // test "-" operator between two Vectors
  Vector u_minus_v = u - v;
  Vector v_minus_u = v - u;
  Vector v_minus_v = v - v;
  Vector v_minus_w = v - w;
  Vector w_minus_v = w - v;
  std::cout << "u - v = " << u_minus_v << std::endl;
  std::cout << "v - u = " << v_minus_u << std::endl;
  std::cout << "v - v = " << v_minus_v << std::endl;
  std::cout << "v - w = " << v_minus_w << std::endl;
  std::cout << "w - v = " << w_minus_v << std::endl;

  // test dot product of Vectors
  double u_dot_v = u * v;
  double v_dot_u = v * u;
  double v_dot_v = v * v;
  double v_dot_w = v * w;
  double w_dot_v = w * v;
  std::cout << "dot product of u and v = " << u_dot_v << std::endl;
  std::cout << "dot product of v and u = " << v_dot_u << std::endl;
  std::cout << "dot product of v and v = " << v_dot_v << std::endl;
  std::cout << "dot product of v and w = " << v_dot_w << std::endl;
  std::cout << "dot product of w and v = " << w_dot_v << std::endl;

  // test Vectors multiplied by a scalar
  double k = 3;
  Vector ku = u * k;
  Vector kv = v * k;
  Vector kw = w * k;
  std::cout << "Vector u multiplied by scalar k = " << ku << std::endl;
  std::cout << "Vector v multiplied by scalar k = " << kv << std::endl;
  std::cout << "Vector w multiplied by scalar k = " << kw << std::endl;

  // test "=" operator
  w = v;
  std::cout << "Vector w = " << w << std::endl;
  v = u;
  std::cout << "Vector v = " << v << std::endl;
  v = w;
  std::cout << "Vector v = " << v << std::endl;
}
