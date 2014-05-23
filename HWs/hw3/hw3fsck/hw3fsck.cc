/*
 * Copyright 2011 Steven Gribble
 *
 *  This file is part of the UW CSE 333 course project sequence
 *  (333proj).
 *
 *  333proj is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  333proj is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with 333proj.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <cstdlib>   // for EXIT_SUCCESS, EXIT_FAILURE, free().
#include <iostream>  // for std::cout, std::cerr, etc.

#include "./FileIndexChecker.h"

using namespace std;
using namespace hw3;

static void Usage(char *progname) {
  cerr << "Usage: " << progname << " indexfiles" << std::endl;
  exit(EXIT_FAILURE);
}

int main(int argc, char **argv) {
  if (argc < 2) Usage(argv[0]);

  // Checking starts here.
  FileIndexChecker fic(argv[1]);
  return EXIT_SUCCESS;
}
