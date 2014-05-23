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

#include <arpa/inet.h>        // for ntohl().

#include "./fileindexutil.h"  // for FileDup().
#include "./HashTableReader.h"

extern "C" {
  #include "libhw1/Assert333.h"
}

namespace hw3 {

HashTableReader::HashTableReader(FILE *f, uint32_t offset)
  : file_(f), offset_(offset) {
  // fread() the number of buckets in this hashtable from its
  // "num_buckets" field, and store in the "num_buckets_" member
  // variable.  (OK, one more reminder: network to host order!)

  // MISSING:

  // seek to "num_buckets" field's position
  Assert333(fseek(f, offset, SEEK_SET) == 0);
  uint32_t num_buckets_no;
  Assert333(fread(&num_buckets_no, sizeof(num_buckets_no), 1, f) == 1);
  num_buckets_ = ntohl(num_buckets_no);
}

HashTableReader::~HashTableReader() {
  // fclose our (FILE *).
  fclose(file_);
  file_ = NULL;
}

HashTableReader::HashTableReader(const HashTableReader &rhs) {
  // This is the copy constructor.

  // Duplicate the offset_, num_buckets_ fields.
  offset_ = rhs.offset_;
  num_buckets_ = rhs.num_buckets_;

  // FileDup() rhs's file_ into our own.
  file_ = FileDup(rhs.file_);
}

HashTableReader &HashTableReader::operator=(const HashTableReader &rhs) {
  // This is the assignment operator.

  if (this != &rhs) {
    // Duplicate the offset_, num_buckets_ fields.
    offset_ = rhs.offset_;
    num_buckets_ = rhs.num_buckets_;

    // Close out our current file_ (if it is open), and then FileDup()
    // rhs's file_ into our own.
    Assert333(file_ != NULL);
    Assert333(fclose(file_) == 0);
    file_ = FileDup(rhs.file_);
  }

  // Return a reference to self.
  return *this;
}

std::list<uint32_t>
HashTableReader::LookupElementPositions(uint64_t hashval) {
  // Figure out which bucket the hash value is in.  We assume
  // hash values are mapped to buckets using the modulo (%) operator.
  uint32_t bucket_num = hashval % num_buckets_;

  // Figure out the offset of the "bucket_rec" field for this bucket.
  uint32_t bucketrec_offset = (offset_ + 4) + 8 * bucket_num;

  // Read the "chain len" and "bucket position" fields from the
  // bucket_rec record, and convert from network to host order.
  uint32_t chain_len, bucket_position;
  // MISSING:

  // seek to bucket record position to read its fields
  Assert333(fseek(file_, bucketrec_offset, SEEK_SET) == 0);

  Assert333(fread(&chain_len, sizeof(chain_len), 1, file_) == 1);
  Assert333(fread(&bucket_position, sizeof(bucket_position), 1, file_) == 1);

  // convert "chain len" and "bucket position" to host order
  chain_len = ntohl(chain_len);
  bucket_position = ntohl(bucket_position);

  // This will be our returned list of element positions.
  std::list<uint32_t> retval;

  // If the bucket is empty, return the empty list.
  if (chain_len == 0) {
    return retval;
  }

  // Read the "element positions" fields from the "bucket" header into
  // the returned list.  Be sure to insert into the list in the
  // correct order (i.e., append to the end of the list).
  // MISSING:

  // seek to the bucket position to read
  Assert333(fseek(file_, bucket_position, SEEK_SET) == 0);
  uint32_t pos, i;
  for (i = 0; i < chain_len; i++) {
    Assert333(fread(&pos, sizeof(pos), 1, file_) == 1);

    // convert pos to host order
    pos = ntohl(pos);
    retval.push_back(pos);
  }

  // Return the list.
  return retval;
}

}  // namespace hw3
