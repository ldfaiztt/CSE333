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

extern "C" {
  #include "./filecrawler.h"
  #include "./doctable.h"
  #include "./memindex.h"
}

#include "./test_suite.h"
#include "./test_filecrawler.h"

namespace hw2 {

TEST_F(Test_FileCrawler, FCTestSimple) {
  int res;
  DocTable dt;
  MemIndex idx;

  res = CrawlFileTree(const_cast<char *>("./test_tree/bash-4.2/support"),
                      &dt,
                      &idx);
  ASSERT_EQ(1, res);
  HW2Addpoints(10);
  FreeDocTable(dt);
  FreeMemIndex(idx);
  HW2Addpoints(10);

  res = CrawlFileTree(const_cast<char *>("./nonexistent/"), &dt, &idx);
  ASSERT_EQ(0, res);
  HW2Addpoints(10);
  res = CrawlFileTree(const_cast<char *>("./test_suite.c"), &dt, &idx);
  ASSERT_EQ(0, res);
  HW2Addpoints(10);
}

}  // namespace hw2

