/*
 * Copyright 2012 Steven Gribble.  This program is part of the cse333
 * course sequence.
 */

#ifndef _SEARCHSERVER_SOCKETLINEREADER_H_
#define _SEARCHSERVER_SOCKETLINEREADER_H_

#include <string>
#include <vector>

// A SocketLineReader is a class that reads data from a socket into
// an internal buffer, splits the data into lines terminated by '\n',
// and returns lines to the caller one at a time.
class SocketLineReader {
 public:
  explicit SocketLineReader(int cfd) : cfd_(cfd) { }
  virtual ~SocketLineReader() { }

  // This method returns the next line of data received from the
  // socket to the caller.  A line of data is data that terminates
  // with a '\n' character.
  //
  // If a line of data is found, it is returned through the output
  // parameter "nextline", and the function returns true.
  //
  // If EOF or an error occurs before the next line is found,
  // returns false.
  bool GetNextLine(std::string *line);

  // Takes a line and splits it up into zero or more
  // whitespace-separated words.  Returns a vector of these words.
  static std::vector<std::string> SplitIntoWords(const std::string &line);

 private:
  // The file descriptor we're reading from.
  int cfd_;

  // The buffer we're reading into.
  std::vector<char> buf_;

  // The amount we attempt to read on each pass through the main
  // read loop.
  static const unsigned int kReadAmount = 2048;
};

#endif  // _SEARCHSERVER_SOCKETLINEREADER_H_
