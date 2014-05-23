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
#include <assert.h>

extern "C" {
  #include "./fileparser.h"
}

#include "./test_suite.h"
#include "./test_fileparser.h"

namespace hw2 {

TEST_F(Test_FileParser, FPTestReadFile) {
  char *filebuf = NULL;
  uint64_t len = 0;

  // read a big file
  filebuf = ReadFile(const_cast<char *>("./test_tree/books/paradiselost.txt"),
                     &len);
  ASSERT_NE(static_cast<char *>(NULL), filebuf);
  ASSERT_EQ(len, 495687U);
  ASSERT_EQ(filebuf[0], 'T');
  ASSERT_EQ(filebuf[495686], static_cast<char>(0x0a));
  free(filebuf);
  HW2Addpoints(10);

  // try to read a non-existent file
  filebuf = ReadFile(const_cast<char *>("bogus/file"), &len);
  ASSERT_EQ(static_cast<char *>(NULL), filebuf);
  HW2Addpoints(10);

  // read a small file
  filebuf = ReadFile(const_cast<char *>("./test_tree/bash-4.2/trap.h"), &len);
  ASSERT_NE(static_cast<char *>(NULL), filebuf);
  ASSERT_EQ(len, 3213U);
  ASSERT_EQ(filebuf[0], '/');
  ASSERT_EQ(filebuf[3212], static_cast<char>(0x0a));
  free(filebuf);
  HW2Addpoints(10);

  // try to read a file that contains non-ASCII text
  filebuf = ReadFile(const_cast<char *>("./test_tree./libhw1.a"), &len);
  ASSERT_EQ(static_cast<char *>(NULL), filebuf);
  HW2Addpoints(10);
}

TEST_F(Test_FileParser, FPTestBuildWordHT) {
  HashTable tab =
    BuildWordHT(const_cast<char *>("./test_tree/bash-4.2/doc/README"));
  ASSERT_NE(static_cast<HashTable>(NULL), tab);
  ASSERT_EQ(NumElementsInHashTable(tab), 91U);
  HW2Addpoints(10);

  // Do a few spot checks.
  {
    // article: 154, 170; identical: 918; versions: 499, 550, 653.
    const char *w1 = "article", *w2 = "identical", *w3 = "versions";
    HTKeyValue kv;
    int retval;
    WordPositions *wp;
    uint32_t pos;

    retval = LookupHashTable(tab,
                             FNVHash64((unsigned char *) w1, strlen(w1)),
                             &kv);
    ASSERT_EQ(retval, 1);
    wp = static_cast<WordPositions *>(kv.value);
    ASSERT_EQ(strcmp(w1, wp->word), 0);
    ASSERT_EQ(NumElementsInLinkedList(wp->positions), 2U);
    retval = PopLinkedList(wp->positions, reinterpret_cast<void **>(&pos));
    ASSERT_EQ(retval, 1);
    ASSERT_EQ(pos, 154U);
    retval = PopLinkedList(wp->positions, reinterpret_cast<void **>(&pos));
    ASSERT_EQ(retval, 1);
    ASSERT_EQ(pos, 170U);
    HW2Addpoints(10);

    retval = LookupHashTable(tab,
                             FNVHash64((unsigned char *) w2, strlen(w2)),
                             &kv);
    ASSERT_EQ(retval, 1);
    wp = static_cast<WordPositions *>(kv.value);
    ASSERT_EQ(strcmp(w2, wp->word), 0);
    ASSERT_EQ(NumElementsInLinkedList(wp->positions), 1U);
    retval = PopLinkedList(wp->positions, reinterpret_cast<void **>(&pos));
    ASSERT_EQ(retval, 1);
    ASSERT_EQ(pos, 918U);
    HW2Addpoints(10);

    retval = LookupHashTable(tab,
                             FNVHash64((unsigned char *) w3, strlen(w3)),
                             &kv);
    ASSERT_EQ(retval, 1);
    wp = static_cast<WordPositions *>(kv.value);
    ASSERT_EQ(strcmp(w3, wp->word), 0);
    ASSERT_EQ(NumElementsInLinkedList(wp->positions), 3U);
    retval = PopLinkedList(wp->positions, reinterpret_cast<void **>(&pos));
    ASSERT_EQ(retval, 1);
    ASSERT_EQ(pos, 499U);
    retval = PopLinkedList(wp->positions, reinterpret_cast<void **>(&pos));
    ASSERT_EQ(retval, 1);
    ASSERT_EQ(pos, 550U);
    retval = PopLinkedList(wp->positions, reinterpret_cast<void **>(&pos));
    ASSERT_EQ(retval, 1);
    ASSERT_EQ(pos, 653U);
    HW2Addpoints(10);

    retval = LookupHashTable(tab,
                             FNVHash64((unsigned char *) "blah", 4),
                             &kv);
    ASSERT_EQ(retval, 0);
    HW2Addpoints(10);
  }

  FreeWordHT(tab);
  HW2Addpoints(10);
}

TEST_F(Test_FileParser, PTestBigBuildWordHT) {
  HashTable tab =
    BuildWordHT(const_cast<char *>("./test_tree/books/paradiselost.txt"));
  ASSERT_NE(static_cast<HashTable>(NULL), tab);
  ASSERT_EQ(NumElementsInHashTable(tab), 10123U);
  FreeWordHT(tab);
  HW2Addpoints(10);
}

}  // namespace hw2
