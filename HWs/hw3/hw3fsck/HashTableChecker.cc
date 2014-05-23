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

#include <iostream>
#include <arpa/inet.h>        // for ntohl().
#include <assert.h>           // for assert().
#include "./fileindexutil.h"  // for FileDup().

#include "./HashTableChecker.h"

using namespace std;

namespace hw3 {

HashTableChecker::HashTableChecker(FILE *f, uint32_t offset, uint32_t len)
  : file_(f), offset_(offset), len_(len) {
}

HashTableChecker::~HashTableChecker() {
  // fclose our (FILE *).
  fclose(file_);
  file_ = NULL;
}

HashTableChecker::HashTableChecker(const HashTableChecker &rhs) {
  // This is the copy constructor.

  // Duplicate the offset_, num_buckets_ fields.
  offset_ = rhs.offset_;
  num_buckets_ = rhs.num_buckets_;

  // FileDup() rhs's file_ into our own.
  file_ = FileDup(rhs.file_);
}

HashTableChecker &HashTableChecker::operator=(const HashTableChecker &rhs) {
  // This is the assignment operator.

  if (this != &rhs) {
    // Duplicate the offset_, num_buckets_ fields.
    offset_ = rhs.offset_;
    num_buckets_ = rhs.num_buckets_;

    // Close out our current file_ (if it is open), and then FileDup()
    // rhs's file_ into our own.
    assert(file_ != NULL);
    assert(fclose(file_) == 0);
    file_ = FileDup(rhs.file_);
  }

  // Return a reference to self.
  return *this;
}

void HashTableChecker::Check(uint32_t offset, uint32_t len) {
  // fread() the number of buckets in this hashtable from its
  // "num_buckets" field. 
  assert(fseek(file_, offset_, SEEK_SET) == 0);
  assert(fread(&num_buckets_, 4, 1, file_) == 1);
  UpdateGlobals("num_buckets");

  // Convert the num_buckets_ from network (on-disk) representation to
  // host (in-memory) byte ordering using ntohl().
  num_buckets_ = ntohl(num_buckets_);

  // Check that the number of buckets is reasonable.
  CheckLT32(num_buckets_*8, len, "num_buckets < len(table)");

  // Loop through all of the bucket_recs, checking each bucket.
  bool foundfirstnonempty = false;
  uint32_t prevchainlen, prevbucket;

  for (uint32_t i = 0; i < num_buckets_; i++) {
    uint32_t curchainlen, curbucket;

    // read the bucket_rec
    UpdateGlobals("bucket_rec[", to_string(i), "]");
    assert(fseek(file_, offset_+4 + (8*i), SEEK_SET) == 0);
    assert(fread(&curchainlen, 4, 1, file_) == 1);
    assert(fread(&curbucket, 4, 1, file_) == 1);
    curchainlen = ntohl(curchainlen);
    curbucket = ntohl(curbucket);

    // check against prev bucket offset for sanity
    if (foundfirstnonempty && (curchainlen > 0)) {
      CheckLT32(prevbucket, curbucket,
                "bucket_rec[i].position < bucket_rec[i+1].position");
      prevchainlen = curchainlen;
      prevbucket = curbucket;
    }

    // if this is the first non-empty bucket, read its offset from the
    // bucket_rec to make sure it lines up with the number of
    // bucket_recs we have.
    if ((curchainlen > 0) && (!foundfirstnonempty)) {
      foundfirstnonempty = true;

      assert(fseek(file_, offset_+4, SEEK_SET) == 0);
      assert(fread(&prevchainlen, 4, 1, file_) == 1);
      prevchainlen = ntohl(prevchainlen);
      assert(fread(&prevbucket, 4, 1, file_) == 1);
      prevbucket = ntohl(prevbucket);
      Check32(offset_ + 4 + 8*num_buckets_, prevbucket,
              "position of the first bucket (expected to be "
              "(table start) + (4) + (8*num_buckets))");
    }

    // Seek to the bucket, make sure there are three element position
    // records that make sense.
    CheckLT32(curbucket, offset+len+1, "bucket position < table end+1");
    for (int j = 0; j < curchainlen; j++) {
      // read the element position
      UpdateGlobals("[bucket_num,element_num]=",
                    "[" + to_string(i) + "," +
                    to_string(j) + "]");
      uint32_t elementpos;
      assert(fseek(file_, curbucket + j*4, SEEK_SET) == 0);
      assert(fread(&elementpos, 4, 1, file_) == 1);
      elementpos = ntohl(elementpos);
      CheckLT32(elementpos, offset+len+1, "element position < table end+1");

      // read the element itself
      CheckElement(elementpos, i);
    }
  }
}

}  // namespace hw3
