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

#ifndef _HW3_DOCIDTABLEREADER_H_
#define _HW3_DOCIDTABLEREADER_H_

#include <stdint.h>  // for uint32_t, etc.
#include <list>      // for std::list
#include <utility>   // for std::pair
#include <cstdio>    // for (FILE *)

#include "./HashTableChecker.h"

using std::list;
using std::pair;

namespace hw3 {

// A DocIDTableChecker (a subclass of HashTableChecker) is used to
// read one of the many the embedded docid-->positions "docIDtable"
// tables within the index file.
class DocIDTableChecker : public HashTableChecker {
 public:
  // Construct a new DocIDTableChecker at a specific offset with an
  // index file.  Arguments:
  //
  // - f: an open (FILE *) for the underlying index file.  The
  //   constructed object takes ownership of the (FILE *) and will
  //   fclose() it  on destruction.
  //
  // - offset: the "docIDtable"'s byte offset within the file.
   DocIDTableChecker(FILE *f, uint32_t offset, uint32_t len);
  ~DocIDTableChecker() { }

  // Check a DocIDTableElement.
  virtual void CheckElement(uint32_t element_offset,
                            uint32_t bucket_number);

  /* // Lookup a docid and get back a std::list<uint32_t> containing the */
  /* // positions listed for that docid. */
  /* // */
  /* // Arguments: */
  /* // */
  /* // - docid:  the docID to look for within the docIDtable. */
  /* // */
  /* // - ret_tr: the std::list<uint32_t> containing the positions of */
  /* //   the word in the document (an output parameter). Nothing is */
  /* //   returned through this if the docID is not found. */
  /* // */
  /* // Returns: */
  /* // */
  /* // - true if the docID is found, false otherwise. */
  /* bool LookupDocID(const uint64_t &docid, list<uint32_t> *ret_list); */

  /* // Returns a list<<pair<uint64_t, uint32_t> > of (docids, num_posns) */
  /* // pairs where "num_posns" is the number of matches the word has */
  /* // within that docID for this docIDtable. */
  /* list<pair<uint64_t, uint32_t> > GetDocIDList(); */
};

}  // namespace hw3

#endif  // _HW3_DOCIDTABLEREADER_H_
