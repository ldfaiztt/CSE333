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

// Lecture 2 exercise 2:
//
// Write a function that:
//  - accepts a function pointer and an integer as an argument
//  - invokes the pointed-to function, with the integer as its argument

#include <stdio.h>     // needed for the definition of NULL, printf
#include <assert.h>    // needed for the definition of assert()


// The C syntax for function pointers is pretty confusing.
// Read the manual (CARM); I've also found this web page
// to be pretty helpful:
//
//   http://www.newty.de/fpt/index.html
//
void InvokeFunction(void (*f)(int), int arg) {
  assert(f != NULL);
  f(arg);
}


// Here's some code to test our function
void FirstFunction(int a) {
  printf("In FirstFunction with argument '%d'\n", a);
}

void SecondFunction(int b) {
  printf("In SecondFunction with argument '%d'\n", b);
}

void ThirdFunction(int c) {
  printf("In ThirdFunction with argument '%d'\n", c);
}

int main(int argc, char **argv) {
  void (*g)(int);

  InvokeFunction(&FirstFunction, 5);
  InvokeFunction(&SecondFunction, 6);

  g = &ThirdFunction;
  InvokeFunction(g, 7);
  return 0;
}
