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

#include <assert.h>     // for assert
#include <sys/types.h>  // for stat()
#include <sys/stat.h>   // for stat()
#include <unistd.h>     // for stat()
#include <iostream>     // for cout, endl

#include "./fileindexutil.h"   // for class CRC32.
#include "./FileIndexChecker.h"
#include "./DocTableChecker.h"
#include "./IndexTableChecker.h"

using std::cout;
using std::endl;

namespace hw3 {

FileIndexChecker::FileIndexChecker(std::string filename) {
  // Stash a copy of the index file's name.
  filename_ = filename;
  cout << "hw3fsck'ing " << filename_ << endl;
  cout << hex;

  // Open a (FILE *) associated with filename.  Crash on error.
  file_ = fopen(filename_.c_str(), "rb");
  assert(file_ != NULL);

  // Make the (FILE *) be unbuffered.  ("man setbuf")
  setbuf(file_, NULL);

  cout << "  checking the header..." << endl;
  UpdateGlobals(to_string("header"));

  // Read the magic number header field from the index file, verify
  // that it is correct.  Warn if not.
  cout << "    checking the magic number..." << endl;
  UpdateGlobals(to_string("magic number"));
  uint32_t magic_number;
  assert(fseek(file_, MAGIC_NUMBER_OFFSET, SEEK_SET) == 0);
  assert(fread(&magic_number, 4, 1, file_) == 1);
  magic_number = ntohl(magic_number);
  Check32(MAGIC_NUMBER, magic_number, "magic number");

  // Read the checksum header field from the index file.
  uint32_t checksum;
  assert(fread(&checksum, 4, 1, file_) == 1);
  checksum = ntohl(checksum);

  // Read the doctable size field from the index file.
  assert(fread(&doctable_size_, 4, 1, file_) == 1);
  doctable_size_ = ntohl(doctable_size_);

  // Read the index size field from the index file.
  assert(fread(&index_size_, 4, 1, file_) == 1);
  index_size_ = ntohl(index_size_);

  // Make sure the index file's length lines up with the header fields.
  cout << "    checking file size against table offsets..." << endl;
  struct stat f_stat;
  assert(stat(filename_.c_str(), &f_stat) == 0);
  Check32(((uint32_t) f_stat.st_size) - FILEINDEX_HEADER_SIZE,
          doctable_size_ + index_size_,
          "doctable_size + index_size");
  if ((ntohl(doctable_size_) + ntohl(index_size_)) ==
      ((uint32_t) f_stat.st_size) - FILEINDEX_HEADER_SIZE) {
    cout << "Note: you likely forgot an endianness conversion, ";
    cout << "since ntohl(doctable_size_) + ntohl(index_size_) == ";
    cout << "filesize - 16" << endl;
  }

  // Re-calculate the checksum, make sure it matches that in the header.
  cout << "    recalculating the checksum..." << endl;
  CRC32 crcobj;
  uint8_t buf[512];
  uint32_t left_to_read =
    ((uint32_t) f_stat.st_size) - FILEINDEX_HEADER_SIZE;
  while (left_to_read > 0) {
    uint32_t readlen = fread(&buf[0], 1, 512, file_);
    assert(readlen > 0);
    for (uint32_t i = 0; i < readlen; i++)
      crcobj.FoldByteIntoCRC(buf[i]);
    left_to_read -= readlen;
  }
  Check32(crcobj.GetFinalCRC(), checksum, "checksum");

  // Everthing looks good; move on to the table checking?
  cout << "  checking the doctable..." << endl;
  DocTableChecker dtc(FileDup(file_),
                      FILEINDEX_HEADER_SIZE,
                      doctable_size_);
  dtc.Check(FILEINDEX_HEADER_SIZE, doctable_size_);

  cout << "  checking the index table..." << endl;
  IndexTableChecker itc(FileDup(file_),
                        FILEINDEX_HEADER_SIZE + doctable_size_,
                        index_size_);
  itc.Check(FILEINDEX_HEADER_SIZE + doctable_size_, index_size_);
}

FileIndexChecker::~FileIndexChecker() {
  // Close the (FILE *).
  assert(fclose(file_) == 0);
}

}  // namespace hw3
