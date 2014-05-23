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

// Lecture 6 exercise 2
//
// Write a program that:
//  - loops forever; in each loop, it:
//  - prompts the user to input a filename
//  - reads from stdin to receive a filename
//  - opens and reads the file, and prints its contents to stdout, in
//    the format shown on the right
//
// Since we use readline() in this program, we need to link against
// libreadline.a.  On linux, you can compile/link with this command:
//
//   gcc -Wall -g -o exercise2 exercise2.c -lreadline

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>

void HexdumpFile(unsigned char *buffer, int len);
unsigned char *ReadFile(char *fname, int *retlen);

int main(int argc, char **argv) {
  char *nextfilename;

  // Loop and read the next filename.
  while (1) {
    unsigned char *fcontent;
    int retlen;

    nextfilename = readline("Enter a filename: ");
    if (nextfilename == NULL)
      break;

    // Read in the file.
    fcontent = ReadFile(nextfilename, &retlen);
    if (fcontent == NULL) {
      fprintf(stderr, "Couldn't read file '%s': ", nextfilename);
      perror(NULL);
      exit(EXIT_FAILURE);
    }

    // Dump the content to stdout.
    HexdumpFile(fcontent, retlen);
    free(fcontent);
    free(nextfilename);
  }

  return EXIT_SUCCESS;
}

// Slurps the file into memory and returns pointer to the
// file contents with file length stored in *retlen.
// Returns NULL on error.
#define READSIZE 1000
unsigned char *ReadFile(char *fname, int *retlen) {
  unsigned char *buf = NULL;
  FILE *f;
  int readlen, count = 0;

  // Open up the file.
  f = fopen(fname, "rb");
  if (f == NULL)
    return NULL;

  // Slurp in the file, READSIZE bytes at a time.
  buf = (unsigned char *) realloc(buf, READSIZE);
  assert(buf != NULL);
  while ((readlen = fread(buf+count, 1, READSIZE, f)) > 0) {
    count += readlen;
    buf = (unsigned char *) realloc(buf, count + READSIZE);
    assert(buf != NULL);
  }

  // Did we break because of an error?
  if (ferror(f)) {
    // Yes, so clean up and arrange to return NULL.
    free(buf);
    buf = NULL;
    count = 0;
  }

  fclose(f);
  *retlen = count;
  return buf;
}

// Print contents of buffer with length buflen on stdout.
void HexdumpFile(unsigned char *buffer, int buflen) {
  int count = 0;
  int bytesleft = buflen;

  // Loop in 16 byte chunks.
  while (bytesleft > 0) {
    int nextcount = (bytesleft >= 16) ? 16 : bytesleft;
    int i;

    // print the length prefix
    fprintf(stdout, "%07x", count);

    // print the content body
    for (i = 0; i < nextcount; i++) {
      fprintf(stdout, " %02x", buffer[count + i]);
    }
    fprintf(stdout, "\n");

    count += nextcount;
    bytesleft -= nextcount;
  }
}
