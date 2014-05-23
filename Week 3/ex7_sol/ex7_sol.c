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

#include <dirent.h>   // for directory ops
#include <errno.h>    // for errno
#include <fcntl.h>    // for open / close
#include <stdio.h>    // for printf
#include <stdlib.h>   // for EXIT_SUCCESS, malloc, free
#include <string.h>
#include <unistd.h>   // for read / write

// Print out usage and exit.
void Usage(void) {
  fprintf(stderr, "usage: ex7 directory\n");
  exit(EXIT_FAILURE);
}

// Together, the following read/print out the directory/file combination.
void ReadAndPrint(char *directory, char *file);
void PrintFile(char *merged_filename);

int main(int argc, char **argv) {
  // Make sure that the user passed us a directory that we can open.
  if (argc != 2)
    Usage();
  DIR *d = opendir(argv[1]);
  if (d == NULL)
    Usage();

  // Iterate through, reading filenames.
  while (1) {
    struct dirent *next = readdir(d);
    if (next == NULL)
      break;

    // Check to see if the filename ends in .txt.
    int namlen = strlen(next->d_name);
    if ((namlen >= 4) &&
        (strcmp(next->d_name + (namlen - 4), ".txt") == 0)) {
      // Yes, so read / print it.
      ReadAndPrint(argv[1], next->d_name);
    }
  }

  // Clean up and exit
  closedir(d);
  return EXIT_SUCCESS;  // EXIT_SUCCESS defined in stdlib.h.
}

// Copy named file in named directory to stdout
void ReadAndPrint(char *directory, char *file) {
  // Concatenate directory and file name.
  int dlen = strlen(directory);
  int flen = strlen(file);
  char *merged_filename = (char *) malloc(sizeof(char) * (dlen + flen + 2));
  if (merged_filename == NULL) {
    fprintf(stderr, "Error on malloc.\n");
    Usage();
  }
  snprintf(merged_filename, dlen + flen + 2, "%s/%s", directory, file);

  // Print the file content.
  PrintFile(merged_filename);

  // All done!
  free(merged_filename);
}

// Copy file whose full pathname is merged_filename to stdout
void PrintFile(char *merged_filename) {
  // Open up the file.
  int fd = open(merged_filename, O_RDONLY);
  if (fd == -1) {
    perror("couldn't open file");
    Usage();
  }

  // Loop through, reading the file 1024 byte
  // chunks at a time.
  char buf[1024];
  while (1) {
    int res = read(fd, buf, 1024);
    if (res == 0) {
      // EOF;
      break;
    } else if ((res == -1) && (errno != EINTR)) {
      // Some kind of error.
      perror("read error.");
      Usage();
    } else {
      // Print out what we read.
      if (fwrite(buf, res, 1, stdout) != 1) {
        fprintf(stderr, "fwrite failed\n");
        Usage();
      }
    }
  }
  close(fd);
}
