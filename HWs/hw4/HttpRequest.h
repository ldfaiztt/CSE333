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

#ifndef _HW4_HTTPREQUEST_H_
#define _HW4_HTTPREQUEST_H_

#include <stdint.h>

#include <map>
#include <string>

using std::string;

namespace hw4 {

// This class represents the state of an HTTP request.  We'll
// only handle "GET"-style requests in this project, which means
// a request has the following format:
//
// GET [URI] [http_protocol]\r\n
// [headername]: [headerval]\r\n
// [headername]: [headerval]\r\n
// ... more headers ...
// [headername]: [headerval]\r\n
// \r\n
//
// e.g.:
//
// GET /foo/bar?baz=bam HTTP/1.1\r\n
// Host: www.news.com\r\n
//
class HttpRequest {
 public:
  HttpRequest() { }
  virtual ~HttpRequest(void) { }

  // Which URI did the client request?
  std::string URI;

  // A map from header name to header value, representing
  // all of the headers that the client supplied to us.  The
  // header names are converted to all lower case; the header
  // values are retained verbatim.
  std::map<std::string, std::string> headers;
};

}  // namespace hw4

#endif  // _HW4_HTTPREQUEST_H_
