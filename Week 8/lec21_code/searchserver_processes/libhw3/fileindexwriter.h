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

#ifndef _HW3_FILEINDEXWRITER_H_
#define _HW3_FILEINDEXWRITER_H_

#include <stdint.h>  // [C++ doesn't yet standardize <cstdint>.]

// Include the HW1 LinkedList and HashTable headers, and the HW2
// MemIndex and DocTable headers.  We'll need these to access the
// routines in the libhw1.a and libhw2.a libraries.  Note that those
// libraries were compiled with gcc, and therefore have "C"-style
// linkage.  Since fileindexwriter.cc is compiled by g++, we need
// do use 'extern "C"' to tell g++ that the routines accessed through
// these header files were compiled with g++.
extern "C" {
  #include "libhw1/LinkedList.h"
  #include "libhw1/HashTable.h"
  #include "libhw2/memindex.h"
  #include "libhw2/doctable.h"
}

namespace hw3 {

// The WriteIndex() function writes the contents of a MemIndex and the
// docid_to_docname mapping of a DocTable into an index file.  The
// on-disk representation is defined in detail on the hw3 web page.
//
// Arguments:
//   - mi: the MemIndex to write into the index file.
//
//   - dt: the DocTable to write into the index file.
//
//   - filename: a C-style string containing the name of the index
//     file that we should create.
//
// Returns:
//   - the resulting size of the index file, in bytes, or 0 on error.
uint32_t WriteIndex(MemIndex mi, DocTable dt, const char *filename);

}  // namespace hw3

#endif  // _HW3_FILEINDEXWRITER_H_
