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

/* IntPair.cc
 * CSE 333 exercise 9 sample solution.
 */

#include "./IntPair.h"

#include <iostream>

IntPair::IntPair(int a, int b) {
  a_ = a;
  b_ = b;
}

void IntPair::Get(int *a, int *b) {
  *a = a_;
  *b = b_;
}

void IntPair::Set(int a, int b) {
  a_ = a;
  b_ = b;
}
