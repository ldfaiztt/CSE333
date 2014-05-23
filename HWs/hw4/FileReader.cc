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

#include <stdio.h>
#include <stdint.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>

extern "C" {
  #include "libhw2/fileparser.h"
}

#include "./HttpUtils.h"
#include "./FileReader.h"

namespace hw4 {

bool FileReader::ReadFile(std::string *str) {
  std::string fullfile = basedir_ + "/" + fname_;

  // Read the file into memory, and store the file contents in the
  // output parameter "str."  Be careful to handle binary data
  // correctly; i.e., you probably want to use the two-argument
  // constructor to std::string (the one that includes a length as a
  // second argument).
  //
  // You might find ::ReadFile() from HW2's fileparser.h useful
  // here.  Be careful, though; remember that it uses malloc to
  // allocate memory, so you'll need to use free() to free up that
  // memory.  Alternatively, you can use a unique_ptr with a malloc/free
  // deleter to automatically manage this for you; see the comment in
  // HttpUtils.h above the MallocDeleter class for details.

  // MISSING:

  // check if the file exists above basedir_
  if (!IsPathSafe(basedir_, fullfile))
    return false;

  // get the file content using ReadFile from fileparser.h
  uint64_t size;
  char *file_content = ::ReadFile(fullfile.c_str(), &size);

  // return false if the file cannot be found or be opened
  if (file_content == NULL)
    return false;

  // store the content in output parameter
  *str = std::string(file_content, size);

  // free the memory allocated for the file content
  free(file_content);
  return true;
}

}  // namespace hw4
