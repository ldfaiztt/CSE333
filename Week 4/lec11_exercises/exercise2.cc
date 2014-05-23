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

// lec 11 exercise 2
//
// Write a C++ class that:
// - is given the name of a file as a constructor argument
// - has a “GetNextWord( )” method that returns the next whitespace or
//   newline-separate word from the file as a copy of a “string”
//   object, or an empty string once you hit EOF.
// - has a destructor that cleans up anything that needs cleaning up

#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include "GetWord.h"

void Usage(char *name) {
  std::cout << "Usage: " << name << " filename" << std::endl;
  exit(EXIT_FAILURE);
}

int main(int argc, char **argv) {
  if (argc != 2) {
    Usage(argv[0]);
  }

  GetWord gw(argv[1]);

  while (1) {
    string next = gw.GetNextWord();
    if (next == "")
      break;
    std::cout << next << std::endl;
  }

  return EXIT_SUCCESS;
}
