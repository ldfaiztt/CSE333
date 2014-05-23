/*
 * Copyright 2012, 2013 Steven Gribble, Hal Perkins
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

#include <stdio.h>    // for printf, etc.
#include <stdlib.h>   // for EXIT_SUCCESS, malloc, free

// Print usage message and exit
void Usage(void) {
  fprintf(stderr, "usage: ex6.c filename\n");
  exit(EXIT_FAILURE);
}

int main(int argc, char **argv) {
  // Open the file given as program argument.  Exit if we don't have
  // exactly one argument or if we cannot open the file for reading.
  if (argc != 2)
    Usage();
  FILE *f = fopen(argv[1], "rb");;
  if (f == NULL)
    Usage();

  // Get the size of the file.
  long fsize;
  if (fseek(f, 0, SEEK_END) != 0)
    Usage();
  fsize = ftell(f);
  if (fsize == -1)
    Usage();

  // Iterate through the file byte-by-byte in reverse order
  // and print the bytes to stdout.
  for (long offset = fsize-1; offset >= 0; offset--) {
    char nextc;
    if (fseek(f, offset, SEEK_SET) != 0)
      Usage();
    if (fread((void *) &nextc, sizeof(char), 1, f) != sizeof(char)) {
      Usage();
    }
    printf("%c", nextc);
  }

  fclose(f);
  return EXIT_SUCCESS;
}
