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

#include <stdint.h>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <map>
#include <string>
#include <vector>

#include "./HttpRequest.h"
#include "./HttpUtils.h"
#include "./HttpConnection.h"

using std::map;
using std::string;

namespace hw4 {

bool HttpConnection::GetNextRequest(HttpRequest *request) {
  // Use "WrappedRead" to read data into the buffer_
  // instance variable.  Keep reading data until either the
  // connection drops or you see a "\r\n\r\n" that demarcates
  // the end of the request header.
  //
  // Once you've seen the request header, use ParseRequest()
  // to parse the header into the *request argument.
  //
  // Very tricky part:  clients can send back-to-back requests
  // on the same socket.  So, you need to preserve everything
  // after the "\r\n\r\n" in buffer_ for the next time the
  // caller invokes GetNextRequest()!

  // MISSING:

  // If the buffer_ has already contained everything
  // for the next request, Parse the request without
  // reading addtional bytes; otherwise, read until
  // the connection dropped or until we see "\r\n\r\n"
  size_t pos = buffer_.find("\r\n\r\n");
  if (pos == std::string::npos) {
    int byte_read;
    unsigned char buf[1024];
    while (1) {
      byte_read = WrappedRead(fd_, buf, 1024);
      if (byte_read == 0) {
        // EOF or connection dropped
        break;
      } else if (byte_read == -1) {
        // read failed
        return false;
      } else {
        // append the bytes to buffer_
        buffer_ += std::string(reinterpret_cast<char*>(buf), byte_read);

        // stop reading if we've read "\r\n\r\n"
        pos = buffer_.find("\r\n\r\n");
        if (pos != std::string::npos)
          break;
      }
    }
  }

  // check if the request header ends with "\r\n\r\n"
  if (pos == std::string::npos)
    return false;

  // parse the header and store it into output parameter
  *request = ParseRequest(pos + 4);

  // return false if the request is not well-formatted
  if (request->URI == "BAD_") {
    request = NULL;
    return false;
  }

  // perserve everything (if any) after "\r\n\r\n" in buffer_
  buffer_ = buffer_.substr(pos + 4);

  return true;
}

bool HttpConnection::WriteResponse(const HttpResponse &response) {
  std::string str = response.GenerateResponseString();
  int res = WrappedWrite(fd_,
                         (unsigned char *) str.c_str(),
                         str.length());
  if (res != static_cast<int>(str.length()))
    return false;
  return true;
}

HttpRequest HttpConnection::ParseRequest(size_t end) {
  HttpRequest req;
  req.URI = "/";  // by default, get "/".

  // Get the header.
  std::string str = buffer_.substr(0, end);

  // Split the header into lines.  Extract the URI from the first line
  // and store it in req.URI.  For each additional line beyond the
  // first, extract out the header name and value and store them in
  // req.headers (i.e., req.headers[headername] = headervalue).
  // You should look at HttpResponse.h for details about the HTTP header
  // format that you need to parse.
  //
  // You'll probably want to look up boost functions for (a) splitting
  // a string into lines on a "\r\n" delimiter, (b) trimming
  // whitespace from the end of a string, and (c) converting a string
  // to lowercase.

  // MISSING:

  // split the request into lines on a "\r\n" delimiter
  std::vector<std::string> lines;
  boost::split(lines, str, boost::is_any_of("\r\n"),
               boost::token_compress_on);

  // check if the request is like this:
  // xxx\r\n
  // [...]
  // \r\n
  if (lines.size() < 2) {
    req.URI = "BAD_";
    return req;
  }

  // trim whitespaces from the end of each line (not sure if needed)
  for (uint32_t i = 0; i < lines.size(); i++)
    boost::trim(lines[i]);

  // split first line into tokens on " " delimiter
  std::vector<std::string> fst_line;
  boost::split(fst_line, lines[0], boost::is_any_of(" "),
               boost::token_compress_on);

  // check the format the first line in request
  if (fst_line.size() == 0) {
    // default: GET / HTTP/1.1
  } else if (fst_line.size() == 1) {
    // We only handle GET, so check if the method in the
    // first line of the request if GET
    if (fst_line[0] != "GET") {
      req.URI = "BAD_";
      return req;
    }
  } else if (fst_line.size() == 2) {
    // If first line has two tokens, the request format should be either
    // GET [URI]\r\n or GET [http_protocol]\r\n;
    // otherwise, it's not well-formatted.
    if (fst_line[0] != "GET" ||
        (fst_line[1][0] != '/' &&
         fst_line[1].find("HTTP/") == std::string::npos)) {
      req.URI = "BAD_";
      return req;
    }
  } else if (fst_line.size() == 3) {
    // If first line has three tokens, the request format should be:
    // GET [URI] [http_protocol]\r\n; otherwise, it's not well-formatted.
    if (fst_line[0] != "GET" ||
        fst_line[1][0] != '/' ||
        fst_line[2].find("HTTP/") == std::string::npos) {
      req.URI = "BAD_";
      return req;
    }

    // store the request URI in URI field
    req.URI = fst_line[1];
  } else {
    // If # of tokens in the first line is not two or three,
    // the request is not well-formatted.
    req.URI = "BAD_";
    return req;
  }

  // split the rest of the lines (except the last line) in request
  // into headername and headervalue on a ": " delimiter
  std::vector<std::string> header;
  for (uint32_t j = 1; j < lines.size() - 1; j++) {
    size_t fst_col = lines[j].find(": ");

    // check if the line is in the format of:
    // [headername]: [headerval]\r\n
    if (fst_col == std::string::npos) {
      req.URI = "BAD_";
      req.headers.clear();
      return req;
    }

    // convert headername to lower case and map
    // headername to headerval in headers
    std::string hname = lines[j].substr(0, fst_col);
    boost::to_lower(hname);
    std::string hval = lines[j].substr(fst_col + 2);
    req.headers[hname] = hval;
  }

  return req;
}

}  // namespace hw4
