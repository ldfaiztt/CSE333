/*
 * Copyright 2012 Steven Gribble.  This program is part of the cse333
 * course sequence.
 */

#include <assert.h>
#include <errno.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <list>
#include <sstream>
#include <string>

#include "./libhw3/QueryProcessor.h"
#include "./SocketLineReader.h"
#include "./SocketUtils.h"

// Prints out an error message describing how to use the program
// and then calls exit(EXIT_FAILURE).
void Usage(char *progname);

// Process queries arriving over the client_fd.
bool HandleClient(int c_fd, struct sockaddr *addr, socklen_t addrlen,
                  int sock_family, hw3::QueryProcessor *cp);

int main(int argc, char **argv) {
  // We expect at least a portnumber and one index file as arguments.
  if (argc < 3) {
    Usage(argv[0]);
  }

  // Create a queryprocessor, validating the indices.
  std::list<std::string> indexlist;
  for (int i = 2; i < argc; i++) {
    indexlist.push_back(argv[i]);
  }
  hw3::QueryProcessor qp(indexlist, true);

  // Create the listening socket on port argv[1].
  int listen_addr_family;
  int listen_fd = Listen(argv[1], &listen_addr_family);
  if (listen_fd == -1) {
    // We failed to bind/listen to the socket.  Quit with failure.
    std::cerr << "Couldn't bind/listen to any addresses." << std::endl;
    return EXIT_FAILURE;
  }

  // Loop forever, accepting a connection from a client and processing
  // queries arriving over it.
  while (1) {
    struct sockaddr_storage caddr;
    socklen_t caddr_len = sizeof(caddr);
    int client_fd = accept(listen_fd,
                           reinterpret_cast<struct sockaddr *>(&caddr),
                           &caddr_len);
    if (client_fd < 0) {
      // Check for "try again" vs. a real error.
      if ((errno == EAGAIN) || (errno == EINTR))
        continue;
      std::cerr << "Failure on accept: " << strerror(errno) << std::endl;
      break;
    }

    // Do the double-fork here.
    pid_t pid = fork();
    if (pid > 0) {
      // I'm the parent, pid is the child.  Wait for the child to exit().
      while (1) {
        int stat_loc;
        pid_t res = wait(&stat_loc);
        if ((res == -1) && (errno == EINTR))
          continue;
        if (res == -1) {
          std::cerr << "main process failed on wait(): ";
          std::cerr << strerror(errno) << std::endl;
          exit(EXIT_FAILURE);
        }
        // The child exited and our wait succeeded.  Break back
        // out to the main accept loop after closing the client fd.
        assert(res == pid);
        close(client_fd);
        break;
      }
    } else if (pid == 0) {
      // I'm the child. Fork a grandchild and exit.
      pid = fork();
      if (pid > 0) {
        // I'm the child.  Exit!
        exit(EXIT_SUCCESS);
      } else if (pid == 0) {
        // I'm the grandchild.  Handle the client connection.
        HandleClient(client_fd,
                     reinterpret_cast<struct sockaddr *>(&caddr),
                     caddr_len,
                     listen_addr_family,
                     &qp);

        // Break out of the main while loop when I'm done with
        // this client, so that the grandchild exits.
        break;
      } else {
        // Error in child's fork.
        std::cerr << "child process coudln't fork(): ";
        std::cerr << strerror(errno) << std::endl;
        exit(EXIT_FAILURE);
      }
    } else {
      // error in parent's fork.
      std::cerr << "main process couldn't fork(): ";
      std::cerr << strerror(errno) << std::endl;
      exit(EXIT_FAILURE);
    }
  }

  // Clean up and exit.
  close(listen_fd);
  return EXIT_SUCCESS;
}

void Usage(char *progname) {
  std::cerr << "Usage: " << progname << " portnumber index+"
            << std::endl;
  exit(EXIT_FAILURE);
}

bool HandleClient(int c_fd, struct sockaddr *addr, socklen_t addrlen,
                  int sock_family, hw3::QueryProcessor *qp) {
  bool terminate = false;

  // Print out information about the client.
  std::cout << std::endl;
  std::cout << "New client connection" << std::endl;
  PrintOut(c_fd, addr, addrlen);
  PrintReverseDNS(addr, addrlen);
  PrintServerSide(c_fd, sock_family);

  // Loop, reading queries and writing query results, until
  // error or client disconnects.
  SocketLineReader slr(c_fd);
  while (1) {
    // Get next "\n" terminated line from the client socket
    std::string line;
    if (!slr.GetNextLine(&line))
      break;

    // Split the line into words
    std::vector<std::string> words = slr.SplitIntoWords(line);
    if (words.size() == 0)
      continue;

    // See if our magic "break" word is spotted.
    if (words[0].compare("secretbreakword") == 0) {
      terminate = true;
      break;
    }

    // Process the query against the words
    std::vector<hw3::QueryProcessor::QueryResult> results =
      qp->ProcessQuery(words);

    // Build up a query result string
    std::stringstream ret;
    ret << "Results:\r\n";
    for (const hw3::QueryProcessor::QueryResult &res : results) {
      ret << " " << res.document_name << " (" << res.rank << ")";
      ret << "\r\n";
    }
    std::string retstr = ret.str();
    int retlen = retstr.size();

    // Write the query result string over the client socket
    int res = WrappedWrite(c_fd, (unsigned char *) retstr.c_str(), retlen);
    if (res != retlen)
      break;
  }

  // Clean up shop.
  std::cout << "Closing client [" << c_fd << "]" << std::endl;
  close(c_fd);
  return terminate;
}
