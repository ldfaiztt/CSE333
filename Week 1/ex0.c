/*
 * Chun-Wei Chen
 * 1267040
 * mijc0517@cs
 * 06/25/13
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/*
 * Calculates the sum of Nilakantha series from 0th term to nth term.
 */
double nilakanthaSeries(uint64_t n) {
    double result = 3.0; // estimation of pi from 0th term to nth term of the Nilakantha series
    int64_t sign = -1; // sign of the Nilakantha series's term

    for (uint64_t i = 1; i <= n; i++) {
        // odd-number term has positive sign and
        // even-number term (except 0th term) has negative sign
        sign *= -1;
        result += sign * (4.0 / ((2.0 * i) * (2.0 * i + 1) * (2.0 * i + 2)));
    }

    return result; 
}

/*
 * Takes an non-negative integer as argument and calculate the estimation of pi.
 */
int main(int argc, char **argv) {
    int64_t arg; // store user's input
    uint64_t checked_arg; // store user's input after verifying it's non-negative integer
    double estimate = 3.0; // estimation of pi

    // check if user passes in exact one argument
    if (argc != 2) {
        printf("ERROR: This program takes one non-negative integer as argument.\n");
        exit(EXIT_FAILURE);
    }

    // check the arugment passed in is an integer
    if (sscanf(argv[1], "%lld", (long long *) &arg) != 1) {
        printf ("ERROR: %s is not an integer.\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    // check the argument passed in is a non-negative integer
    if (arg < 0) {
        printf ("ERROR: %lld is not a non-negative integer.\n", (long long) arg);
        exit(EXIT_FAILURE);
    }

    checked_arg = (uint64_t) arg;

    // calculate the estimation of pi
    estimate = nilakanthaSeries(checked_arg);

    printf("Our estimate of Pi is %.20f\n", estimate);

    return EXIT_SUCCESS;
}
