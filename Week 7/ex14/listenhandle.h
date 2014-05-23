/*
 * Copyright 2013 Chun-Wei Chen
 * 1267040
 * mijc0517@cs
 * 08/10/13
 */

#ifndef _LISTEN_H_
#define _LISTEN_H_

#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>

// Returns to the client the listening file descriptor; -1 if failed.
int Listen(char *portnum, int *sock_family);

// Reads the data from client and write it to stdout.
void HandleClient(int c_fd, struct sockaddr *addr, size_t addrlen,
                  int sock_family);

#endif
