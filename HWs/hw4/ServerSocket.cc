/*
 * Copyright 2012 Steven Gribble
 *
 *  This file is part of the UW CSE 333 course project sequence
 *  (333proj).
 *
 *  333proj is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  333proj is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with 333proj.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>       // for snprintf()
#include <unistd.h>      // for close(), fcntl()
#include <sys/types.h>   // for socket(), getaddrinfo(), etc.
#include <sys/socket.h>  // for socket(), getaddrinfo(), etc.
#include <arpa/inet.h>   // for inet_ntop()
#include <netdb.h>       // for getaddrinfo()
#include <errno.h>       // for errno, used by strerror()
#include <string.h>      // for memset, strerror()
#include <iostream>      // for std::cerr, etc.

#include "./ServerSocket.h"

extern "C" {
  #include "./libhw1/Assert333.h"
}

namespace hw4 {

ServerSocket::ServerSocket(uint16_t port) {
  port_ = port;
  listen_sock_fd_ = -1;
}

ServerSocket::~ServerSocket() {
  // Close the listening socket if it's not zero.  The rest of this
  // class will make sure to zero out the socket if it is closed
  // elsewhere.
  if (listen_sock_fd_ != -1)
    close(listen_sock_fd_);
  listen_sock_fd_ = -1;
}

bool ServerSocket::BindAndListen(int ai_family, int *listen_fd) {
  // Use "getaddrinfo," "socket," "bind," and "listen" to
  // create a listening socket on port port_.  Return the
  // listening socket through the output parameter "listen_fd".

  // MISSING:

  // create the "hints" data structure for getaddrinfo()
  struct addrinfo hints;

  // zero out the "hints"
  memset(&hints, 0, sizeof(struct addrinfo));

  // check if ai_family passed in is valid
  if (ai_family != AF_INET && ai_family != AF_INET6 && ai_family != AF_UNSPEC)
    return false;

  // fill in the fields of "hints" for getaddrinfo()
  hints.ai_family = ai_family;
  hints.ai_socktype = SOCK_STREAM;  // stream
  hints.ai_flags = AI_PASSIVE;  // use wildcard "INADDR_ANY"
  hints.ai_protocol = IPPROTO_TCP;  // tcp protocol
  hints.ai_canonname = NULL;
  hints.ai_addr = NULL;
  hints.ai_next = NULL;

  // convert port_ to C-string
  struct addrinfo *result;
  std::string port = std::to_string(port_);

  // get a list of addres structures via "result"
  int res = getaddrinfo(NULL, port.c_str(), &hints, &result);

  if (res != 0)
    return false;  // getaddrinfo() failed

  int ret_fd = -1;
  for (struct addrinfo *rp = result; rp != NULL; rp = rp->ai_next) {
    ret_fd = socket(rp->ai_family,
                    rp->ai_socktype,
                    rp->ai_protocol);

    if (ret_fd == -1)
      continue;  // create this socket failed, try the next returned result

    // Configure the socket; we're setting a socket "option."  In
    // particular, we set "SO_REUSEADDR", which tells the TCP stack
    // so make the port we bind to available again as soon as we
    // exit, rather than waiting for a few tens of seconds to recycle it.
    int optval = 1;
    Assert333(setsockopt(ret_fd, SOL_SOCKET, SO_REUSEADDR,
                         &optval, sizeof(optval)) == 0);

    // Try binding the socket to the address and port number returned
    // by getaddrinfo().
    if (bind(ret_fd, rp->ai_addr, rp->ai_addrlen) == 0) {
      // Bind worked!
      sock_family_ = rp->ai_family;
      break;
    }

    // The bind failed.  Close the socket, then loop back around and
    // try the next address/port returned by getaddrinfo().
    close(ret_fd);
    ret_fd = -1;
  }

  // Free the structure returned by getaddrinfo().
  freeaddrinfo(result);

  // If we failed to bind, return failure.
  if (ret_fd == -1)
    return false;

  // Success. Tell the OS that we want this to be a listening socket.
  if (listen(ret_fd, SOMAXCONN) != 0) {
    // failed to mark socket as listening
    close(ret_fd);
    return false;
  }

  // store the listening socket file descriptor in field and output parameter
  listen_sock_fd_ = ret_fd;
  *listen_fd = ret_fd;

  return true;
}

bool ServerSocket::Accept(int *accepted_fd,
                          std::string *client_addr,
                          uint16_t *client_port,
                          std::string *client_dnsname,
                          std::string *server_addr,
                          std::string *server_dnsname) {
  // Accept a new connection on the listening socket listen_sock_fd_.
  // (Block until a new connection arrives.)  Return the newly accepted
  // socket, as well as information about both ends of the new connection,
  // through the various output parameters.

  // MISSING:

  struct sockaddr_storage caddr;
  socklen_t caddr_len = sizeof(caddr);
  struct sockaddr *addr = reinterpret_cast<struct sockaddr *>(&caddr);
  int client_fd = -1;
  while (1) {
    client_fd = accept(listen_sock_fd_,
                       addr,
                       &caddr_len);

    if (client_fd < 0) {
      if ((errno == EAGAIN) || (errno == EINTR))
        continue;

      return false;
    }
    break;
  }

  if (client_fd < 0)
    return false;

  // store client file desciptor in output parameter
  *accepted_fd = client_fd;

  // get client IP address/port and store them in output parameters
  if (addr->sa_family == AF_INET) {
    // client uses IPv4 address
    char astring[INET_ADDRSTRLEN];
    struct sockaddr_in *in4 = reinterpret_cast<struct sockaddr_in *>(addr);
    inet_ntop(AF_INET, &(in4->sin_addr), astring, INET_ADDRSTRLEN);

    *client_addr = std::string(astring);
    *client_port = htons(in4->sin_port);
  } else {
    // client uses IPv6 address
    char astring[INET6_ADDRSTRLEN];
    struct sockaddr_in6 *in6 = reinterpret_cast<struct sockaddr_in6 *>(addr);
    inet_ntop(AF_INET6, &(in6->sin6_addr), astring, INET6_ADDRSTRLEN);

    *client_addr = std::string(astring);
    *client_port = htons(in6->sin6_port);
  }

  // get client DNS name and store it in output parameter
  char hostname[1024];
  Assert333(getnameinfo(addr, caddr_len, hostname, 1024, NULL, 0, 0) == 0);
  *client_dnsname = std::string(hostname);

  // get the client IP address/DNS name and store them un output parameters
  char hname[1024];
  hname[0] = '\0';
  if (sock_family_ == AF_INET) {
    // server use IPv4 address
    struct sockaddr_in srvr;
    socklen_t srvrlen = sizeof(srvr);
    char addrbuf[INET_ADDRSTRLEN];
    getsockname(client_fd, (struct sockaddr *) &srvr, &srvrlen);
    inet_ntop(AF_INET, &srvr.sin_addr, addrbuf, INET_ADDRSTRLEN);
    getnameinfo((const struct sockaddr *) &srvr,
                srvrlen, hname, 1024, NULL, 0, 0);

    *server_addr = std::string(addrbuf);
    *server_dnsname = std::string(hname);
  } else {
    // server uses IPv6 address
    struct sockaddr_in6 srvr;
    socklen_t srvrlen = sizeof(srvr);
    char addrbuf[INET6_ADDRSTRLEN];
    getsockname(client_fd, (struct sockaddr *) &srvr, &srvrlen);
    inet_ntop(AF_INET6, &srvr.sin6_addr, addrbuf, INET6_ADDRSTRLEN);
    getnameinfo((const struct sockaddr *) &srvr,
                srvrlen, hname, 1024, NULL, 0, 0);

    *server_addr = std::string(addrbuf);
    *server_dnsname = std::string(hname);
  }

  return true;
}

}  // namespace hw4
