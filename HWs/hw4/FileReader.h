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

#ifndef _HW4_FILEREADER_H_
#define _HW4_FILEREADER_H_

#include <string>

namespace hw4 {

// This class is used to read a file into memory and return its
// contents as a string.
class FileReader {
 public:
  // "basedir" is the directory inside of which we will look for
  // files, and "fname" is a filename relative to that directory.
  // For example, if:
  //
  //   basedir is   "./hw4_htmldir"
  //   fname is     "test/foo.html"
  //
  // then we would read in "./hw4_htmldir/test/foo.html"
  FileReader(std::string basedir, std::string fname)
    : basedir_(basedir), fname_(fname) { }
  virtual ~FileReader(void) { }

  // Attempts to reads in the file specified by the constructor
  // arguments. If the file could not be found, could not be opened,
  // or exists above the basedir in the file system hierarchy (e.g.,
  // filename is "../../../escape.html"), returns false.  Otherwise,
  // returns true and also returns the file contents through "str".
  bool ReadFile(std::string *str);

 private:
  std::string basedir_;
  std::string fname_;
};

}  // namespace hw4

#endif  // _HW4_FILEREADER_H_
