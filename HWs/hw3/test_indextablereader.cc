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

#include <cstdio>

#include "./fileindexutil.h"
#include "./test_indextablereader.h"
#include "./test_suite.h"

extern "C" {
  #include "libhw1/HashTable.h"
  #include "libhw1/Assert333.h"
}

namespace hw3 {

TEST_F(Test_IndexTableReader, TestIndexTableReaderBasic) {
  // Open up the (FILE *) for ./unit_test_indices/enron.idx
  std::string idx("./unit_test_indices/enron.idx");
  FILE *f = fopen(idx.c_str(), "rb");
  ASSERT_NE(static_cast<FILE *>(NULL), f);

  // Read in the size of the doctable.
  Assert333(fseek(f, DTSIZE_OFFSET, SEEK_SET) == 0);
  uint32_t doctable_size;
  Assert333(fread(&doctable_size, 4, 1, f) == 1);
  doctable_size = ntohl(doctable_size);

  // Prep the IndexTableReader; the word-->docid_table table is at
  // offset FILEINDEX_HEADER_SIZE + doctable_size.
  IndexTableReader itr(f, FILEINDEX_HEADER_SIZE + doctable_size);

  // Do a couple of bucket lookups, just to make sure we're
  // inheriting LookupElementPositions correctly.
  uint64_t h1 = FNVHash64((unsigned char *) "anyway", 6);
  std::list<uint32_t> res = LookupElementPositions(&itr, h1);
  ASSERT_GT(res.size(), (unsigned int) 0);

  uint64_t h2 = FNVHash64((unsigned char *) "attachment", 10);
  res = LookupElementPositions(&itr, h2);
  ASSERT_GT(res.size(), (unsigned int) 0);

  // The unit test test_docidtablereader.cc exercises the
  // IndexTableReader's LookupWord() method, so we won't replicate that
  // here.
  //
  // Done!
  HW3Addpoints(30);
}

}  // namespace hw3
