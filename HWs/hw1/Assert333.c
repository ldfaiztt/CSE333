/*
 * Copyright 2012 Steven Gribble
 *
 *  This file is part of the UW CSE333 project sequence (333proj).
 *
 *  333proj is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published
 *  by the Free Software Foundation, either version 3 of the License,
 *  or (at your option) any later version.
 *
 *  333proj is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with 333proj. If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./Assert333.h"

void AssertionFailure(const char *exp, const char *file,
                      const char *baseFile, int line) {
  if (!strcmp(file, baseFile)) {
    fprintf(stderr,
            "Assert333(%s) failed in file %s, line %d\n", exp, file, line);
  } else {
    fprintf(stderr,
            "Assert333(%s) failed in file %s (included from %s), line %d\n",
            exp, file, baseFile, line);
  }
  exit(EXIT_FAILURE);
}
