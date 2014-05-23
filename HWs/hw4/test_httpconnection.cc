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

#include <sys/types.h>
#include <sys/socket.h>
#include <string>

#include "./HttpRequest.h"
#include "./HttpResponse.h"
#include "./HttpUtils.h"
#include "./HttpConnection.h"

#include "./test_suite.h"
#include "./test_httpconnection.h"

namespace hw4 {

TEST_F(Test_HttpConnection, TestHttpConnectionBasic) {
  // Create a socketpair; we'll hand one end of the socket to the
  // HttpConnection object, and use the other end of the socket
  // ourselves for testing.
  int spair[2] = {-1, -1};
  ASSERT_EQ(0, socketpair(AF_UNIX, SOCK_STREAM, 0, spair));

  // Create the HttpConnection object we'll test.
  HttpConnection hc(spair[0]);

  // Write two requests on the socket.
  std::string req1 = "GET /foo HTTP/1.1\r\n";
  req1 += "Host: somehost.foo.bar\r\n";
  req1 += "Connection: close\r\n";
  req1 += "\r\n";
  std::string req2 = "GET /bar HTTP/1.1\r\n";
  req2 += "Connection: close\r\n";
  req2 += "Host: somehost.foo.bar\r\n";
  req2 +=  "\r\n";
  ASSERT_EQ(static_cast<int>(req1.size()),
            WrappedWrite(spair[1],
                         (unsigned char *) req1.c_str(),
                         static_cast<int>(req1.size())));
  ASSERT_EQ(static_cast<int>(req2.size()),
            WrappedWrite(spair[1],
                         (unsigned char *) req2.c_str(),
                         static_cast<int>(req2.size())));

  // Do the GetNextRequests.
  HttpRequest htreq1, htreq2;
  ASSERT_TRUE(hc.GetNextRequest(&htreq1));
  ASSERT_TRUE(hc.GetNextRequest(&htreq2));

  // Make sure the request parsing worked.
  ASSERT_EQ("/foo", htreq1.URI);
  ASSERT_EQ("somehost.foo.bar", htreq1.headers["host"]);
  ASSERT_EQ("close", htreq1.headers["connection"]);

  ASSERT_EQ("/bar", htreq2.URI);
  ASSERT_EQ("somehost.foo.bar", htreq2.headers["host"]);
  ASSERT_EQ("close", htreq2.headers["connection"]);
  HW4Addpoints(20);

  // Prepare the responses.
  HttpResponse rep1;
  rep1.protocol = "HTTP/1.1";
  rep1.response_code = 200;
  rep1.message = "OK";
  rep1.headers["Host"] = "foo.bar";
  rep1.body = "This is the body of the response.";
  std::string rep1str = "HTTP/1.1 200 OK\r\n";
  rep1str += "Host: foo.bar\r\n";
  rep1str += "Content-length: 33\r\n\r\n";
  rep1str += "This is the body of the response.";

  HttpResponse rep2;
  rep2.protocol = "HTTP/1.1";
  rep2.response_code = 200;
  rep2.message = "OK";
  rep2.headers["Connection"] = "close";
  rep2.body = "This is the second response.";
  std::string rep2str = "HTTP/1.1 200 OK\r\n";
  rep2str += "Connection: close\r\n";
  rep2str += "Content-length: 28\r\n\r\n";
  rep2str += "This is the second response.";

  // Generate the responses, test them.
  unsigned char buf1[1024] = { 0 };
  ASSERT_TRUE(hc.WriteResponse(rep1));
  ASSERT_EQ(static_cast<int>(87), WrappedRead(spair[1], buf1, 1024));
  ASSERT_EQ((const char *) buf1, rep1str);

  unsigned char buf2[1024] = { 0 };
  ASSERT_TRUE(hc.WriteResponse(rep2));
  ASSERT_EQ(static_cast<int>(86), WrappedRead(spair[1], buf2, 1024));
  ASSERT_EQ((const char *) buf2, rep2str);

  // Clean up.
  close(spair[0]);
  close(spair[1]);
  HW4Addpoints(20);
}

}  // namespace hw4
