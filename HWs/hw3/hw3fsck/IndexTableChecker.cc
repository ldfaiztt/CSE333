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

#include <assert.h>     // for assert().
#include <arpa/inet.h>  // for ntohl(), ntohs().
#include <stdint.h>     // for uint32_t, etc.
#include <string>       // for std::string.
#include <iostream>     // for cout, etc.
#include <sstream>      // for std::stringstream.
#include <cctype>       // for isascii, etc.

#include "./fileindexutil.h"   // for FileDup().

extern "C" {
#include "../libhw1/HashTable.h"  // for libhw1/HashTable.h's FNVHash64().
}

#include "./IndexTableChecker.h"

using namespace std;

namespace hw3 {

// The constructor for IndexTableChecker calls the constructor of
// HashTableChecker(), its superclass. The superclass takes care of
// taking ownership of f and using it to extract and cache the number
// of buckets within the table.
IndexTableChecker::IndexTableChecker(FILE *f, uint32_t offset, uint32_t len)
  : HashTableChecker(f, offset, len) { }

void IndexTableChecker::CheckElement(uint32_t element_offset,
                                     uint32_t bucket_number) {
  UpdateGlobals("bucket_rec[", to_string(bucket_number), "]");

  // Read in the word length.
  uint16_t wordlen;
  assert(fseek(file_, element_offset, SEEK_SET) == 0);
  assert(fread(&wordlen, 2, 1, file_) == 1);
  wordlen = ntohs(wordlen);
  CheckLT16(wordlen, 8192, "[IndexTable] word length");

  // Read in the docID table length.
  uint32_t docidlen;
  assert(fread(&docidlen, 4, 1, file_) == 1);
  docidlen = ntohl(docidlen);
  CheckLT32(element_offset + 2 + 4 + wordlen, offset_ + len_,
          "[IndexTable] element end < indextable end");

  // Read in the word.
  char word[wordlen+1];
  word[wordlen] = '\0';
  assert(fread(&word[0], wordlen, 1, file_) == 1);

  // Make sure the word is all ascii and lower case.
  for (int i = 0; i < wordlen; i++) {
    uint16_t res = isascii(word[i]) ? 1 : 0;
    Check16(1, res,
            string(("[IndexTable] isascii(word)[" +
                    to_string(i) + "]")).c_str());
    if (!isalpha(word[i]))
      continue;
    res = islower(word[i]) ? 1 : 0;
    Check16(1, res,
            string(("[IndexTable] islower(word)[" +
                    to_string(i) + "]")).c_str());
  }

  UpdateGlobals(string("DocIDtable for word ") +
                word + ", embedded in bucket_rec[",
                to_string(bucket_number), "]");
  DocIDTableChecker ditc(FileDup(file_),
                         element_offset + 2 + 4 + wordlen,
                         docidlen);
  ditc.Check(element_offset + 2 + 4 + wordlen, docidlen);
}

}  // namespace hw3
