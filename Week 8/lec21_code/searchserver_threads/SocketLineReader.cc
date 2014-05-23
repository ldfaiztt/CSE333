/*
 * Copyright 2012 Steven Gribble.  This program is part of the cse333
 * course sequence.
 */

#include <string.h>
#include <algorithm>
#include <unistd.h>
#include <sstream>

#include "./SocketLineReader.h"

bool SocketLineReader::GetNextLine(std::string *line) {
  // Keep attempting to read data until we find a '\n' terminated
  // line within buf_.
  while (1) {
    // Do we have a '\n' terminated line in buf_?  If so, return it
    // and shift the data in buf_.
    unsigned int offset = 0;
    while (offset < buf_.size()) {
      if (buf_[offset] == '\n') {
        // Found our line!  Return it and shift buf_ down.
        *line = std::string(&(buf_[0]), offset + 1);
        buf_.erase(buf_.begin(), buf_.begin() + offset + 1);
        return true;
      }
      offset++;
    }

    // We didn't find a line, so we need to read() more data.  First,
    // we need to resize buf_ to handle the new characters we might
    // read; later, we'll trim the characters we didn't.
    unsigned int readoffset = buf_.size();
    buf_.resize(readoffset + kReadAmount);

    // Read more data.
    int res = read(cfd_, &(buf_[readoffset]), kReadAmount);
    if (res > 0) {
      // Trim the part of the buffer we didn't read into.
      buf_.erase(buf_.begin() + readoffset + res,
                 buf_.begin() + readoffset + kReadAmount);
      continue;
    }

    // Did we hit EINTR/EAGAIN?
    if ((res == -1) && ((errno == EAGAIN) || (errno == EINTR)))
      continue;

    // We either hit EOF (res == 0) or a real error (res == -1)
    break;
  }

  // Broke out of the loop, so we must have hit an error.
  return false;
}

std::vector<std::string> SocketLineReader::SplitIntoWords(
    const std::string &line) {
  std::stringstream ss(line);
  std::vector<std::string> retvec;
  std::string word;

  while (ss >> word) {
    std::transform(word.begin(), word.end(), word.begin(), ::tolower);
    retvec.push_back(word);
  }
  return retvec;
}
