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

#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <list>

#include "./ServerSocket.h"
#include "./HttpServer.h"

using std::cerr;
using std::cout;
using std::endl;

// Print out program usage, and exit() with EXIT_FAILURE.
void Usage(char *progname);

// Parses the command-line arguments, invokes Usage() on failure.
// "port" is a return parameter to the port number to listen on,
// "path" is a return parameter to the directory containing
// our static files, and "indices" is a return parameter to a
// list of index filenames.  Ensures that the path is a readable
// directory, and the index filenames are readable, and if not,
// invokes Usage() to exit.
void GetPortAndPath(int argc,
                    char **argv,
                    uint16_t *port,
                    std::string *path,
                    std::list<std::string> *indices);

int main(int argc, char **argv) {
  // Print out welcome message.
  cout << "Welcome to http333d, the UW cse333 web server!" << endl;
  cout << "  Copyright 2012 Steven Gribble" << endl;
  cout << "  http://www.cs.washington.edu/homes/gribble" << endl;
  cout << endl;
  cout << "initializing:" << endl;
  cout << "  parsing port number and static files directory..." << endl;

  // Ignore the SIGPIPE signal, otherwise we'll crash out if a client
  // disconnects unexpectedly.
  signal(SIGPIPE, SIG_IGN);

  // Get the port number and list of index files.
  uint16_t portnum;
  std::string staticdir;
  std::list<std::string> indices;
  GetPortAndPath(argc, argv, &portnum, &staticdir, &indices);
  cout << "    port: " << portnum << endl;
  cout << "    path: " << staticdir << endl;

  // Run the server.
  hw4::HttpServer hs(portnum, staticdir, indices);
  if (!hs.Run()) {
    cerr << "  server failed to run!?" << endl;
  }

  cout << "server completed!  Exiting." << endl;
  return EXIT_SUCCESS;
}


void Usage(char *progname) {
  cerr << "Usage: " << progname << " port staticfiles_directory indices+";
  cerr << endl;
  exit(EXIT_FAILURE);
}

void GetPortAndPath(int argc,
                    char **argv,
                    uint16_t *port,
                    std::string *path,
                    std::list<std::string> *indices) {
  // Be sure to check a few things:
  //  (a) that you have a sane number of command line arguments
  //  (b) that the port number is reasonable
  //  (c) that "path" (i.e., argv[2]) is a readable directory
  //  (d) that you have at least one index, and that all indices
  //      are readable files.

  // MISSING:

  // check if there are at least four arugments passed in
  if (argc < 4)
    Usage(argv[0]);

  // check if port number (argv[1]) passed in is reasonable
  *port = atoi(argv[1]);
  if (*port < 1024) {
    cerr << "Port number < 1024 is not reasonable." << endl;
    Usage(argv[0]);
  }

  // check if path (argv[2]) passed in is a readable directory
  struct stat dirstat;
  if (stat(argv[2], &dirstat) == -1) {
    cerr << argv[2] << " is not readable." << endl;
    Usage(argv[0]);
  }

  if (!S_ISDIR(dirstat.st_mode)) {
    cerr << argv[2] << " is not a directory." << endl;
    Usage(argv[0]);
  }

  *path = std::string(argv[2]);

  // check the rest of the command line arguments to see
  // if there is at least one readable index file
  for (int i = 3; i < argc; i++) {
    std::string fname(argv[i]);
    if (fname.length() >= 4 && fname.substr(fname.length() - 4) == ".idx") {
      struct stat fstat;
      if (stat(argv[i], &fstat) == -1) {
        cerr << argv[i] << " is not readable." << endl;
        Usage(argv[0]);
      }

      if (!S_ISREG(fstat.st_mode)) {
        cerr << argv[i] << " is not a regular file." << endl;
        Usage(argv[0]);
      }

      indices->push_back(argv[i]);
    }
  }

  // invoke Usage to exit if there is no readable index file passed in
  if (indices->size() == 0) {
    cerr << "Didn't pass in at least one readable index file." << endl;
    Usage(argv[0]);
  }
}
