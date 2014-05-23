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

#include "./fileindexutil.h"  // for ntohll()
#include "./DocIDTableReader.h"

extern "C" {
  #include "libhw1/Assert333.h"
}

namespace hw3 {

// The constructor for DocIDTableReader calls the constructor
// of HashTableReader(), its superclass. The superclass takes
// care of taking ownership of f and using it to extract and
// cache the number of buckets within the table.
DocIDTableReader::DocIDTableReader(FILE *f, uint32_t offset)
  : HashTableReader(f, offset) { }

bool DocIDTableReader::LookupDocID(const uint64_t &docid,
                                   std::list<uint32_t> *ret_list) {
  // Use the superclass's "LookupElementPositions" function to
  // walk through the docIDtable and get back a list of offsets
  // to elements in the bucket for this docID.
  std::list<uint32_t> elements = LookupElementPositions(docid);

  // If the list of elements is empty, we're done.
  if (elements.size() == 0)
    return false;

  // Iterate through the elements, looking for our docID.
  std::list<uint32_t>::iterator it;
  for (it = elements.begin(); it != elements.end(); it++) {
    uint32_t next_offset = *it;

    // Slurp the next docid out of the element.
    uint64_t element_docid;
    // MISSING:
    // seek to element's position and read its docID
    Assert333(fseek(file_, next_offset, SEEK_SET) == 0);
    Assert333(fread(&element_docid, sizeof(element_docid), 1, file_) == 1);

    // convert docID to host order
    element_docid = ntohll(element_docid);

    // Is it a match?
    if (element_docid == docid) {
      // Yes!  Extract the number of positions in the list.
      uint32_t num_pos;
      // MISSING:
      Assert333(fread(&num_pos, sizeof(num_pos), 1, file_) == 1);

      // convert number of position to host order
      num_pos = ntohl(num_pos);

      // Extract the positions themselves, appending to
      // std::list<uint32_t>.  Be sure to push in the right
      // order, adding to the end of the list as you extract
      // successive positions.

      // MISSING:
      std::list<uint32_t> retval;
      uint32_t nextpos, i;
      for (i = 0; i < num_pos; i++) {
        Assert333(fread(&nextpos, sizeof(nextpos), 1, file_) == 1);

        // convert the position to host order
        nextpos = ntohl(nextpos);

        retval.push_back(nextpos);
      }


      // Return the positions list through the output parameter,
      // and return true.

      // MISSING:
      *ret_list = retval;

      return true;
    }
  }

  // We failed to find a matching docID, so return false.
  return false;
}

list<pair<uint64_t, uint32_t> > DocIDTableReader::GetDocIDList() {
  // This will be our returned list of docIDs within this table.
  list<pair<uint64_t, uint32_t> > docidlist;

  // Go through *all* of the buckets of this hashtable, extracting
  // out the docids in each element and the number of word positions
  // for the each docid.
  for (uint32_t i = 0; i < num_buckets_; i++) {
    // Seek to the next bucket_rec.  The "offset_" member
    // variable stores the offset of this docid table within
    // the index file.
    // MISSING:
    Assert333(fseek(file_, offset_ + 4 + i * 8, SEEK_SET) == 0);

    // Read in the chain length and bucket position fields from
    // the bucket_rec.
    uint32_t chainlen, bucketposition;
    // MISSING:
    Assert333(fread(&chainlen, sizeof(chainlen), 1, file_) == 1);
    Assert333(fread(&bucketposition, sizeof(bucketposition), 1, file_) == 1);

    // convert chain length and bucket position to host order
    chainlen = ntohl(chainlen);
    bucketposition = ntohl(bucketposition);

    // Sweep through the next bucket, iterating through each
    // chain element in the bucket.
    for (uint32_t j = 0; j < chainlen; j++) {
      // Seek to chain element's position field in the bucket header.
      Assert333(fseek(file_, bucketposition + j*4, SEEK_SET) == 0);

      // Read the next element position from the bucket header.
      uint32_t elementposition;
      // MISSING:
      Assert333(fread(&elementposition, sizeof(elementposition), 1, file_) == 1);

      // convert element position to host order
      elementposition = ntohl(elementposition);

      // Seek to the element itself.
      // MISSING:
      Assert333(fseek(file_, elementposition, SEEK_SET) == 0);

      // Read in the docid from the element.
      uint64_t docid;
      // MISSING:
      Assert333(fread(&docid, sizeof(docid), 1, file_) == 1);

      // convert docID to host order
      docid = ntohll(docid);

      // Read in the number of positions from the element.
      uint32_t numposn;
      // MISSING:
      Assert333(fread(&numposn, sizeof(numposn), 1, file_) == 1);

      // convert number of positions to host order
      numposn = ntohl(numposn);

      // Append it to our result list.
      docidlist.push_back(pair<uint64_t, uint32_t>(docid, numposn));
    }
  }

  // Done!  Return the result list.
  return docidlist;
}

}  // namespace hw3
