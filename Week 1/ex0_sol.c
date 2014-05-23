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

#include <stdio.h>   // for printf, sscanf
#include <stdlib.h>  // for EXIT_SUCCESS / EXIT_FAILURE and exit
#include <stdint.h>  // for uint64_t

// Print out the usage of the program and exit.
void Usage(void);

// Return the nth fractional term in the Nilakantha series.
double NthNilakantha(uint64_t n);

int main(int argc, char **argv) {
  // Make sure the user provided us with a command line argument
  // and exit if not.
  if (argc != 2)
    Usage();

  // Try to convert the command line argument to an integer >= 1
  // and exit if unable.
  uint64_t res;
  if ((sscanf(argv[1], "%llu", (unsigned long long *) &res) != 1) ||
      (res == 0)) {
    Usage();
  }

  // Calculate and print the estimate.
  double estimate = 3.0;
  for (uint64_t i = 1; i<= res; i++) {
    estimate += NthNilakantha(i);
  }
  printf("Our estimate of Pi is %.20f\n", estimate);

  // Quit.
  return EXIT_SUCCESS;
}

double NthNilakantha(uint64_t n) {
  // Figure out the Nth term in the Nilkantha series, according to the
  // formula provided in the exercise description.
  double term = 4.0;
  term /= 2.0 * n;
  term /= 2.0 * n + 1.0;
  term /= 2.0 * n + 2.0;
  if (n % 2 == 0)
    term *= -1.0;

  return term;
}

void Usage(void) {
  fprintf(stderr,
          "usage: ./ex0 n, where n>=0.  Prints pi estimated " \
          "to n terms of the Nilakantha series.\n");
  exit(EXIT_FAILURE);
}
