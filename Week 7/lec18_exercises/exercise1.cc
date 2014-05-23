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

// Lec 18 Exercise 1
//
// Write a program that creates a listening socket, accepts
// connections from clients, and:
//  - reads a line of text from the client
//  - parses the line of text as a DNS name
//  - does a DNS lookup on the name
//  - writes back to the client the list of IP addrsses associated
//    with the DNS name 
//  - closes the connection to the client

#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <netdb.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <string>

using std::string;

// This structure stores information about a client that has
// connected to us.
typedef struct {
  int fd;
  struct sockaddr_storage caddr;
  socklen_t caddr_len;
} ClientInfo;

void Usage(char *progname);
void PrintOut(int fd, struct sockaddr *addr, size_t addrlen);
void PrintReverseDNS(struct sockaddr *addr, size_t addrlen);
string ForwardDNS(string hostname);
int  Listen(char *portnum);
void *HandleClient(void *c_info);
bool ReadLineFromSocket(int fd, string *retstr);

int main(int argc, char **argv) {
  // Expect the port number as a command line argument.
  if (argc != 2) {
    Usage(argv[0]);
  }

  // Parse the port number, or fail.
  unsigned short port = 0;
  if (sscanf(argv[1], "%hu", &port) != 1) {
    Usage(argv[0]);
  }

  int listen_fd = Listen(argv[1]);
  if (listen_fd <= 0) {
    // We failed to bind/listen to a socket.  Quit with failure.
    std::cerr << "Couldn't bind to any addresses." << std::endl;
    return EXIT_FAILURE;
  }

  // Loop forever, accepting client connections and dispatching them.
  while (1) {
    // Allocate a "ClientInfo" structure to store information about
    // the next client connection that we receive.  We'll hand this
    // structure off to a thread that we dispatch to handle the
    // client.
    ClientInfo *cinfo = new ClientInfo;
    cinfo->caddr_len = sizeof(cinfo->caddr);
    cinfo->fd = accept(listen_fd,
                       reinterpret_cast<struct sockaddr *>(&(cinfo->caddr)),
                       &(cinfo->caddr_len));
    if (cinfo->fd < 0) {
      if ((errno == EAGAIN) || (errno == EINTR)) {
        delete cinfo;
        continue;
      }
      std::cerr << "Failure on accept: " << strerror(errno) << std::endl;
      delete cinfo;
      break;
    }

    // Dispatch a thread to handle this file descriptor.
    pthread_t thr;
    assert(pthread_create(&thr, NULL, HandleClient, (void *) cinfo) == 0);
    assert(pthread_detach(thr) == 0);
  }

  // Close up shop.
  close(listen_fd);
  return EXIT_SUCCESS;
}

void Usage(char *progname) {
  std::cerr << "usage: " << progname << " port" << std::endl;
  exit(EXIT_FAILURE);
}

void PrintOut(int fd, struct sockaddr *addr, size_t addrlen) {
  std::cout << "Socket [" << fd << "] is bound to:" << std::endl;
  if (addr->sa_family == AF_INET) {
    // Print out the IPV4 address and port

    char astring[INET_ADDRSTRLEN];
    struct sockaddr_in *in4 = reinterpret_cast<struct sockaddr_in *>(addr);
    inet_ntop(AF_INET, &(in4->sin_addr), astring, INET_ADDRSTRLEN);
    std::cout << " IPv4 address " << astring;
    std::cout << " and port " << htons(in4->sin_port) << std::endl;

  } else if (addr->sa_family == AF_INET6) {
    // Print out the IPV4 address and port

    char astring[INET6_ADDRSTRLEN];
    struct sockaddr_in6 *in6 = reinterpret_cast<struct sockaddr_in6 *>(addr);
    inet_ntop(AF_INET, &(in6->sin6_addr), astring, INET6_ADDRSTRLEN);
    std::cout << " IPv6 address " << astring;
    std::cout << " and port " << htons(in6->sin6_port) << std::endl;

  } else {
    std::cout << " ???? address and port ????" << std::endl;
  }
}

void PrintReverseDNS(struct sockaddr *addr, size_t addrlen) {
  char hostname[1024];  // ought to be big enough.
  if (getnameinfo(addr, addrlen, hostname, 1024, NULL, 0, 0) != 0) {
    sprintf(hostname, "[reverse DNS failed]");
  }
  std::cout << " DNS name: " << hostname << std::endl;
}

