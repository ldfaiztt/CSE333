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

#include <arpa/inet.h>  // for ntohl(), etc.
#include <stdint.h>     // for uint32_t, etc.
#include <sstream>      // for std::stringstream

#include "./fileindexutil.h"  // for ntohll()
#include "./DocTableReader.h"

extern "C" {
  #include "libhw1/Assert333.h"
}

namespace hw3 {

// The constructor for DocTableReader calls the constructor
// of HashTableReader(), its superclass. The superclass takes
// care of taking ownership of f and using it to extract and
// cache the number of buckets within the table.
DocTableReader::DocTableReader(FILE *f, uint32_t offset)
  : HashTableReader(f, offset) { }

bool DocTableReader::LookupDocID(const uint64_t &docid,
                                 std::string *ret_str) {
  // Use the superclass's "LookupElementPositions" function to
  // walk through the doctable and get back a list of offsets
  // to elements in the bucket for this docID.
  std::list<uint32_t> elements = LookupElementPositions(docid);

  // If the list is empty, we're done.
  if (elements.size() == 0)
    return false;

  // Iterate through the elements, looking for our docID.
  std::list<uint32_t>::iterator it;
  for (it = elements.begin(); it != elements.end(); it++) {
    uint32_t next_offset = *it;

    // Slurp the next docid out of the element.
    uint64_t element_docid;
    // MISSING:
    // seek to the element's position and read its docID
    Assert333(fseek(file_, next_offset, SEEK_SET) == 0);
    Assert333(fread(&element_docid, sizeof(element_docid), 1, file_) == 1);

    // convert docID to host order
    element_docid = ntohll(element_docid);

    // Is it a match?
    if (element_docid == docid) {
      // Yes!  Extract the filename length.
      uint16_t filename_len;
      // MISSING:
      Assert333(fread(&filename_len, sizeof(filename_len), 1, file_) == 1);

      // convert filename lenthg to host order
      filename_len = ntohs(filename_len);

      // Extract the filename, using a stringstream and its "<<"
      // operator, fread()'ing a character at a time.
      std::stringstream ss;
      for (int i = 0; i < filename_len; i++) {
        uint8_t nextc;

        Assert333(fread(&nextc, 1, 1, file_) == 1);
        ss << nextc;
      }

      // Using the str() method of ss to extract a std::string object,
      // and return it through the output parameter ret_str.  Return
      // true.
      // MISSING:
      *ret_str = ss.str();

      return true;
    }
  }

  // We failed to find a matching docID, so return false.
  return false;
}

}  // namespace hw3
