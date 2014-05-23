/*
 * Copyright 2013 Chun-Wei Chen
 * 1267040
 * mijc0517@cs
 * 08/08/13
 */

#ifndef _CONNECT_H_
#define _CONNECT_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

// Lookup IP address.
bool LookupName(char *name,
                unsigned short port,
                struct sockaddr_storage *ret_addr,
                size_t *ret_addrlen);

// Connect to a remote host.
bool Connect(const struct sockaddr_storage &addr,
             const size_t &addrlen,
             int *ret_fd);

#endif
