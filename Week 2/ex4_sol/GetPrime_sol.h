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

#ifndef _EX4_GETPRIME_H_
#define _EX4_GETPRIME_H_

#include <stdint.h>  // for uint64_t etc.

// Returns the nth prime number; for example:
//
//   GetPrime(1) --> 2
//   GetPrime(2) --> 3
//   GetPrime(3) --> 5
//   GetPrime(4) --> 7
//   etc.
//
// n must be >0.
uint64_t GetPrime(uint16_t n);

#endif   // _EX4_GETPRIME_H_
