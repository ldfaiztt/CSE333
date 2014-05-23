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

#ifndef _HW3_INDEXTABLEREADER_H_
#define _HW3_INDEXTABLEREADER_H_

#include <stdint.h>  // for uint32_t, etc.
#include <string>    // for std::string.
#include <cstdio>    // for (FILE *)

#include "./HashTableReader.h"
#include "./DocIDTableReader.h"

namespace hw3 {

// An IndexTableReader is a subclass of HashTableReader used to
// read the word-->docID_table "index" within the index file.
class IndexTableReader : protected HashTableReader {
  // This is here so that the Test_IndexTableReader unit test fixture can
  // access protected member variables of IndexTableReader.  See
  // test_indextablereader.h for details.
  friend class Test_IndexTableReader;

 public:
  // Construct an IndexTableReader.  Arguments:
  //
  // - f: an open (FILE *) for the underlying index file.  The new
  //   object takes ownership of the (FILE *) and will fclose() it
  //   on destruction.
  //
  // - offset: the file offset of the first byte of the doctable
  IndexTableReader(FILE *f, uint32_t offset);
  ~IndexTableReader() { }

  // Lookup a word and get back a DocIDTableReader containing the
  // docID-->positions mapping associated with the docID.
  //
  // Arguments:
  //
  // - word:  the word to look for
  //
  // Returns:
  //
  // - a pointer to a DocIDTableReader if the word is found.  The caller
  //   takes ownership of this pointer, and must call delete on it when
  //   done with the object.
  //
  // - NULL if the word is not found.
  DocIDTableReader *LookupWord(const std::string &word);
};

}  // namespace hw3

#endif  // _HW3_INDEXTABLEREADER_H_
