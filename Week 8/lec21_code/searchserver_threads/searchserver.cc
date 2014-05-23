/*
 * Copyright 2012 Steven Gribble.  This program is part of the cse333
 * course sequence.
 */

#include <assert.h>
#include <errno.h>
#include <netinet/in.h>
#include <pthread.h>
#include <string.h>
#include <sys/types.h>
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

// When we spawn a new thread, we want to pass it a bunch of arguments
// to get its work done.  But, pthread_create only allows us to pass a
// single (void *) as an argument.  So, we'll dynamically allocate one
// of these "thr_arg" structures, fill it in with all the arguments we
// want to pass in, and pass a pointer to the structure cast to a
// (void *).
typedef struct thr_arg_st {
  int c_fd;
  struct sockaddr_storage addr;
  socklen_t addrlen;
  int sock_family;
  std::list<std::string> indexlist;
} thr_arg;

// This function is where newly spawned threads begin their life.
// We will arrange to pass a (thr_arg *) as the "arg" pointer.
void *thr_fn(void *arg);

// Process queries arriving over the client_fd.
bool HandleClient(int c_fd, struct sockaddr *addr, socklen_t addrlen,
                  int sock_family, hw3::QueryProcessor *cp);

int main(int argc, char **argv) {
  // We expect at least a portnumber and one index file as arguments.
  if (argc < 3) {
    Usage(argv[0]);
  }

  // Prepare the list of indices, so that we can pass it in to
  // newly created threads.  This way, each thread can create its
  // own QueryProcessor.
  std::list<std::string> indexlist;
  for (int i = 2; i < argc; i++) {
    indexlist.push_back(argv[i]);
  }

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
    // Allocate and prepare a new "thr_arg" structure that we will
    // pass in to thr_fn() when we create the new thread.
    thr_arg *arg = new thr_arg;
    arg->addrlen = sizeof(arg->addr);
    arg->sock_family = listen_addr_family;
    arg->indexlist = indexlist;

    // Accept the next connection from a client
    arg->c_fd = accept(listen_fd,
                       reinterpret_cast<struct sockaddr *>(&(arg->addr)),
                       &(arg->addrlen));
    if (arg->c_fd < 0) {
      // Check for "try again" vs. a real error.
      if ((errno == EAGAIN) || (errno == EINTR))
        continue;
      std::cerr << "Failure on accept: " << strerror(errno) << std::endl;
      break;
    }

    // Create the new thread, passing in the pointer to the thr_arg
    // we prepared.
    pthread_t thr;
    if (pthread_create(&thr, NULL, thr_fn,
                       reinterpret_cast<void *>(arg)) != 0) {
      std::cerr << "Failure calling pthread_create." << std::endl;
      exit(EXIT_FAILURE);
    }

    // Detach the thread so that we don't have to pthread_join to it.
    if (pthread_detach(thr) != 0) {
      std::cerr << "Failure calling pthread_detach." << std::endl;
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

void *thr_fn(void *arg) {
  // Recover the "thr_arg" from arg.
  thr_arg *ta = reinterpret_cast<thr_arg *>(arg);

  // Create a new QueryProcessor for this thread.
  hw3::QueryProcessor qp(ta->indexlist, false);

  // Call HandleClient to process the query.
  HandleClient(ta->c_fd,
               reinterpret_cast<struct sockaddr *>(&(ta->addr)),
               ta->addrlen,
               ta->sock_family,
               &qp);

  // We're all done with the "thr_arg", so remember to delete it.
  delete ta;

  // Pthreads allows a thread to return information back to the
  // parent that spawned it.  We don't have anything to return
  // here, so we just return NULL.
  return NULL;
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
