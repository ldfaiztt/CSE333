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

#ifndef _HW4_HTTPRESPONSE_H_
#define _HW4_HTTPRESPONSE_H_

#include <stdint.h>

#include <map>
#include <string>
#include <sstream>

using std::string;

namespace hw4 {

// This class represents the state of an HTTP response, including the
// headers and body.  Customers (primarily HttpServer.cc) create an
// instance of this class when preparing their response, and they
// use GenerateResponseString() to generate a string-representation
// ready for sending on a socket.
//
// A response has the following format:
//
// [http_protocol] [response_code] [message]\r\n
// [headername]: [headerval]\r\n
// [headername]: [headerval]\r\n
// ... more headers ...
// [headername]: [headerval]\r\n
// [body]
//
// e.g.:
//
// HTTP/1.1 200 OK\r\n
// Content-length: 10\r\n
// \r\n
// Hi there!!

class HttpResponse {
 public:
  HttpResponse() { }
  virtual ~HttpResponse(void) { }

  // The HTTP protocol string to pass back in the first line.
  std::string protocol;

  // The HTTP response code to pass back in the first line.
  uint16_t response_code;

  // The HTTP response code message to pass back in the first line.
  std::string message;

  // A map from header name to header value, representing
  // all of the headers we'll give back to the client.  Should
  // not contain "Content-length" -- we'll dynamically calculate
  // it inside GenerateReponseString().  The header names should
  // be properly capitalized.
  std::map<std::string, std::string> headers;

  // The body of the response.
  std::string body;

  // A method to generate a std::string of the HTTP response, suitable
  // for writing back to the client.  We automatically generate the
  // "Content-length:" header, and make that be the last header
  // in the block.  The value of the Content-length header is the
  // size of the response body (in bytes).
  std::string GenerateResponseString(void) const {
    std::stringstream header;
    std::map<std::string, std::string>::const_iterator it;

    header << protocol << " " << response_code << " " << message << "\r\n";
    for (it = headers.begin(); it != headers.end(); it++) {
      header << it->first << ": " << it->second << "\r\n";
    }
    header << "Content-length: " << body.size() << "\r\n";
    header << "\r\n";
    header << body;
    return header.str();
  }
};

}  // namespace hw4

#endif  // _HW4_HTTPRESPONSE_H_
