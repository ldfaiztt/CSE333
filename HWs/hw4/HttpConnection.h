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

#ifndef _HW4_HTTPCONNECTION_H_
#define _HW4_HTTPCONNECTION_H_

#include <stdint.h>
#include <unistd.h>
#include <map>
#include <string>

#include "./HttpRequest.h"
#include "./HttpResponse.h"

namespace hw4 {

// Comment here
class HttpConnection {
 public:
  explicit HttpConnection(int fd) : fd_(fd) { }
  virtual ~HttpConnection(void) {
    close(fd_);
    fd_ = -1;
  }

  // Read and parse the next request from the file descriptor fd_,
  // storing the state in the output parameter "request."  Returns
  // true if a request could be read, false if the parsing failed
  // for some reason, in which case the caller should close the
  // connection.
  bool GetNextRequest(HttpRequest *request);

  // Write the response to the file descriptor fd_.  Returns true
  // if the response was successfully written, false if the
  // connection experiences an error and should be closed.
  bool WriteResponse(const HttpResponse &response);

 private:
  // A helper function to parse the contents of data read from
  // the HTTP connection.
  HttpRequest ParseRequest(size_t end_of_headers);

  // The file descriptor associated with the client.
  int fd_;

  // A buffer storing data read from the client.
  std::string buffer_;
};

}  // namespace hw4

#endif  // _HW4_HTTPCONNECTION_H_
