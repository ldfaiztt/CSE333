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
#include "./test_doctablereader.h"
#include "./test_suite.h"

extern "C" {
#include "libhw1/HashTable.h"
}

namespace hw3 {

TEST_F(Test_DocTableReader, TestDocTableReaderBasic) {
  // Open up the FILE * for ./unit_test_indices/enron.idx
  std::string idx("./unit_test_indices/enron.idx");
  FILE *f = fopen(idx.c_str(), "rb");
  ASSERT_NE(static_cast<FILE *>(NULL), f);

  // Prep the DocTableReader; the docid-->docname table is at
  // offset FILEINDEX_HEADER_SIZE.
  DocTableReader dtr(f, FILEINDEX_HEADER_SIZE);

  // Do a couple of bucket lookups, just to make sure we're
  // inheriting LookupElementPositions correctly.
  std::list<uint32_t> res = LookupElementPositions(&dtr, 5);
  ASSERT_GT(res.size(), (unsigned int) 0);

  res = LookupElementPositions(&dtr, 6);
  ASSERT_GT(res.size(), (unsigned int) 0);

  // Try some docid-->string lookups.  Start by trying two that
  // should exist.
  std::string str;
  bool success = dtr.LookupDocID(5, &str);
  ASSERT_TRUE(success);
  ASSERT_EQ(std::string("test_tree/enron_email/102."),
            str);
  success = dtr.LookupDocID(55, &str);
  ASSERT_TRUE(success);
  ASSERT_EQ(std::string("test_tree/enron_email/149."),
            str);

  // Lookup a docid that shouldn't exist.
  success = dtr.LookupDocID(100000, &str);
  ASSERT_FALSE(success);

  // Done!
  HW3Addpoints(30);
}

}  // namespace hw3
