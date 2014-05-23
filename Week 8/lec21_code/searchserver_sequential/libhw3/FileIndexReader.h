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

#ifndef _HW3_FILEINDEXREADER_H_
#define _HW3_FILEINDEXREADER_H_

#include <stdint.h>  // for uint32_t, etc.
#include <string>    // for std::string
#include <cstdio>    // for (FILE *)

#include "./fileindexutil.h"    // for DISALLOW_COPY_AND_ASSIGN()
#include "./DocTableReader.h"
#include "./IndexTableReader.h"

using std::string;

namespace hw3 {

// A FileIndexReader is used to access an index file, read the header
// information out of it,  and manufacture DocTableReader and
// IndexTableReader hash table accessors.  (To manufacture a
// DocIDTableReader, you use a manufactured IndexTableReader.)
class FileIndexReader {
  // This friend declaration is here so that the Test_FileIndexReader
  // unit test fixture can access protected member variables of
  // FileIndexReader.  See test_fileindexreader.h for details.
  friend class Test_FileIndexReader;

 public:
  // Arguments:
  //
  // - filename: the index file to load.
  //
  // - validate: whether to validate the checksums (default=true).
  FileIndexReader(string filename, bool validate = true);
  ~FileIndexReader();

  // Manufactures and returns a DocTableReader for this index file.
  // A DocTableReader is a HashTableReader subclass that is
  // specialized to read the docid-->filename hashtable within this
  // index file. (See DocTableReader.h for details.)
  DocTableReader GetDocTableReader();

  // Manufactures and returns an IndexTableReader for this index file.
  // An IndexTableReader is a HashTableReader subclass that is
  // specialized to read the word-->docidtable hashtable within this
  // index file. (See IndexTableReader.h for details.)
  IndexTableReader GetIndexTableReader();

 protected:
  // The name of the index file we're reading.
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
  DISALLOW_COPY_AND_ASSIGN(FileIndexReader);
};

}  // namespace hw3

#endif  // _HW3_FILEINDEXREADER_H_
