/*
 * Copyright 2013 Chun-Wei Chen
 * 1267040
 * mijc0517@cs
 * 06/26/13
 */

#include <stdio.h>
#include <stdlib.h>

#define EPSILON 0.000000001

/*
 * Take a double as argument and increase its value.
 */
void incr_double(double d);

/*
 * Take an array of ints as argument and increase its first element.
 */
void incr_first_element(int ia[]);

int main(int argc, char **argv) {
  // test whether double is pass-by-value or pass-by-reference
  double d = 1.0;
  double cd = d;
  incr_double(cd);

  if (abs(d - cd) < EPSILON) {
    printf("double: pass-by-value\n");
  } else {
    printf("double: pass-by-reference\n");
  }

  int ia[3] = {1, 2, 3};
  incr_first_element(ia);

  if (ia[0] == 1) {
    printf("array of ints: pass-by-value\n");
  } else {
    printf("array of ints: pass-by-reference\n");
  }

  return EXIT_SUCCESS;
}

void incr_double(double d) {
  d += 1;
}

void incr_first_element(int ia[]) {
  ia[0] += 1;
}
