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

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

extern "C" {
  #include "./memindex.h"
  #include "./filecrawler.h"
}

#include "./test_suite.h"
#include "./test_memindex.h"

namespace hw2 {

TEST_F(Test_MemIndex, MITestSimple) {
  int res;
  DocTable dt;
  MemIndex idx;
  LinkedList llres;
  LLIter lit;
  unsigned int i;

  const char *q1[] = {"equations"};
  const char *q2[] = {"report", "normal"};
  const char *q3[] = {"report", "suggestions", "normal"};
  const char *q4[] = {"report", "normal", "foobarbaz"};

  // Crawl part of the file tree.
  res = CrawlFileTree(const_cast<char *>("./test_tree/bash-4.2/support"),
                      &dt, &idx);
  ASSERT_EQ(res, 1);
  ASSERT_EQ(MINumWordsInMemIndex(idx), 3852U);

  // Process query 1, check results.
  llres = MIProcessQuery(idx, const_cast<char **>(q1), 1);
  ASSERT_NE((LinkedList) NULL, llres);
  ASSERT_EQ(NumElementsInLinkedList(llres), 2U);
  lit = LLMakeIterator(llres, 0);
  for (i = 0; i < NumElementsInLinkedList(llres); i++) {
    SearchResult *res;

    LLIteratorGetPayload(lit, reinterpret_cast<void **>(&res));
    if (i == 0) {
      char *docname = DTLookupDocID(dt, res->docid);
      ASSERT_EQ(
         strcmp(docname,
                "./test_tree/bash-4.2/support/texi2html"), 0);
    } else if (i == 1) {
      char *docname = DTLookupDocID(dt, res->docid);
      ASSERT_EQ(
         strcmp(docname,
                "./test_tree/bash-4.2/support/man2html.c"), 0);
    }
    LLIteratorNext(lit);
  }
  LLIteratorFree(lit);
  FreeLinkedList(llres, &free);
  HW2Addpoints(20);

  // Process query 2, check results.
  llres = MIProcessQuery(idx, const_cast<char **>(q2), 2);
  ASSERT_NE((LinkedList) NULL, llres);
  ASSERT_EQ(NumElementsInLinkedList(llres), 2U);
  lit = LLMakeIterator(llres, 0);
  for (i = 0; i < NumElementsInLinkedList(llres); i++) {
    SearchResult *res;

    LLIteratorGetPayload(lit, reinterpret_cast<void **>(&res));
    if (i == 0) {
      char *docname = DTLookupDocID(dt, res->docid);
      ASSERT_EQ(
         strcmp(docname,
                "./test_tree/bash-4.2/support/texi2html"), 0);
    } else if (i == 1) {
      char *docname = DTLookupDocID(dt, res->docid);
      ASSERT_EQ(
         strcmp(docname,
                "./test_tree/bash-4.2/support/man2html.c"), 0);
    }
    LLIteratorNext(lit);
  }
  LLIteratorFree(lit);
  FreeLinkedList(llres, &free);
  HW2Addpoints(20);

  // Process query 3, check results.
  llres = MIProcessQuery(idx, const_cast<char **>(q3), 3);
  ASSERT_NE((LinkedList) NULL, llres);
  ASSERT_EQ(NumElementsInLinkedList(llres), 1U);
  lit = LLMakeIterator(llres, 0);
  for (i = 0; i < NumElementsInLinkedList(llres); i++) {
    SearchResult *res;

    LLIteratorGetPayload(lit, reinterpret_cast<void **>(&res));
    if (i == 0) {
      char *docname = DTLookupDocID(dt, res->docid);
      ASSERT_EQ(
         strcmp(docname,
                "./test_tree/bash-4.2/support/texi2html"), 0);
    }
    LLIteratorNext(lit);
  }
  LLIteratorFree(lit);
  FreeLinkedList(llres, &free);
  HW2Addpoints(20);

  // Process query 4, check results.
  llres = MIProcessQuery(idx, const_cast<char **>(q4), 3);
  ASSERT_EQ((LinkedList) NULL, llres);
  HW2Addpoints(20);

  // Free up everything.
  FreeDocTable(dt);
  FreeMemIndex(idx);
  HW2Addpoints(10);
}

}  // namespace hw2
