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
#include <iostream>
#include <algorithm>

#include "./fileindexutil.h"
#include "./IndexTableReader.h"
#include "./test_docidtablereader.h"
#include "./test_suite.h"

extern "C" {
  #include "libhw1/Assert333.h"
}

namespace hw3 {

TEST_F(Test_DocIDTableReader, TestDocIDTableReaderBasic) {
  // This is a tough unit test to write, since we can't assume
  // much about where in an index file a DocIDTable lives.
  // So, we violate a little bit of the unit testing credo and
  // fold in a different module as a dependency: we make use of the
  // IndexTableReader class.

  // Open up the FILE * for ./unit_test_indices/enron.idx
  std::string idx("./unit_test_indices/enron.idx");
  FILE *f = fopen(idx.c_str(), "rb");
  ASSERT_NE(static_cast<FILE *>(NULL), f);

  // Read in the size of the doctable.
  Assert333(fseek(f, DTSIZE_OFFSET, SEEK_SET) == 0);
  uint32_t doctable_size;
  Assert333(fread(&doctable_size, 4, 1, f) == 1);
  doctable_size = ntohl(doctable_size);

  // Prep an IndexTableReader; the word-->docid table is at offset
  // FILEINDEX_HEADER_SIZE + doctable_size
  IndexTableReader itr(f, FILEINDEX_HEADER_SIZE + doctable_size);

  // Use the IndexTableReader to manufacture a DocIDTableReader.
  DocIDTableReader *ditr = itr.LookupWord(std::string("happy"));
  ASSERT_NE(static_cast<DocIDTableReader *>(NULL), ditr);

  // Use the DocIDTableReader to look for matching docids.
  std::list<uint32_t> matchlist;
  bool success = ditr->LookupDocID(604, &matchlist);
  ASSERT_TRUE(success);
  ASSERT_EQ((unsigned int) 2, matchlist.size());

  matchlist.clear();
  success = ditr->LookupDocID(613, &matchlist);
  ASSERT_TRUE(success);
  ASSERT_EQ((unsigned int) 1, matchlist.size());

  matchlist.clear();
  success = ditr->LookupDocID(37, &matchlist);
  ASSERT_TRUE(success);
  ASSERT_EQ((unsigned int) 1, matchlist.size());

  // Lookup a docID that shouldn't exist.
  matchlist.clear();
  success = ditr->LookupDocID(100000, &matchlist);
  ASSERT_FALSE(success);
  ASSERT_EQ((unsigned int) 0, matchlist.size());

  // Clean up.
  delete ditr;

  // Done!
  HW3Addpoints(30);
}

}  // namespace hw3
