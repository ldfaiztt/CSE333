/*
 * Copyright 2012 Steven Gribble
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
#include <string.h>

extern "C" {
  #include "./doctable.h"
}

#include "./test_suite.h"
#include "./test_doctable.h"

namespace hw2 {

TEST_F(Test_DocTable, DTTestSimple) {
  DocTable t1;
  const char *f1 = "foo/bar/baz.txt", *f2 = "bar/baz.txt";
  char *fres;
  uint64_t d1, d2, dres;

  t1 = AllocateDocTable();
  ASSERT_NE(static_cast<DocTable>(NULL), t1);
  ASSERT_EQ(0U, DTNumDocsInDocTable(t1));
  HW2Addpoints(5);

  d1 = DTRegisterDocumentName(t1, const_cast<char *>(f1));
  ASSERT_NE(0U, d1);
  ASSERT_EQ(1U, DTNumDocsInDocTable(t1));
  d2 = DTRegisterDocumentName(t1, const_cast<char *>(f2));
  ASSERT_NE(0U, d2);
  ASSERT_EQ(2U, DTNumDocsInDocTable(t1));
  HW2Addpoints(5);

  dres = DTRegisterDocumentName(t1, const_cast<char *>(f2));
  ASSERT_EQ(d2, dres);
  dres = DTRegisterDocumentName(t1, const_cast<char *>(f1));
  ASSERT_EQ(d1, dres);
  HW2Addpoints(5);

  dres = DTLookupDocumentName(t1, const_cast<char *>(f1));
  ASSERT_EQ(d1, dres);
  dres = DTLookupDocumentName(t1, const_cast<char *>("nonexistent/file"));
  ASSERT_EQ(0U, dres);
  fres = DTLookupDocID(t1, d1);
  ASSERT_EQ(0, strcmp(fres, f1));
  fres = DTLookupDocID(t1, static_cast<uint64_t>(0xDEADBEEF));
  ASSERT_EQ(static_cast<char *>(NULL), fres);
  HW2Addpoints(5);

  FreeDocTable(t1);
  HW2Addpoints(10);
}

}  // namespace hw2
