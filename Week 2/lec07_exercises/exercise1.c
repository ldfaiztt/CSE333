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

// Lecture 7 exercise 1
//
// Write a program that:
// - prompts the user to input a string (use fgets())
//   - assume the string is a sequence of whitespace-separated integers
//   - e.g., "5555 1234 4 5543"
// - converts the string into an array of integers
// - converts an array of integers into an array of strings
//    - where each element of the string array is the binary representation
//      of the associated integer
// - prints out the array of strings

#include <stdio.h>    // for NULL
#include <stdlib.h>   // for malloc(), realloc(), free()
#include <assert.h>   // for assert()
#include <string.h>   // for string manipulation functions

// Reads a line of input from stdin using fgets(), or
// NULL on error.  Caller is responsible for free()'ing the
// returned string.  Does not include a newline at the
// end of the string.
char *GetNextLine(void);

// Converts the string to an array of integers, and returns
// the array and the array length.  (Array length is returned
// through the output parameter "retarraylen".)
//
// Caller is responsible for free()'ing the returned array.
//
// Returns NULL on error.
int *ToIntArray(char *string, int *retarraylen);

// Converts an integer array into an array of strings,
// where each string is the binary representation of the
// associated integer.
//
// Returns the array of strings, or NULL on error.
// Caller is responsible for free()'ing each string in
// the returned array, as well as the array itself.
char **ToBitStrArray(int *intarray, int arrlen);

int main(int argc, char **argv) {
  while (1) {
    char *nextline;
    int arraylen, i;
    int *integerarray;
    char **outstring;

    // Read the next line of input.
    nextline = GetNextLine();
    assert(nextline != NULL);

    // Convert to an integer array.
    integerarray = ToIntArray(nextline, &arraylen);
    assert(integerarray != NULL);
    free(nextline);

    // Convert to an array of strings.
    outstring = ToBitStrArray(integerarray, arraylen);
    assert(outstring != NULL);
    free(integerarray);

    // Print out, also free()'ing as we go.
    for (i = 0; i < arraylen; i++) {
      if (i == (arraylen-1))
        printf("%s\n", outstring[i]);
      else
        printf("%s ", outstring[i]);
      free(outstring[i]);
    }
    free(outstring);
  }
  // Never gets here. :)
  return EXIT_SUCCESS;
}


// It would have been easier to implement this using the C
// "getline()" function, but we were told to implement it using
// fgets(), i.e., stream reads from stdin.  Oh well!
char *GetNextLine(void) {
  char *linestr = NULL;
  int count = 0;

  // Initialize linestr to contain a NULL-terminated
  // string.  We'll grow it one character at a time
  // using realloc().  ("man realloc")
  linestr = (char *) malloc(1 * sizeof(char));
  if (linestr == NULL)
    return NULL;
  linestr[0] = '\0';

  fprintf(stdout, "Enter next array of integers:\n");
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
    if (fgets(&(linestr[count]), 2, stdin) == NULL) {
      // We hit the end of stdin. Return our string.
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

int *ToIntArray(char *string, int *retarraylen) {
  int *retarray = NULL;
  char *nexttok = NULL;
  int arrlen = 0;

  // We'll use strtok to split up the string into
  // whitespace-separated tokens.  "man strtok"
  nexttok = strtok(string, " \t");
  while (nexttok != NULL) {
    // Convert the token into an integer using sscanf.
    // "man sscanf"
    int nextint, res;
    res = sscanf(nexttok, "%d", &nextint);
    if (res == 0) {
      // bogus string (not an integer), so return failure.
      if (retarray != NULL)
        free(retarray);
      return NULL;
    }

    // Got it! realloc the array and add the integer in.
    arrlen++;
    retarray = realloc(retarray, arrlen * sizeof(int));
    if (retarray == NULL) {
      // out of memory.
      return NULL;
    }
    retarray[arrlen-1] = nextint;

    // Parse the next token and loop around.
    nexttok = strtok(NULL, " \t");
  }

  // Return our results.
  *retarraylen = arrlen;
  return retarray;
}

char **ToBitStrArray(int *intarray, int arrlen) {
  assert(arrlen != 0);

  // We know we have a valid array of integers,
  // and we know an integer is sizeof(int) bytes
  // long.  So, we know exactly how much memory
  // we need to allocate.  Allocate it all up front.
  int i;

  // Allocate the string array.
  char **stringarray = (char **) malloc(arrlen*sizeof(char *));

  if (stringarray == NULL)
    return NULL;

  // Loop through to malloc each string in the string array.
  for (i = 0; i < arrlen; i++) {
    int j, mallocsize, nextbyte;

    // need 8*sizeof(int) bytes for the bit rep, plus 1 byte for null
    mallocsize = 8 * sizeof(int) + 1;
    stringarray[i] = (char *) malloc(mallocsize * sizeof(char));
    if (stringarray[i] == NULL) {
      // out of memory.  Free everything, then return NULL.
      for (j = 0; j < i; j++)
        free(stringarray[j]);
      free(stringarray);
      return NULL;
    }

    // Do the bit-by-bit string build up.  We'll go right-to-left.
    nextbyte = intarray[i];
    for (j = 0; j < (mallocsize - 1); j++) {
      int nextbit;

      // Mask out all but the last bit of the integer.
      nextbit = nextbyte & 0x01;
      if (nextbit == 0)
        stringarray[i][mallocsize - 2 - j] = '0';
      else
        stringarray[i][mallocsize - 2 - j] = '1';

      // shift the int to the right by 1 bit
      nextbyte = nextbyte >> 1;
    }
    // Add the null terminator for this string, then loop
    // back up to do the next string in the string array.
    stringarray[i][mallocsize-1] = '\0';
  }

  // All done!
  return stringarray;
}
