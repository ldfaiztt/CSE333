/*
 * Copyright 2011 Steven Gribble
 *
 *  This file is the solution to an exercise problem posed during
 *  one of the UW CSE 333 lectures (333exercises).
 *
 *  333exercises is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  333exercises is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with 333exercises.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _COMPLEX_H_
#define _COMPLEX_H_

// Here's our typedef for a Complex number.  We choose to
// expose the type to customers, so that customers can directly
// access fields instead of having to use accessor functions.
//
// A complex number is ((real) + i*(imaginary))
typedef struct {
  double real;
  double imaginary;
} Complex, *ComplexPtr;

// Adds a and b, returns the result.
Complex ComplexAdd(Complex a, Complex b);

// Subtracts b from a, returns the result.
Complex ComplexSubtract(Complex a, Complex b);

// Multplies a times b, returns the result.
Complex ComplexMultiply(Complex a, Complex b);

// Divides a by b, returns the result.  On some
// architectures and compilers, this function
// might cause a divide-by-zero exception to be thrown
// to the OS for some values of b; on other architectures,
// this might cause the fields of the returned complex
// to be set to floating point NAN.
Complex ComplexDivide(Complex a, Complex b);

#endif  // _COMPLEX_H_
