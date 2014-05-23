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

#ifndef _HW3_DOCTABLECHECKER_H_
#define _HW3_DOCTABLECHECKER_H_

#include <stdint.h>  // for uint32_t, etc.
#include <string>    // for std::string
#include <cstdio>    // for (FILE *)

#include "./HashTableChecker.h"

namespace hw3 {

// A DocTableChecker (a subclass of HashTableChecker) is used to
// read the single docid-->docname "doctable" within the index file.
class DocTableChecker : public HashTableChecker {
 public:
  // Construct a new DocTableChecker at a specified offset within
  // an index file.  Arguments:
  //
  // - f: an open (FILE *) for the underlying index file.  The
  //   constructed  object takes ownership of the (FILE *) and will
  //   fclose() it on destruction.
  //
  // - offset: the "doctable"'s byte offset within the file.
   DocTableChecker(FILE *f, uint32_t offset, uint32_t len);
  ~DocTableChecker() { }

  // Check a DocTableElement.
  virtual void CheckElement(uint32_t element_offset,
                            uint32_t bucket_number);

  // Lookup a docid and get back a std::string containing the filename
  // associated with the docid, if it exists.
  //
  // Arguments:
  //
  // - docid:  the docID to look for within the doctable.
  //
  // - ret_tr: the string containing the filename (an output parameter).
  //   Nothing is returned through this if the docID is not found.
  //
  // Returns:
  //
  // - true if the docID is found, false otherwise.
  // bool LookupDocID(const uint64_t &docid, std::string *ret_str);
};

}  // namespace hw3

#endif  // _HW3_DOCTABLECHECKER_H_
