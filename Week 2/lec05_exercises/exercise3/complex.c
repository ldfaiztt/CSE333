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

#include "complex.h"

Complex ComplexAdd(Complex a, Complex b) {
  Complex res;

  res.real = a.real + b.real;
  res.imaginary = a.imaginary + b.imaginary;
  return res;
}

Complex ComplexSubtract(Complex a, Complex b) {
  Complex res;

  res.real = a.real - b.real;
  res.imaginary = a.imaginary - b.imaginary;
  return res;
}

Complex ComplexMultiply(Complex a, Complex b) {
  Complex res;

  res.real = (a.real * b.real) - (a.imaginary * b.imaginary);
  res.imaginary = (a.imaginary * b.real) - (a.real * b.imaginary);
  return res;
}

Complex ComplexDivide(Complex a, Complex b) {
  // This is the hard one.  See Wikipedia for the formula. ;)
  Complex res;

  res.real =
    ((a.real * b.real) + (a.imaginary * b.imaginary)) /
    ((b.real * b.real) + (b.imaginary * b.imaginary));

  res.imaginary =
    ((a.imaginary * b.real) - (a.real * b.imaginary)) /
    ((b.real * b.real) + (b.imaginary * b.imaginary));

  return res;
}
