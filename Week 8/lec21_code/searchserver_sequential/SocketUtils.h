/*
 * Copyright 2012 Steven Gribble.  This program is part of the cse333
 * course sequence.
 */

#ifndef _SEARCHSERVER_SOCKETUTILS_H_
#define _SEARCHSERVER_SOCKETUTILS_H_

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

// Prints out information about the file descriptor "fd" and
// the struct sockaddr pointer to by "addr".  In particular,
// prints out the IPv4/IPv6 address and port number.
void PrintOut(int fd, struct sockaddr *addr, size_t addrlen);

// Attempts to do a reverse DNS lookup on to find the DNS name
// associated with the IPv4/IPv6 address inside "addr."  Will
// either print out the DNS name or an error message if the
// reverse DNS lookup fails.
void PrintReverseDNS(struct sockaddr *addr, size_t addrlen);

// Prints out information about the file descriptor "client_fd"
// and the server-side address information it is bound to.
// In particular, prints out the IPv4/IPv6 address and port
// number that the client connected to on the server.
void PrintServerSide(int client_fd, int sock_family);

// A wrapper around write() that shields the caller from the
// ugly details of partial writes, EINTR, and so on.
//
// Writes "writelen" bytes to "fd" from "buf".  Blocks the
// caller until either writelen bytes have been written or
// an error is encountered.  Returns the total number of
// bytes written; if this number is less than writelen,
// then an unrecoverable error happened.
unsigned int WrappedWrite(int fd, unsigned char *buf, unsigned int writelen);

#endif  // _SEARCHSERVER_SOCKETUTILS_H_
