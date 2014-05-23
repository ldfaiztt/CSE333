/*
 * Copyright 2012 Steven Gribble, Hal Perkins
 *
 *  This file is part of the UW CSE 333 course project exercises.
 *
 *  This is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This software is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

/* IntPair.h
 * CSE 333 exercise 9 sample solution.
 */

#ifndef _INTPAIR_H_
#define _INTPAIR_H_

// An IntPair is a class that represents a pair of integers.  The
// class offers an accessor, a setter, and a "PrintToStdout" function.
class IntPair {
 public:
  // Create a new IntPair, setting the pair to be "a" and "b".
  IntPair(int a, int b);

  // Get the values of a and b; note the use of output parameters.
  void Get(int *a, int *b);

  // Set the values of a and b.
  void Set(int a, int b);

 private:
  // variables storing the state of the IntPair object
  int a_, b_;
};

#endif  // _INTPAIR_H_
