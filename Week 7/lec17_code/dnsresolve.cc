#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <iostream>

void Usage(char *progname) {
  std::cerr << "usage: " << progname << " hostname" << std::endl;
  exit(EXIT_FAILURE);
}

int main(int argc, char **argv) {
  int retval;
  struct addrinfo hints, *results, *r;

  if (argc != 2) {
    Usage(argv[0]);
  }

  // Zero out the hints data structure using memset.
  memset(&hints, 0, sizeof(hints));

  // Indicate we're happy with both AF_INET or AF_INET6 addresses.
  hints.ai_family = AF_UNSPEC;

  // Constrain the answers to SOCK_STREAM addresses.  [You can use
  // the ai_addr field in a result as an argument to connect() or
  // bind(), so if you leave ai_socketype as 0 for unconstrained,
  // you'll get multiple results for each IP address found, one for
  // each socket type.]
  hints.ai_socktype = SOCK_STREAM;

  // Do the lookup by invoking getaddrinfo().  This could take some
  // time, since the resolution may require communicating with one
  // or more DNS resolvers out on the Internet.
  if ((retval = getaddrinfo(argv[1], NULL, &hints, &results)) != 0) {
    std::cerr << "getaddrinfo failed: ";
    std::cerr << gai_strerror(retval) << std::endl;
    return EXIT_FAILURE;
  }

  // Print the results!
  std::cout << "Here are the IP addresses found for '" << argv[1];
  std::cout << "'" << std::endl;
  for (r = results; r != NULL; r = r->ai_next) {
    // Treat the IPv4 and IPv6 cases differently.
    if (r->ai_family == AF_INET) {
      char ipstring[INET_ADDRSTRLEN];
      struct sockaddr_in *v4addr = (struct sockaddr_in *) r->ai_addr;
      inet_ntop(r->ai_family,
                &(v4addr->sin_addr),
                ipstring,
                INET_ADDRSTRLEN);
      std::cout << "  IPv4: " << ipstring << std::endl;
    } else if (r->ai_family == AF_INET6) {
      char ipstring[INET6_ADDRSTRLEN];
      struct sockaddr_in6 *v6addr = (struct sockaddr_in6 *) r->ai_addr;
      inet_ntop(r->ai_family,
                &(v6addr->sin6_addr),
                ipstring,
                INET6_ADDRSTRLEN);
      std::cout << "  IPv6: " << ipstring << std::endl;
    } else {
      std::cout << "  unknown address family " << r->ai_family << std::endl;
    }
  }

  // Clean up.
  freeaddrinfo(results);
  return 0;
}
