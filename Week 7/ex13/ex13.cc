/*
 * Copyright 2013 Chun-Wei Chen
 * 1267040
 * mijc0517@cs
 * 08/10/13
 */

#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "./connect.h"

void Usage(char *progname);

// bool WriteToServer(char[] &buf, int socket_fd, int byte_to_write);

int main(int argc, char **argv) {
  if (argc != 4)
    Usage(argv[0]);

  unsigned short port = 0;
  if (sscanf(argv[2], "%hu", &port) != 1)
    Usage(argv[0]);

  // lookup IP address
  struct sockaddr_storage addr;
  size_t addrlen;
  if (!LookupName(argv[1], port, &addr, &addrlen)) {
    std::cerr << "LookupName() " << argv[1] << " failed." << std::endl;
    Usage(argv[0]);
  }

  // connect to the remote host
  int socket_fd;
  if (!Connect(addr, addrlen, &socket_fd)) {
    std::cerr << "Connect() " << argv[1] << " failed." << std::endl;
    Usage(argv[0]);
  }

  // get a file descriptor for local file
  int file_fd = open(argv[3], O_RDONLY);
  if (file_fd == -1) {
    std::cerr << "Open() " << argv[3] << " failed." << std::endl;
    Usage(argv[0]);
  }

  // read bytes from the local file
  char readbuf[1024];
  int byte_to_write, res;
  while (1) {
    byte_to_write = read(file_fd, readbuf, 1023);
    if (byte_to_write == 0) {
      // break out of the loop if no more byte to read (i.e. reach end-of-file)
      break;
    } else if (byte_to_write == -1) {
      // continue reading file if EINTR is set; terminate the process otherwise
      if (errno == EINTR)
        continue;
      std::cerr << "File read failure: " << strerror(errno) << std::endl;
      close(file_fd);
      close(socket_fd);
      return EXIT_FAILURE;
    } else {
      readbuf[byte_to_write] = '\0';
      while (byte_to_write != 0) {
        res = write(socket_fd, readbuf, byte_to_write);
        if (res == 0) {
          std::cerr << "Socket closed prematurely." << std::endl;
          close(file_fd);
          close(socket_fd);
          return EXIT_FAILURE;
        } else if (res == -1) {
          // continue writing to server if EINTR is set;
          // terminate the process otherwise
          if (errno == EINTR)
            continue;
          std::cerr << "Socket write failure: " << strerror(errno) << std::endl;
          return EXIT_FAILURE;
        }
        byte_to_write -= res;
      }
    }
  }

  // clean up
  close(socket_fd);
  close(file_fd);
  return EXIT_SUCCESS;
}

void Usage(char *progname) {
  std::cerr << "usage: " << progname << " hostname port filename" << std::endl;
  exit(EXIT_FAILURE);
}
