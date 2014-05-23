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

#ifndef _SOCKETUTIL_H_
#define _SOCKETUTIL_H_

#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>

// Does a DNS lookup on name "name", and returns through the output
// parameter "ret_addr" a fully-formed struct sockaddr.  The length
// of that struct sockaddr is returned through "ret_addrlen".  Also
// initializes the port to "port".
//
// On failure, returns false.  On success, returns true.
bool LookupName(char *name,
                unsigned short port,
                struct sockaddr_storage *ret_addr,
                size_t *ret_addrlen);

// Connects to the remote host and port specified by addr/addrlen.
// Returns a connected socket through the output parameter "ret_fd".
//
// On failure, returns false.  On success, returns true.
bool Connect(const struct sockaddr_storage &addr,
             const size_t &addrlen,
             int *ret_fd);

// Creates a listening socket that is bound to any local IP
// address and to the port number specified by "portnum."
//
// On success, returns a file descriptor for the created listening
// socket.  The caller is responsible for eventually close()'ing
// the socket.  Also returns through the output parameter
// "sock_family" the network address family (i.e., AF_INET or
// AF_INET6).
//
// On failure, returns -1.
int Listen(char *portnum, int *sock_family);

// A wrapper around "read" that shields the caller from dealing
// with the ugly issues of partial reads, EINTR, EAGAIN, and so
// on.
//
// Reads at most "readlen" bytes from the file descriptor fd
// into the buffer "buf".  Returns the number of bytes actually
// read.  On fatal error, returns -1.  If EOF is hit and no
// bytes have been read, returns 0.  Might read fewer bytes
// than requested.
int WrappedRead(int fd, unsigned char *buf, int readlen);

// A wrapper around "write" that shields the caller from dealing
// with the ugly issues of partial writes, EINTR, EAGAIN, and so
// on.
//
// Writes "writelen" bytes to the file descriptor fd from
// the buffer "buf".  Blocks the caller until either writelen
// bytes have been written, or an error is encountered.  Returns
// the total number of bytes written; if this number is less
// than writelen, it's because some fatal error was encountered,
// like the connection being dropped.
int WrappedWrite(int fd, unsigned char *buf, int writelen);

// Prints out information about the file descriptor "fd" and
// the struct sockaddr pointer to by "addr".  In particular,
// prints out the IPv4/IPv6 address and port number.
void PrintOut(int fd, struct sockaddr *addr, size_t addrlen);

// Attempts to do a reverse DNS lookup on to find the DNS name
// associated with the IPv4/IPv6 address inside "addr."  Will
// either print out the DNS name or an error message if the
// reverse DNS lookup fails.
void PrintReverseDNS(struct sockaddr *addr, size_t addrlen);

#endif  // _SOCKETUTIL_H_
