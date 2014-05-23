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

#ifndef _HW3_INDEXTABLECHECKER_H_
#define _HW3_INDEXTABLECHECKER_H_

#include <stdint.h>  // for uint32_t, etc.
#include <string>    // for std::string.
#include <cstdio>    // for (FILE *)

#include "./HashTableChecker.h"
#include "./DocIDTableChecker.h"

namespace hw3 {

// An IndexTableChecker is a subclass of HashTableChecker used to
// read the word-->docID_table "index" within the index file.
class IndexTableChecker : public HashTableChecker {
 public:
  // Construct an IndexTableChecker.  Arguments:
  //
  // - f: an open (FILE *) for the underlying index file.  The new
  //   object takes ownership of the (FILE *) and will fclose() it
  //   on destruction.
  //
  // - offset: the file offset of the first byte of the doctable
   IndexTableChecker(FILE *f, uint32_t offset, uint32_t len);
  ~IndexTableChecker() { }

  // Check an IndexTableElement.
  virtual void CheckElement(uint32_t element_offset,
                            uint32_t bucket_number);
};

}  // namespace hw3

#endif  // _HW3_INDEXTABLECHECKER_H_
