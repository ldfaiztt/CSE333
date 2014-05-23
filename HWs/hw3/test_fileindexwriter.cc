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

#include <unistd.h>
#include <sys/types.h>
#include <stdint.h>
#include <iostream>
#include <string>
#include <sstream>

#include "./test_fileindexwriter.h"
#include "./fileindexwriter.h"
#include "./test_suite.h"

namespace hw3 {

// Test our ability to write to a file index.
TEST_F(Test_FileIndexWriter, TestFileIndexWrite) {
  uint32_t mypid = (uint32_t) getpid();
  std::stringstream ss;
  ss << "/tmp/test." << mypid << ".index";
  std::string fname = ss.str();

  std::cout << "             " <<
    "Writing index " << mi_ << "out to " << fname << "..." << std::endl;
  uint32_t res = WriteIndex(mi_, dt_, fname.c_str());
  std::cout << "             " <<
    "...done writing." << std::endl;
  ASSERT_EQ(unlink(fname.c_str()), 0);
  ASSERT_LT((uint32_t) 100000, res);

  HW3Addpoints(20);
}

}  // namespace hw3
