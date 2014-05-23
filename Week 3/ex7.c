/*
 * Copyright 2013 Chun-Wei Chen
 * 1267040
 * mijc0517@cs
 * 07/14/13
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

/*
 * Prints the txt files in the directory.
 * dir and file cannot be NULL.
 */
void PrintDirectoryFiles(char *dir, char *file);

/*
 * Helper function to print the txt file in the directory.
 * full_file_path cannot be NULL.
 */
void PrintDirectoryFilesHelper(char *full_file_path);

/*
 * Takes a directory name as argument and prints out 
 * the content of .txt files in that directory.
 */
int main(int argc, char **argv) {
  if (argc != 2) {
    printf("The program needs a directory name as arugment.\n");
    return EXIT_FAILURE;
  }

  DIR *dir = opendir(argv[1]);
  if (dir == NULL) {
    printf("Open directory %s failed.\n", argv[1]);
    return EXIT_FAILURE;
  }

  struct dirent entry;
  struct dirent *file;
  while (1) {
    readdir_r(dir, &entry, &file);
    // no more file to read
    if (file == NULL)
      break;

    uint64_t file_name_length = strlen(file->d_name);
    // check if the file is .txt file
    if ((file_name_length >= 4) &&
        strcmp(file->d_name + (file_name_length - 4), ".txt") == 0)
      PrintDirectoryFiles(argv[1], file->d_name);
  }

  closedir(dir);
  return EXIT_SUCCESS;
}

void PrintDirectoryFiles(char *dir, char *file) {
  if (dir == NULL) {
    printf("Argument dir passed in cannot be NULL.\n");
    exit(EXIT_FAILURE);
  }

  if (file == NULL) {
    printf("Argument file passed in cannot be NULL.\n");
    exit(EXIT_FAILURE);
  }

  uint64_t path_length = strlen(dir);
  uint64_t file_length = strlen(file);

  // plus two because of / between dirctory and file and \0 at the end
  char *full_file_path = (char *) malloc(sizeof(char) *
                                         (path_length + file_length + 2));

  if (full_file_path == NULL) {
    printf("malloc failed.\n");
    exit(EXIT_FAILURE);
  }

  // store the full path of the file into full_file_path
  memcpy(full_file_path, dir, path_length);
  full_file_path[path_length] = '/';
  memcpy(full_file_path + path_length + 1, file, file_length + 1);

  // call the helper function to open and print out the file content
  PrintDirectoryFilesHelper(full_file_path);

  free(full_file_path);
}

void PrintDirectoryFilesHelper(char *full_file_path) {
  if (full_file_path == NULL) {
    printf("Argument full_file_path passed in cannot be NULL.\n");
    exit(EXIT_FAILURE);
  }

  int64_t fd = open(full_file_path, O_RDONLY);
  if (fd == -1) {
    printf("Open file %s failed.\n", full_file_path);
    exit(EXIT_FAILURE);
  }

  char buf[256];
  while (1) {
    int64_t result = read(fd, buf, 256);

    if (result == -1) {
      if (errno != EINTR) {
        printf("Read file %s failed.\n", full_file_path);
        exit(EXIT_FAILURE);
      }
      continue;
    } else if (result == 0) {
      break;
    } else {
      if (fwrite(buf, result, 1, stdout) != 1) {
        printf("Write failed.\n");
        exit(EXIT_FAILURE);
      }
    }
  }
  close(fd);
}
