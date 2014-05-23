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

#include <assert.h>     // for assert()
#include <arpa/inet.h>  // for ntohl(), etc.
#include <stdint.h>     // for uint32_t, etc.
#include <iostream>     // for cout, endl, etc.

#include "./fileindexutil.h"  // for ntohll()

#include "./DocIDTableChecker.h"

using namespace std;

namespace hw3 {

// The constructor for DocIDTableChecker calls the constructor
// of HashTableChecker(), its superclass. The superclass takes
// care of taking ownership of f and using it to extract and
// cache the number of buckets within the table.
DocIDTableChecker::DocIDTableChecker(FILE *f, uint32_t offset, uint32_t len)
  : HashTableChecker(f, offset, len) { }

void DocIDTableChecker::CheckElement(uint32_t element_offset,
                                     uint32_t bucket_number) {
  // seek to the start of the element
  assert(fseek(file_, element_offset, SEEK_SET) == 0);

  // read the docID
  uint64_t docid;
  assert(fread(&docid, 8, 1, file_) == 1);
  docid = ntohll(docid);

  // make sure the docID is in the right bucket
  Check64(bucket_number, (uint32_t) (docid % num_buckets_),
          "[DocID table] DocID % num_buckets == bucket_number");

  // read in the number of positions
  uint32_t numposn;
  assert(fread(&numposn, 4, 1, file_) == 1);
  numposn = ntohl(numposn);
  CheckLT32(numposn, 1000000, "[DocID table] num_positions");

  // loop through and check the positions
  uint32_t prevposn;
  for (uint32_t i = 0; i < numposn; i++) {
    uint32_t curposn;
    assert(fread(&curposn, 4, 1, file_) == 1);
    curposn = ntohl(curposn);
    if (i > 0) {
      CheckLT32(prevposn,
                curposn,
                "word position[i] < word position[i+1]");
    }
    prevposn = curposn;
  }
}


// bool DocIDTableChecker::LookupDocID(const uint64_t &docid,
//                                    std::list<uint32_t> *ret_list) {
//   // Use the superclass's "LookupElementPositions" function to
//   // walk through the docIDtable and get back a list of offsets
//   // to elements in the bucket for this docID.
//   std::list<uint32_t> elements = LookupElementPositions(docid);

//   // If the list of elements is empty, we're done.
//   if (elements.size() == 0)
//     return false;

//   // Iterate through the elements, looking for our docID.
//   std::list<uint32_t>::iterator it;
//   for (it = elements.begin(); it != elements.end(); it++) {
//     uint32_t next_offset = *it;

//     // Slurp the next docid out of the element.
//     uint64_t element_docid;
//     assert(fseek(file_, next_offset, SEEK_SET) == 0);
//     assert(fread(&element_docid, 8, 1, file_) == 1);
//     element_docid = ntohll(element_docid);

//     // Is it a match?
//     if (element_docid == docid) {
//       // Yes!  Extract the number of positions in the list.
//       uint32_t num_pos;
//       assert(fread(&num_pos, 4, 1, file_) == 1);
//       num_pos = ntohl(num_pos);

//       // Extract the positions themselves, appending to
//       // std::list<uint32_t>.
//       std::list<uint32_t> poslist;
//       for (uint32_t i = 0; i < num_pos; i++) {
//         uint32_t next_pos;
//         assert(fread(&next_pos, 4, 1, file_) == 1);
//         next_pos = ntohl(next_pos);
//         poslist.push_back(next_pos);
//       }

//       // Return the positions list through the output parameter,
//       // and return true.
//       *ret_list = poslist;
//       return true;
//     }
//   }

//   // We failed to find a matching docID, so return false.
//   return false;
// }

// list<pair<uint64_t, uint32_t> > DocIDTableChecker::GetDocIDList() {
//   // This will be our returned list of docIDs within this table.
//   list<pair<uint64_t, uint32_t> > docidlist;

//   // Go through *all* of the buckets of this hashtable, extracting
//   // out the docids in each element and the number of word positions
//   // for the each docid.
//   for (uint32_t i = 0; i < num_buckets_; i++) {
//     // Seek to the next bucket_rec.  The "offset_" member
//     // variable stores the offset of this docid table within
//     // the index file .
//     assert(fseek(file_, offset_ + 4 + 8*i, SEEK_SET) == 0);

//     // Read in the chain length and bucket position fields from
//     // the bucket_rec.
//     uint32_t chainlen, bucketposition;
//     assert(fread(&chainlen, 4, 1, file_) == 1);
//     chainlen = ntohl(chainlen);
//     assert(fread(&bucketposition, 4, 1, file_) == 1);
//     bucketposition = ntohl(bucketposition);

//     // Sweep through the next bucket, iterating through each
//     // chain element in the bucket.
//     for (uint32_t j = 0; j < chainlen; j++) {
//       // Seek to chain element's position field in the bucket header.
//       assert(fseek(file_, bucketposition + j*4, SEEK_SET) == 0);

//       // Read the next element position from the bucket header.
//       uint32_t elementposition;
//       assert(fread(&elementposition, 4, 1, file_) == 1);
//       elementposition = htonl(elementposition);

//       // Seek to the element itself.
//       assert(fseek(file_, elementposition, SEEK_SET) == 0);

//       // Read in the docid from the element.
//       uint64_t docid;
//       assert(fread(&docid, 8, 1, file_) == 1);
//       docid = ntohll(docid);

//       // Read in the number of positions from the element.
//       uint32_t numposn;
//       assert(fread(&numposn, 4, 1, file_) == 1);
//       numposn = ntohl(numposn);

//       // Append it to our result list.
//       docidlist.push_back(pair<uint64_t, uint32_t>(docid, numposn));
//     }
//   }

//   // Done!  Return the result list.
//   return docidlist;
// }

}  // namespace hw3
