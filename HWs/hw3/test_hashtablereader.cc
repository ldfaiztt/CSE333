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
#include "./test_hashtablereader.h"
#include "./test_suite.h"

namespace hw3 {

TEST_F(Test_HashTableReader, TestHashTableReaderBasic) {
  // Open up the FILE * for ./unit_test_indices/enron.idx
  std::string idx("./unit_test_indices/enron.idx");
  FILE *f = fopen(idx.c_str(), "rb");
  ASSERT_NE(static_cast<FILE *>(NULL), f);

  // Prep the HashTableReader to point to the docid-->docname table,
  // which is at offset FILEINDEX_HEADER_SIZE in the file.
  HashTableReader htr(f, FILEINDEX_HEADER_SIZE);

  // Do a couple of bucket lookups.
  std::list<uint32_t> res = htr.LookupElementPositions(5);
  ASSERT_GT(res.size(), (unsigned int) 0);

  res = htr.LookupElementPositions(6);
  ASSERT_GT(res.size(), (unsigned int) 0);

  // Done!
  HW3Addpoints(20);
}

}  // namespace hw3
