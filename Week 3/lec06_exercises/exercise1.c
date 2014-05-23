/*
 * Copyright 2011, 2013 Steven Gribble, Hal Perkins
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

// Lecture 6 exercise 1
//
//
// Write a program that:
//  - uses argc/argv to receive the name of a text file
//  - reads the contents of the file a line at a time
//  - parses each line, converting text into a uint32_t
//  - builds an array of the parsed uint32_t’s
//  - sorts the array
//  - prints the sorted array to stdout
// hints:  use “man” to read about getline, sscanf, realloc, and qsort

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <errno.h>

// Read a line of input from stdin using fgets() and return a new
// heap-allocated string containing the line, or NULL on error.
// Caller is responsible for free()'ing the returned string.  Does not
// include a newline at the end of the string.
char *GetNextLine(FILE *f);

// Read integers from file f and return a pointer to a new
// heap-allocated array containing the data.  Store the number of
// integers read (= length of the array) in arrlen.
int *ReadIntArray(FILE *f, int *arrlen);

// Compare integers *el1 and *el2.  Return -1, 0, or +1 if *el1<*el2,
// *el1==*el2, or *el1>*el2, respectively.
// (Intended as a compare function for qsort.)
int IntComparator(const void *el1, const void *el2);

void Usage(void) {
  fprintf(stderr, "usage: ./exercise1 filename\n");
  exit(EXIT_FAILURE);
}

int main(int argc, char **argv) {
  FILE *f;
  int *array, arraylen;

  if (argc != 2)
    Usage();

  f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "Couldn't open '%s':", argv[1]);
    perror(NULL);
    Usage();
  }

  array = ReadIntArray(f, &arraylen);
  if (array == NULL) {
    fprintf(stderr, "File '%s' doesn't contain integers\n", argv[1]);
    exit(EXIT_FAILURE);
  }

  qsort(array, arraylen, sizeof(int), &IntComparator);

  {
    int i;

    for (i = 0; i < arraylen; i++) {
      printf("%d\n", array[i]);
    }
  }

  fclose(f);
  free(array);
  return EXIT_SUCCESS;
}

int *ReadIntArray(FILE *f, int *arrlen) {
  int *array = NULL, len = 0;

  while (1) {
    char *nextline;
    int nextint, res;

    // Read the next line of input.
    nextline = GetNextLine(f);
    if (nextline == NULL) {
      // EOF
      break;
    }

    // Convert to an integer.
    res = sscanf(nextline, "%d", &nextint);
    if (res == 0) {
      // bogus string -- not an integer.  exit with failure.
      fprintf(stderr, "file doesn't contain integers; quitting.\n");
      exit(EXIT_FAILURE);
    }

    // Grow the integer array.
    array = (int *) realloc(array, (len + 1) * sizeof(int));
    array[len] = nextint;
    len++;
    free(nextline);
  }

  *arrlen = len;
  return array;
}


// We re-use and modify the GetNextLine() function from
// lecture 7 exercise 1.
char *GetNextLine(FILE *f) {
  char *linestr = NULL;
  int count = 0;

  // Initialize linestr to contain a NULL-terminated
  // string.  We'll grow it one character at a time
  // using realloc().  ("man realloc")
  linestr = (char *) malloc(1 * sizeof(char));
  if (linestr == NULL)
    return NULL;
  linestr[0] = '\0';

  while ( 1 ) {
    // Allocate space for the next character + NULL. Yes, this
    // is not the most elegant use of realloc(), but it gets the
    // job done. ;)
    linestr = realloc(linestr, count+2);
    if (linestr == NULL) {
      free(linestr);
      return NULL;
    }

    // Read in the next character.  Note fgets reads (size-1)
    // characters and adds a '\0', so we need size=2.
    if (fgets(&(linestr[count]), 2, f) == NULL) {
      // We hit the end of file. Return our string, or null
      // if we didn't read anything.
      if (count == 0) {
        free(linestr);
        return NULL;
      }
      return linestr;
    }
    if (linestr[count] == '\n') {
      // We hit the end of a line.  Return our string, but overwrite
      // the newline with '\0'.
      linestr[count] = '\0';
      return linestr;
    }
    // fall through to next loop.
    count++;
  }
}

int IntComparator(const void *el1, const void *el2) {
  int *int1ptr, *int2ptr;

  int1ptr = (int *) el1;
  int2ptr = (int *) el2;

  if (*int1ptr > *int2ptr)
    return 1;
  if (*int1ptr < *int2ptr)
    return -1;
  return 0;
}
