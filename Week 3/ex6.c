/*
 * Copyright 2013 Chun-Wei Chen
 * 1267040
 * mijc0517@cs
 * 07/08/13
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char **argv) {
  // check if the user provide exactly one argument
  if (argc != 2) {
    printf("The program needs a file name as arugment.\n");
    return EXIT_FAILURE;
  }

  FILE *file;
  int64_t file_size;

  if ((file = fopen(argv[1], "rb")) == NULL) {
    printf("fopen failed: %s\n", argv[1]);
    return EXIT_FAILURE;
  }

  if ((fseek(file, 0L, SEEK_END)) != 0) {
    printf("fseek failed: %s\n", argv[1]);
    return EXIT_FAILURE;
  }

  if ((file_size = ftell(file)) == -1) {
    printf("ftell failed: %s\n", argv[1]);
    return EXIT_FAILURE;
  }

  char prev_char;

  // print the file content backwards, byte-by-byte
  for (int64_t i = file_size - 1; i >= 0; i--) {
    if (fseek(file, i, SEEK_SET) != 0) {
      printf("fseek failed: %s\n, offset: %ld\n", argv[1], i);
      return EXIT_FAILURE;
    }

    if ((fread((void *) &prev_char, 1, 1, file)) != 1) {
      printf("fread failed: %s\n, offset: %ld\n", argv[1], i);
      return EXIT_FAILURE;
    }

    printf("%c", prev_char);
  }

  fclose(file);
  return EXIT_SUCCESS;
}
