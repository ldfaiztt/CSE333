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

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string>

#include "./test_suite.h"
#include "./HttpUtils.h"

#include "./test_httputils.h"

using std::string;

namespace hw4 {

TEST_F(Test_HttpUtils, TestHttpUtilsURIDecode) {
  // Test out URIDecoding.
  string empty("");
  string plain("foo");
  string two("%74%77%6f");
  string twoupper("%74%77%6F");
  string nope("%16nope");
  string broken("%broken%1");
  string spacey("%20+blah blah");
  ASSERT_EQ(string(""), URIDecode(empty));
  ASSERT_EQ(string("foo"), URIDecode(plain));
  ASSERT_EQ(string("two"), URIDecode(two));
  ASSERT_EQ(string("two"), URIDecode(twoupper));
  ASSERT_EQ(string("%16nope"), URIDecode(nope));
  ASSERT_EQ(string("%broken%1"), URIDecode(broken));
  ASSERT_EQ(string("  blah blah"), URIDecode(spacey));
}

TEST_F(Test_HttpUtils, TestHttpUtilsURLParser) {
  // Test out URL parsing.
  string easy("/foo/bar");
  string tricky("/foo/bar?");
  string query("/foo/bar?foo=blah+blah");
  string many("/foo/bar?foo=bar&bam=baz");
  string manyshort("/foo/bar?foo=%22bar%22&bam=baz");

  URLParser p;
  p.Parse(easy);
  ASSERT_EQ("/foo/bar", p.get_path());
  ASSERT_EQ((unsigned) 0, p.get_args().size());

  p.Parse(tricky);
  ASSERT_EQ("/foo/bar", p.get_path());
  ASSERT_EQ((unsigned) 0, p.get_args().size());

  p.Parse(query);
  ASSERT_EQ("/foo/bar", p.get_path());
  ASSERT_EQ((unsigned) 1, p.get_args().size());
  ASSERT_EQ("blah blah", p.get_args()["foo"]);

  p.Parse(many);
  ASSERT_EQ("/foo/bar", p.get_path());
  ASSERT_EQ((unsigned) 2, p.get_args().size());
  ASSERT_EQ("bar", p.get_args()["foo"]);
  ASSERT_EQ("baz", p.get_args()["bam"]);

  p.Parse(manyshort);
  ASSERT_EQ("/foo/bar", p.get_path());
  ASSERT_EQ((unsigned) 2, p.get_args().size());
  ASSERT_EQ("\"bar\"", p.get_args()["foo"]);
  ASSERT_EQ("baz", p.get_args()["bam"]);

  HW4Addpoints(20);
}

TEST_F(Test_HttpUtils, TestHttpUtilsIsPathSafe) {
  std::string basedir = "test_files/ok";
  std::string file1_ok = "test_files/ok/./bar";
  std::string file2_ok = "test_files/ok/baz/../bar";
  std::string file3_ok = "test_files/ok/../ok/baz";
  std::string file4_bad = "test_files/ok/../bad";
  std::string file5_bad = "test_files/ok/./..";
  std::string file6_bad = "//etc/passwd";

  ASSERT_TRUE(IsPathSafe(basedir, file1_ok));
  ASSERT_TRUE(IsPathSafe(basedir, file2_ok));
  ASSERT_TRUE(IsPathSafe(basedir, file3_ok));
  ASSERT_FALSE(IsPathSafe(basedir, file4_bad));
  ASSERT_FALSE(IsPathSafe(basedir, file5_bad));
  ASSERT_FALSE(IsPathSafe(basedir, file6_bad));
  HW4Addpoints(20);
}

TEST_F(Test_HttpUtils, TestHttpUtilsWrappedReadWrite) {
  std::string filedata = "This is a test; this is only a test.\n";

  // Make sure the file we'll write/read is deleted.
  unlink("test_files/test.txt");

  // Open the file and write to it.
  int file_fd = open("test_files/test.txt",
                     O_RDWR | O_CREAT,
                     S_IRUSR | S_IWUSR);
  ASSERT_NE(-1, file_fd);
  ASSERT_EQ(static_cast<int>(filedata.size()),
            WrappedWrite(file_fd,
                         (unsigned char *) filedata.c_str(),
                         filedata.size()));
  close(file_fd);

  // Reopen the file and read it in.
  unsigned char readdata[64] = { 0 };
  file_fd = open("test_files/test.txt", O_RDONLY);
  ASSERT_NE(-1, file_fd);
  ASSERT_EQ(static_cast<int>(filedata.size()),
            WrappedRead(file_fd, readdata, filedata.size()));
  close(file_fd);
  std::string readstr((const char *) readdata);
  ASSERT_TRUE(readstr == filedata);

  // Delete the file.
  unlink("test_files/test.txt");
  HW4Addpoints(20);
}

}  // namespace hw4
