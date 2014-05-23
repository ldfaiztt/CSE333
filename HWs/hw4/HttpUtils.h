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

#ifndef _HW4_HTTPUTILS_H_
#define _HW4_HTTPUTILS_H_

#include <stdint.h>

#include <string>
#include <utility>
#include <map>

using std::pair;
using std::string;
using std::map;

namespace hw4 {

// This function tests whether the file "testfile" is contained below
// the root directory "rootdir".  If so, i.e., if the path is safe,
// the function returns true.  Otherwise, returns false.
//
// So, for example, the following combination is safe:
//
//   rootdir:  "test_files"
//   testfile: "test_files/ok/bar"
//
// but the following is not:
//
//   rootdir:  "test_files"
//   testfile: "libhw1/libhw1.a"
//
// nor is:
//
//   rootdir:  "test_files"
//   testfile: "test_files/../libhw1/libhw1.a"
//
bool IsPathSafe(string rootdir, string testfile);

// This function performs HTML escaping in place.  It scans a string
// for dangerous HTML tokens (such as "<") and replaces them with the
// escaped HTML equivalent (such as "&lt;").  This helps to prevent
// XSS attacks.
string EscapeHTML(const string &from);

// This function performs URI decoding.  It scans a string for
// the "%" escape character and converts the token to the
// appropriate ASCII character.  See the wikipedia article on
// URL encoding for an explanation of what's going on here:
//
//    http://en.wikipedia.org/wiki/Percent-encoding
//
string URIDecode(const string &from);

// A URL that's part of a web request has the following structure:
//
//   /foo/bar/baz?field=value&field2=value2
//
//      path     ?   args
//
// This class accepts a URL and splits it into these components and
// URIDecode()'s them, allowing the caller to access the components
// through convenient methods.
class URLParser {
 public:
  URLParser() { }
  virtual ~URLParser();

  void Parse(const string url);

  // Return the "path" component of the url, post-uri-decoding.
  string get_path() const;

  // Return the "args" component of the url post-uri-decoding.
  // The args component is parsed into a map from field to value.
  map<string, string> get_args() const;

 private:
  string url_;
  string path_;
  map<string, string> args_;
};

// Return a randomly generated port number between 10000 and 40000.
uint16_t GetRandPort();

// A wrapper around "read" that shields the caller from dealing
// with the ugly issues of partial reads, EINTR, EAGAIN, and so
// on.
//
// Reads at most "readlen" bytes from the file descriptor fd
// into the buffer "buf".  Returns the number of bytes actually
// read.  On fatal error, returns -1.  If EOF is hit and no
// bytes have been read, returns 0.  Might read fewer bytes
// than requested.
int WrappedRead(int fd, unsigned char *buf, int readlen);

// A wrapper around "write" that shields the caller from dealing
// with the ugly issues of partial writes, EINTR, EAGAIN, and so
// on.
//
// Writes "writelen" bytes to the file descriptor fd from
// the buffer "buf".  Blocks the caller until either writelen
// bytes have been written, or an error is encountered.  Returns
// the total number of bytes written; if this number is less
// than writelen, it's because some fatal error was encountered,
// like the connection being dropped.
int WrappedWrite(int fd, unsigned char *buf, int writelen);

// A convenience routine to manufacture a (blocking) socket to the
// hostname and port number provided as arguments.  Hostname can
// be a DNS name or an IP address, in string form.  On success,
// returns a file descriptor thorugh "client_fd" and returns true.
// On failure, returns false.  Caller is responsible for close()'ing
// the file descriptor.
bool ConnectToServer(string hostname, uint16_t portnum, int *client_fd);

// As we learned in class, std::unique_ptr is useful for wrapping memory
// that is dynamically allocated from the heap using "new".  If, however,
// you end up using hw2 functions (like ReadFile from hw2/fileparser.h),
// you might be faced with a situation where memory is dynamically allocated
// using malloc, not new.  In this case, you need to teach the unique_ptr
// to use free() instead of delete.
//
// The way you do this is by specifying a "deleter" when you construct
// the unique pointer.  We provide a malloc/free deleter below.  So, to
// use it, you would do something like this:
//
//  std::unique_ptr<char,MallocDeleter<char>> str(malloc(sizeof(char) * len));
//
// Then, when str falls out of scope, its memory will automatically free()'d.
template<typename T>
class MallocDeleter {
 public:
  void operator()(T* ptr) {
    free(ptr);
  }
};


}  // namespace hw4

#endif  // _HW4_HTTPUTILS_H_
