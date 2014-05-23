/*
 * Copyright 2013 Chun-Wei Chen
 * 1267040
 * mijc0517@cs
 * 07/03/13
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>
#include <math.h>

#include "GetPrime.h"

/*
 * Returns true if n is prime, false otherwise.
 */
bool IsPrime(uint64_t n);

uint64_t GetPrime(uint16_t n) {
  // check if passed in 0 as argument
  if (n == 0) {
    printf("Passed in %" PRIu16 ". Argument n must be a postive number.\n", n);
    return EXIT_FAILURE;
  }

  // return 2 directly if the user asks for first prime
  // taking care this case in order to increase the number
  // by 2 each iteration that reduces the number we need to
  // test by half
  else if (n == 1) {
    return 2;
  }
  
  // decrease n by 1 since alreay checked the user is not
  // asking for the first prime
  n--;
  
  // start from the second prime
  uint64_t num_to_test = 3;
  
  while (num_to_test <= (UINT64_MAX - 2)) {
    if (IsPrime(num_to_test)) {
      // n == 1 means the function has found the nth prime
      if (n == 1) {
        return num_to_test;
      }
      
      n--;
    }

    // test the next odd number
    num_to_test += 2;
  }

  // terminate the program if it reached UINT64_MAX
  // since UINT64_MAX is not a prime but we can't go up
  // any further to find next prime
  if (num_to_test == UINT64_MAX) {
    printf("Reached the maximum value of uint64_t.\n");
    return EXIT_FAILURE;
  }

  return 0;
}

bool IsPrime(uint64_t n) {
  // if n is 0 or 1, return false since neither of them are prime
  if (n == 0 || n == 1) {
    return false;
  }

  // return true if n is the only even prime -- 2
  else if (n == 2) {
    return true;
  }

  // return false if n is a even number greater than 2
  else if (n % 2 == 0) {
    return false;
  }

  // test every odd number i >= 3 and i <= n/2
  // to see if i is a factor of n
  for (uint64_t i = 3; i <= (n / 2); i += 2) {
    if (n % i == 0) {
      return false;
    }
  }

  return true;
}
