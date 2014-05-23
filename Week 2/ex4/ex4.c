/*
 * Copyright 2013 Chun-Wei Chen
 * 1267040
 * mijc0517@cs
 * 07/03/13
 */

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include "GetPrime.h"

int main(int argc, char **argv) {
  printf("The 10th prime is: %" PRIu64 "\n", GetPrime(10));
  printf("The 168th prime is: %" PRIu64 "\n", GetPrime(168));
  printf("The 1000th prime is: %" PRIu64 "\n", GetPrime(1000));
  return EXIT_SUCCESS;
}
