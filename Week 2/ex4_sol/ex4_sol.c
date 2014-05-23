/*
 * Copyright 2012 Steven Gribble
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

#include <stdio.h>        // for printf
#include <stdlib.h>       // for EXIT_SUCCESS, malloc, free
#include <inttypes.h>     // for PRIu64

#include "./GetPrime.h"  // for GetPrime

int main(int argc, char **argv) {
  printf("The 5th prime is: %" PRIu64 ".\n", GetPrime(5));
  printf("The 105th prime is: %" PRIu64 ".\n", GetPrime(105));
  return EXIT_SUCCESS;  // EXIT_SUCCESS defined in stdlib.h.
}
