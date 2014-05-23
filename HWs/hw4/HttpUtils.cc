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

// This file contains a number of HTTP and HTML parsing routines
// that come in useful throughput the assignment.

#include <arpa/inet.h>
#include <errno.h>
#include <limits.h>
#include <netdb.h>
#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string.hpp>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>
#include <vector>
#include "./HttpUtils.h"

using boost::algorithm::replace_all;
using std::vector;

namespace hw4 {

bool IsPathSafe(string rootdir, string testfile) {
  char rootpathbuffer[PATH_MAX], testfilebuffer[PATH_MAX];
  if (!realpath(rootdir.c_str(), rootpathbuffer))
    return false;
  if (!realpath(testfile.c_str(), testfilebuffer))
    return false;

  // Make sure that testfile is a prefix of rootdir.
  if (strlen(testfilebuffer) <= strlen(rootpathbuffer))
    return false;
  if (strncmp(rootpathbuffer,
              testfilebuffer,
              strlen(rootpathbuffer)) != 0)
    return false;

  // It's safe!
  return true;
}

string EscapeHTML(const string &from) {
  string ret = from;
  replace_all(ret, "&",  "&amp;");
  replace_all(ret, "\"", "&quot;");
  replace_all(ret, "\'", "&apos;");
  replace_all(ret, "<",  "&lt;");
  replace_all(ret, ">",  "&gt;");
  return ret;
}

// Look for a "%XY" token in the string, where XY is a
// hex number.  Replace the token with the appropriate ASCII
// character, but only if 32 <= dec(XY) <= 127.
string URIDecode(const string &from) {
  string retstr;

  if (from.length() < 3)
    return from;

  // Loop through the characters in the string.
  for (unsigned int pos = 0; pos < from.length(); pos++) {
    char c1 = from[pos];
    char c2 = (pos < from.length()-1) ? toupper(from[pos+1]) : ' ';
    char c3 = (pos < from.length()-2) ? toupper(from[pos+2]) : ' ';

    // Special case the '+' for old encoders.
    if (c1 == '+') {
      retstr.append(1, ' ');
      continue;
    }

    // Is this an escape sequence?
    if (c1 != '%') {
      retstr.append(1, c1);
      continue;
    }

    // Yes.  Are the next two characters hex digits?
    if (!((('0' <= c2) && (c2 <= '9')) ||
          (('A' <= c2) && (c2 <= 'F')))) {
      retstr.append(1, c1);
      continue;
    }
    if (!((('0' <= c3) && (c3 <= '9')) ||
           (('A' <= c3) && (c3 <= 'F')))) {
      retstr.append(1, c1);
      continue;
    }

    // Yes.  Convert to a code.
    uint8_t code = 0;
    if (c2 >= 'A') {
      code = 16 * (10 + (c2 - 'A'));
    } else {
      code = 16 * (c2 - '0');
    }
    if (c3 >= 'A') {
      code += 10 + (c3 - 'A');
    } else {
      code += (c3 - '0');
    }

    // Is the code reasonable?
    if (!((code >= 32) && (code <= 127))) {
      retstr.append(1, c1);
      continue;
    }

    // Great!  Convert and append.
    retstr.append(1, static_cast<char>(code));
    pos += 2;
  }
  return retstr;
}

void URLParser::Parse(const string url) {
  url_ = url;

  // Split the URL into the path and the args components.
  vector<string> ps;
  boost::split(ps, url, boost::is_any_of("?"));
  if (ps.size() < 1)
    return;

  // Store the URI-decoded path.
  path_ = URIDecode(ps[0]);

  if (ps.size() < 2)
    return;

  // Split the args into each field=val; chunk.
  vector<string> vals;
  boost::split(vals, ps[1], boost::is_any_of("&"));

  // Iterate through the chunks.
  for (unsigned int i = 0; i < vals.size(); i++) {
    // Split the chunk into field, value.
    string val = vals[i];
    vector<string> fv;
    boost::split(fv, val, boost::is_any_of("="));
    if (fv.size() == 2) {
      // Add the field, value to the args_ map.
      args_[URIDecode(fv[0])] = URIDecode(fv[1]);
    }
  }
}

URLParser::~URLParser() { }

string URLParser::get_path() const {
  return path_;
}

map<string, string> URLParser::get_args() const {
  return args_;
}

uint16_t GetRandPort() {
  uint16_t portnum = 10000;
  portnum += ((uint16_t) getpid()) % 25000;
  portnum += ((uint16_t) rand()) % 5000;  // NOLINT(runtime/threadsafe_fn)
  return portnum;
}

int WrappedRead(int fd, unsigned char *buf, int readlen) {
  int res;
  while (1) {
    res = read(fd, buf, readlen);
    if (res == -1) {
      if ((errno == EAGAIN) || (errno == EINTR))
        continue;
    }
    break;
  }
  return res;
}

int WrappedWrite(int fd, unsigned char *buf, int writelen) {
  int res, written_so_far = 0;

  while (written_so_far < writelen) {
    res = write(fd, buf + written_so_far, writelen - written_so_far);
    if (res == -1) {
      if ((errno == EAGAIN) || (errno == EINTR))
        continue;
      break;
    }
    if (res == 0)
      break;
    written_so_far += res;
  }
  return written_so_far;
}

bool ConnectToServer(string hostname, uint16_t portnum, int *client_fd) {
  struct addrinfo hints, *results, *r;
  int clientsock, retval;
  char portstr[10];

  // Convert the port number to a C-style string.
  snprintf(portstr, sizeof(portstr), "%hu", portnum);

  // Zero out the hints data structure using memset.
  memset(&hints, 0, sizeof(hints));

  // Indicate we're happy with either AF_INET or AF_INET6 addresses.
  hints.ai_family = AF_UNSPEC;

  // Constrain the answers to SOCK_STREAM addresses.
  hints.ai_socktype = SOCK_STREAM;

  // Do the lookup.
  if ((retval = getaddrinfo(hostname.c_str(),
                            portstr,
                            &hints,
                            &results)) != 0) {
    std::cerr << "getaddrinfo failed: ";
    std::cerr << gai_strerror(retval) << std::endl;
    return false;
  }

  // Loop through, trying each out until one succeeds.
  for (r = results; r != NULL; r = r->ai_next) {
    // Try manufacturing the socket.
    if ((clientsock = socket(r->ai_family, SOCK_STREAM, 0)) == -1) {
      continue;
    }
    // Try connecting to the peer.
    if (connect(clientsock, r->ai_addr, r->ai_addrlen) == -1) {
      continue;
    }
    *client_fd = clientsock;
    freeaddrinfo(results);
    return true;
  }
  freeaddrinfo(results);
  return false;
}

}  // namespace hw4
