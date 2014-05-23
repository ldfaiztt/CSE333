/*
 * Copyright 2012-13 Steven Gribble, Hal Perkins
 *
 *  This file is part of the UW CSE 333 course exercises (333exer).
 *
 *  333exer is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  333exer is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with 333exer.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>    // for printf
#include <stdlib.h>   // for exit, EXIT_SUCCESS
#include <stdbool.h>  // for bool

#include "./GetPrime.h"

// Return true if "factor" is a factor of num, otherwise false.
bool IsFactor(uint64_t factor, uint64_t num);

// Return true if "num" is prime, otherwise false.
bool IsPrime(uint64_t num);

uint64_t GetPrime(uint16_t n) {
  // error check: terminate program if n is 0
  if (n == 0) {
    fprintf(stderr, "error: GetPrime(0) called!\n");
    exit(EXIT_FAILURE);
  }

  uint64_t checknext = 2;
  // Advance checknext and count prime values as they are discovered.
  // When the nth one is found, return it.
  while (1) {
    // If checknext is prime, return it if it is the requested one,
    // otherwise decrease count of primes remaining to be discovered
    if (IsPrime(checknext)) {
      if (n == 1) {
        return checknext;
      }
      n--;
    }

    // terminate program if we've reached the largest positive integer
    if (checknext == UINT64_MAX) {
      fprintf(stderr, "Hit the largest uint64_t, aborting.\n");
      exit(EXIT_FAILURE);
    }

    // advance to next trial number
    checknext++;
  }

  // Should never get here.
  return 0;
}


bool IsFactor(uint64_t factor, uint64_t num) {
  if (num % factor == 0UL)
    return true;
  return false;
}

bool IsPrime(uint64_t num) {
  for (uint64_t i = 2L; i < num; i++) {
    if (IsFactor(i, num))
      return false;
  }
  return true;
}
