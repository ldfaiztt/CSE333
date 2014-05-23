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

#ifndef _HW3_HASHTABLEREADER_H_
#define _HW3_HASHTABLEREADER_H_

#include <stdint.h>  // for uint32_t, etc.
#include <cstdio>    // for (FILE *).
#include <list>      // for std::list.

namespace hw3 {

// A HashTableReader is the base class for the different kinds
// of hash table readers.  Its subclasses are the DocTableReader, the
// IndexTableReader, and the DocPositionsReader.
class HashTableReader {
  // This friend declaration is here so that the Test_HashTableReader
  // unit test fixture can access protected member variables of
  // HashTableReader.  See test_hashtablereader.h for details.
  friend class Test_HashTableReader;

 public:
  // Construct a HashTableReader reader.  Arguments:
  //
  // - f: an open (FILE *) for the underlying index file.  The
  //   constructed object takes ownership of the (FILE *) and will
  //   fclose() it on destruction.
  //
  // - offset: the hash table's byte offset within the file.
  HashTableReader(FILE *f, uint32_t offset);
  ~HashTableReader();

  // We have to implement a copy constructor and assignment operator
  // to manage the (FILE *) that instances of HashTableReader use.
  // If somebody uses a copy constructor to manufactur a new
  // HashTableReader or the assignment operator to assign to an
  // existing one from another HashTableReader, we want to duplicate
  // the (FILE *) so that the right fclose()-on-destruction behavior
  // takes place.
  HashTableReader(const HashTableReader &rhs);
  HashTableReader &operator=(const HashTableReader &rhs);

  // Given a 64-bit hash value, this function navigates through
  // the on-disk hash table and returns a list of file offsets of
  // "element" fields within the bucket that the hash value maps to.
  // Only subclasses may invoke this.
  //
  // Arguments:
  //
  // - hashval: the 64-bit hash value to look up.
  //
  // Returns:
  //
  // - A list of offsets of "element" fields inside the bucket that
  //   the hash value maps to.  If no elements are in the  bucket,
  //   this returns an empty list.
  std::list<uint32_t> LookupElementPositions(uint64_t hashval);

 protected:
  // The open (FILE *) stream associated with this hash table.
  FILE *file_;

  // The byte offset within the file that this hash table starts at.
  uint32_t offset_;

  // A cached copy of the total number of buckets in this hash table.
  uint32_t num_buckets_;
};

}  // namespace hw3

#endif  // _HW3_HASHTABLEREADER_H_
