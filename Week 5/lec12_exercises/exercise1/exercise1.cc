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

// lec 12 exercise 1

#include <unistd.h>
#include <cstdlib>
#include <iostream>

#include "./Histogram.h"
#include "./GetWord.h"

void Usage(char *progname) {
  std::cerr << "Usage: " << progname << " textfile" << std::endl;
  exit(EXIT_FAILURE);
}

int main(int argc, char **argv) {
  if (argc != 2)
    Usage(argv[0]);

  GetWord gw(argv[1]);
  Histogram h;

  while (1) {
    string nextword = gw.GetNextWord();
    if (nextword == "")
      break;
    h.AddWord(nextword);
  }

  std::cout << h;
  return EXIT_SUCCESS;
}