int Listen(char *portnum) {
  // Populate the "hints" addrinfo structure for getaddrinfo().
  // ("man addrinfo")
  struct addrinfo hints;
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_UNSPEC;      // allow IPv4 or IPv6
  hints.ai_socktype = SOCK_STREAM;  // stream
  hints.ai_flags = AI_PASSIVE;      // use wildcard "INADDR_ANY"
  hints.ai_protocol = IPPROTO_TCP;  // tcp protocol
  hints.ai_canonname = NULL;
  hints.ai_addr = NULL;
  hints.ai_next = NULL;

  // Use argv[1] as the string representation of our portnumber to
  // pass in to getaddrinfo().  getaddrinfo() returns a list of
  // address structures via the output parameter "result".
  struct addrinfo *result;
  int res = getaddrinfo(NULL, portnum, &hints, &result);

  // Did addrinfo() fail?
  if (res != 0) {
    std::cerr << "getaddrinfo() failed: ";
    std::cerr << gai_strerror(res) << std::endl;
    return -1;
  }

  // Loop through the returned address structures until we are able
  // to create a socket and bind to one.  The address structures are
  // linked in a list through the "ai_next" field of result.
  int listen_fd = -1;
  for (struct addrinfo *rp = result; rp != NULL; rp = rp->ai_next) {
    listen_fd = socket(rp->ai_family,
                       rp->ai_socktype,
                       rp->ai_protocol);
    if (listen_fd == -1) {
      // Creating this socket failed.  So, loop to the next returned
      // result and try again.
      std::cerr << "socket() failed: " << strerror(errno) << std::endl;
      listen_fd = -1;
      continue;
    }

    // Configure the socket; we're setting a socket "option."  In
    // particular, we set "SO_REUSEADDR", which tells the TCP stack
    // so make the port we bind to available again as soon as we
    // exit, rather than waiting for a few tens of seconds to recycle it.
    int optval = 1;
    assert(setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR,
                      &optval, sizeof(optval)) == 0);

    // Try binding the socket to the address and port number returned
    // by getaddrinfo().
    if (bind(listen_fd, rp->ai_addr, rp->ai_addrlen) == 0) {
      // Bind worked!  Print out the information about what
      // we bound to.
      PrintOut(listen_fd, rp->ai_addr, rp->ai_addrlen);
      break;
    }

    // The bind failed.  Close the socket, then loop back around and
    // try the next address/port returned by getaddrinfo().
    close(listen_fd);
    listen_fd = -1;
  }

  // Free the structure returned by getaddrinfo().
  freeaddrinfo(result);

  // If we failed to bind, return failure.
  if (listen_fd <= 0)
    return listen_fd;

  // Success. Tell the OS that we want this to be a listening socket.
  if (listen(listen_fd, SOMAXCONN) != 0) {
    std::cerr << "Failed to mark socket as listening: ";
    std::cerr << strerror(errno) << std::endl;
    close(listen_fd);
    return -1;
  }

  return listen_fd;
}

void *HandleClient(void *c_fd) {
  ClientInfo cinfo = *((ClientInfo *) c_fd);
  delete ((ClientInfo *) c_fd);

  // Print out information about the client.
  std::cout << std::endl;
  std::cout << "New client connection" << std::endl;
  PrintOut(cinfo.fd, (sockaddr *) &(cinfo.caddr), cinfo.caddr_len);
  PrintReverseDNS((sockaddr *) &(cinfo.caddr), cinfo.caddr_len);

  // Loop, reading data and doing a DNS lookup on the content.
  while (1) {
    string nextstr;
    bool res = ReadLineFromSocket(cinfo.fd, &nextstr);
    if (!res) {
      std::cout << " [The client disconnected.]" << std::endl;
      break;
    }
    
    std::cout << " the client sent: " << nextstr << std::endl;
    string retstr = ForwardDNS(nextstr);
    std::cout << "sending: " << retstr;

    write(cinfo.fd, retstr.c_str(), retstr.size());
  }

  close(cinfo.fd);
  return NULL;
}

// Reads characters from the socket "fd" until it spots
// a newline or EOF.  Returns the read characters (minus the
// newline) through "retstr".  Returns true if something was
// read, false otherwise.  If returns false, customer should
// close the socket.
bool ReadLineFromSocket(int fd, string *retstr) {
  // We won't try to make this efficient; we'll keep appending
  // single characters to a string until we hit EOF or newline.
  // This means that C++ will be making a *ton* of string copies
  // along the way.
  string data;
  int count = 0;

  while (1) {
    unsigned char nextC;
    ssize_t res = read(fd, &nextC, 1);
    if (res == 1) {
      // Ignore '\r' characters if we see them.
      if (nextC == '\r')
        continue;

      // Stop on '\n' characters.
      if (nextC == '\n') {
        // All done!
        *retstr = data;
        return true;
      }
      // Append the character.
      data.append(1, nextC);
      count++;
      continue;
    }
    if (res == 0) {
      if (count == 0)
        return false;
      *retstr = data;
      return true;
    }
    if (res == -1) {
      if ((errno == EINTR) || (errno == EAGAIN))
        continue;
      // Unrecoverable error.
      return false;
    }
  }

  // should never get here.
  assert(0);
  return false;
}

string ForwardDNS(string hostname) {
  // Try to do a forward DNS lookup on the given hostname.
  int retval;
  struct addrinfo hints, *results, *r;
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  if ((retval = getaddrinfo(hostname.c_str(),
                            NULL,
                            &hints,
                            &results) != 0)) {
    return (string("[dns lookup of '") + hostname + "' failed.\n");
  }
  string retstr;
  for (r = results; r != NULL; r = r->ai_next) {
    std::cout << r->ai_flags << std::endl;
    std::cout << r->ai_family << std::endl;
    std::cout << r->ai_socktype << std::endl;
    std::cout << r->ai_protocol << std::endl;
    std::cout << r->ai_addrlen << std::endl;
    if (r->ai_family == AF_INET) {
      char ipstring[INET_ADDRSTRLEN];
      struct sockaddr_in *v4addr = (struct sockaddr_in *) r->ai_addr;
      std::cout << v4addr->sin_family << std::endl;
      std::cout << v4addr->sin_port << std::endl;
      inet_ntop(r->ai_family,
                &(v4addr->sin_addr),
                ipstring,
                INET_ADDRSTRLEN);
      retstr += string("  IPv4: ") + ipstring + "\n";
    } else {
      char ipstring[INET6_ADDRSTRLEN];
      struct sockaddr_in6 *v6addr = (struct sockaddr_in6 *) r->ai_addr;
      inet_ntop(r->ai_family,
                &(v6addr->sin6_addr),
                ipstring,
                INET6_ADDRSTRLEN);
      retstr += string("  IPv6: ") + ipstring + "\n";
    }
  }
  return retstr;
}
