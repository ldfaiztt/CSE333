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

// lec 17 exercise 1

#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <iostream>
#include <string>

// Translates the DNS name to one or more IP addresses and prints
// them out, one line per IP address.  If the DNS translation fails,
// prints nothing.
void PrintTranslation(const char *dnsname);

int main(int argc, char **argv) {
  // Read in from STDIN, one line at a time.
  std::string nextline;
  while (1) {
    std::cin >> nextline;
    if (!std::cin.good()) {
      return EXIT_FAILURE;
    }

    // Translate the next line.
    PrintTranslation(nextline.c_str());
  }
  return EXIT_SUCCESS;
}

void PrintTranslation(const char *dnsname) {
  struct addrinfo hints, *results, *r;
  int retval;

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;  // OK with IPv4 or IPv6
  hints.ai_socktype = SOCK_STREAM;
  if ((retval = getaddrinfo(dnsname, NULL, &hints, &results)) != 0) {
    return;
  }

  for (r = results; r != NULL; r = r->ai_next) {
    // Treat the IPv4 and IPv6 cases differently.
    if (r->ai_family == AF_INET) {
      char ipstring[INET_ADDRSTRLEN];
      struct sockaddr_in *v4addr = (struct sockaddr_in *) r->ai_addr;
      inet_ntop(r->ai_family,
                &(v4addr->sin_addr),
                ipstring,
                INET_ADDRSTRLEN);
      std::cout << ipstring << std::endl;
    } else {
      char ipstring[INET6_ADDRSTRLEN];
      struct sockaddr_in6 *v6addr = (struct sockaddr_in6 *) r->ai_addr;
      inet_ntop(r->ai_family,
                &(v6addr->sin6_addr),
                ipstring,
                INET6_ADDRSTRLEN);
      std::cout << ipstring << std::endl;
    }
  }
  freeaddrinfo(results);
}
