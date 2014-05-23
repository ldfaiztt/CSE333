/*
 * Copyright 2011 Steven Gribble
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

#ifndef _HW3_FILEINDEXCHECKER_H_
#define _HW3_FILEINDEXCHECKER_H_

#include <stdint.h>  // for uint32_t, etc.
#include <string>    // for std::string
#include <cstdio>    // for (FILE *)

#include "./fileindexutil.h"    // for DISALLOW_COPY_AND_ASSIGN()

using namespace std;

namespace hw3 {

// A FileIndexChecker is used to access an index file, validate the
// header information out of it, and manufacture DocTableChecker and
// IndexTableChecker hash table accessors.  (To manufacture a
// DocIDTableChecker, you use a manufactured IndexTableChecker.)
class FileIndexChecker {
 public:
  // Arguments:
  //
  // - filename: the index file to load.
  FileIndexChecker(string filename);
  ~FileIndexChecker();

 protected:
  // The name of the index file we're checking.
  string filename_;

  // The stdio.h (FILE *) for the file.
  FILE *file_;

  // A cached copy of the doctable size field from the index header.
  uint32_t doctable_size_;

  // A cached copy of the index size field from the index header.
  uint32_t index_size_;

 private:
  // Disable the copy constructor and assignment operator.  See
  // the following helpful Google C++ style guide entry for details
  // on how this works and why it is a good idea to do, when you can:
  //
  //    http://google-styleguide.googlecode.com/svn/trunk/
  //    cppguide.xml#Copy_Constructors
  DISALLOW_COPY_AND_ASSIGN(FileIndexChecker);
};

}  // namespace hw3

#endif  // _HW3_FILEINDEXCHECKER_H_
