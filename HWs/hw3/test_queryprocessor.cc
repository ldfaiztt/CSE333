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

#include <list>
#include <vector>
#include <string>

#include "./test_queryprocessor.h"
#include "./test_suite.h"

using std::list;
using std::vector;
using std::string;

namespace hw3 {

TEST_F(Test_QueryProcessor, TestQueryProcessorBasic) {
  // Set up the list of index files.
  list<string> idxlist;
  idxlist.push_back("./unit_test_indices/bash.idx");
  idxlist.push_back("./unit_test_indices/books.idx");
  idxlist.push_back("./unit_test_indices/enron.idx");

  // Construct the QueryProcessor.
  QueryProcessor qp(idxlist);

  // Try some queries.
  vector<string> query;
  query.push_back("whale");
  query.push_back("ocean");
  query.push_back("ravenous");

  vector<QueryProcessor::QueryResult> res = qp.ProcessQuery(query);
  ASSERT_EQ((unsigned int) 3, res.size());
  ASSERT_EQ(string("test_tree/books/mobydick.txt"), res[0].document_name);
  ASSERT_EQ((unsigned int) 1314, res[0].rank);
  ASSERT_EQ(string("test_tree/books/leavesofgrass.txt"),
            res[1].document_name);
  ASSERT_EQ((unsigned int) 42, res[1].rank);
  ASSERT_EQ(string("test_tree/books/ulysses.txt"), res[2].document_name);
  ASSERT_EQ((unsigned int) 15, res[2].rank);

  query.push_back("huckleberry");
  res = qp.ProcessQuery(query);
  ASSERT_EQ((unsigned int) 0, res.size());

  // Done!
  HW3Addpoints(20);
}

}  // namespace hw3
