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

#include <sys/types.h>  // for stat()
#include <sys/stat.h>   // for stat()
#include <unistd.h>     // for stat()

#include "./fileindexutil.h"   // for class CRC32.
#include "./FileIndexReader.h"

extern "C" {
  #include "libhw1/Assert333.h"
}

namespace hw3 {

FileIndexReader::FileIndexReader(std::string filename,
                                 bool validate) {
  // Stash a copy of the index file's name.
  filename_ = filename;

  // Open a (FILE *) associated with filename.  Crash on error.
  file_ = fopen(filename_.c_str(), "rb");
  Assert333(file_ != NULL);

  // Make the (FILE *) be unbuffered.  ("man setbuf")
  // MISSING:
  setbuf(file_, NULL);

  // Read the magic number header field from the index file, verify
  // that it is correct.  Crash if not.
  uint32_t magic_number;
  // MISSING:
  Assert333(fread(&magic_number, sizeof(magic_number), 1, file_) == 1);

  // convert magic number to host order
  magic_number = ntohl(magic_number);
  Assert333(magic_number == 0xCAFEF00D);

  // Read the checksum header field from the index file.
  uint32_t checksum;
  // MISSING:
  Assert333(fread(&checksum, sizeof(checksum), 1, file_) == 1);

  // convert checksum to host order
  checksum = ntohl(checksum);

  // Read the doctable size field from the index file, and store
  // it in the doctable_size_ member variable of this object instance.
  // (We're not going to remind you to convert between network and
  // host order any more; you'll have to remember to do it yourself
  // in the right locations from now on.)
  // MISSING:
  uint32_t doctable_size_no;
  Assert333(fread(&doctable_size_no, sizeof(doctable_size_no), 1, file_) == 1);

  // convert doctable size to host order
  doctable_size_ = ntohl(doctable_size_no);

  // Read the index size field from the index file and store it in the
  // index_size_ member variable.
  // MISSING:
  uint32_t index_size_no;
  Assert333(fread(&index_size_no, sizeof(index_size_no), 1, file_) == 1);

  // convert index size to host order
  index_size_ = ntohl(index_size_no);

  // Make sure the index file's length lines up with the header fields.
  struct stat f_stat;
  Assert333(stat(filename_.c_str(), &f_stat) == 0);
  Assert333((uint32_t) f_stat.st_size ==
            (uint32_t) (FILEINDEX_HEADER_SIZE +
                        doctable_size_ +
                        index_size_));

  if (validate) {
    // Re-calculate the checksum, make sure it matches that in the header.
    // Use fread() to read the checksum and pass the bytes you read into
    // the crcobj.  Note you don't need to do any host/network order
    // conversion, since we're doing this byte-by-byte.
    CRC32 crcobj;
    uint8_t buf[512];
    uint32_t left_to_read = doctable_size_ + index_size_;
    uint32_t byte_read, i;
    while (left_to_read > 0) {
      // MISSING:
      byte_read = fread(reinterpret_cast<void *>(buf), 1, 512, file_);
      left_to_read -= byte_read;

      for (i = 0; i < byte_read; i++)
        crcobj.FoldByteIntoCRC(buf[i]);
    }
    Assert333(crcobj.GetFinalCRC() == checksum);
  }

  // Everthing looks good; we're done!
}

FileIndexReader::~FileIndexReader() {
  // Close the (FILE *).
  Assert333(fclose(file_) == 0);
}

DocTableReader FileIndexReader::GetDocTableReader() {
  // The docid->name mapping starts at offset FILEINDEX_HEADER_SIZE in
  // the index file.  Be sure to dup the (FILE *) rather than sharing
  // it across objects, just so that we don't end up with the possibility
  // of threads contending for the (FILE *) and associated with race
  // conditions.
  return DocTableReader(FileDup(file_), FILEINDEX_HEADER_SIZE);
}

IndexTableReader FileIndexReader::GetIndexTableReader() {
  // The index (word-->docid table) mapping starts at offset
  // (FILEINDEX_HEADER_SIZE + doctable_size_) in the index file.  Be
  // sure to dup the (FILE *) rather than sharing it across objects,
  // just so that we don't end up with the possibility of threads
  // contending for the (FILE *) and associated race conditions.
  return IndexTableReader(FileDup(file_),
                          FILEINDEX_HEADER_SIZE + doctable_size_);
}

}  // namespace hw3
