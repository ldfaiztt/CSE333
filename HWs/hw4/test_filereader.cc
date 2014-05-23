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

#include "./test_suite.h"
#include "./test_filereader.h"

#include "./FileReader.h"

using std::string;

namespace hw4 {

TEST_F(Test_FileReader, TestFileReaderBasic) {
  // See if we can read a file successfully.
  FileReader f(".", "test_files/hextext.txt");
  std::string contents;
  ASSERT_TRUE(f.ReadFile(&contents));
  ASSERT_EQ(4800U, contents.size());
  HW4Addpoints(10);

  // Make sure reading a non-existent file fails.
  f = FileReader(".", "non-existent");
  ASSERT_FALSE(f.ReadFile(&contents));
  HW4Addpoints(5);

  // Make sure a file path attack fails.
  f = FileReader("./libhw2", "./libhw2/../cpplint.py");
  ASSERT_FALSE(f.ReadFile(&contents));
  HW4Addpoints(5);
}

}  // namespace hw4
