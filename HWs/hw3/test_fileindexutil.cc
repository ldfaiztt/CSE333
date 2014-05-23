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

#include "./test_fileindexutil.h"
#include "./fileindexutil.h"
#include "./test_suite.h"

namespace hw3 {

// This is the unit test for the 32-bit CRC calculation.
TEST_F(Test_FileIndexUtil, TestCRC32) {
  CRC32 crc;

  // Calculate the CRC of (0x01, 0x02, 0x03, 0x04).  It should be
  // the 32-bit unsigned number 0xB63CFBCD.
  crc.FoldByteIntoCRC((const uint8_t) 1);
  crc.FoldByteIntoCRC((const uint8_t) 2);
  crc.FoldByteIntoCRC((const uint8_t) 3);
  crc.FoldByteIntoCRC((const uint8_t) 4);
  ASSERT_EQ(((uint32_t) 0xB63CFBCD), crc.GetFinalCRC());
}

// This is the unit test for the htonll and ntohll macros.
TEST_F(Test_FileIndexUtil, TestHtonll) {
  uint64_t small = 0x01ULL;
  uint64_t medium = 0xFEDCBA98ULL;
  uint64_t large = 0x0100000000000000ULL;
  uint64_t giant = 0xFEDCBA9876543210ULL;
  uint64_t small_no, medium_no, large_no, giant_no;
  unsigned char *t;

  // Convert numbers to network order (i.e., big endian).
  small_no = htonll(small);
  medium_no = htonll(medium);
  large_no = htonll(large);
  giant_no = htonll(giant);

  // Verify they are in network order.
  t = (unsigned char *) &small_no;
  ASSERT_EQ((unsigned char) 0x00, t[0]);
  ASSERT_EQ((unsigned char) 0x00, t[1]);
  ASSERT_EQ((unsigned char) 0x00, t[6]);
  ASSERT_EQ((unsigned char) 0x01, t[7]);

  t = (unsigned char *) &medium_no;
  ASSERT_EQ((unsigned char) 0x00, t[0]);
  ASSERT_EQ((unsigned char) 0x00, t[1]);
  ASSERT_EQ((unsigned char) 0xBA, t[6]);
  ASSERT_EQ((unsigned char) 0x98, t[7]);

  t = (unsigned char *) &large_no;
  ASSERT_EQ((unsigned char) 0x01, t[0]);
  ASSERT_EQ((unsigned char) 0x00, t[1]);
  ASSERT_EQ((unsigned char) 0x00, t[6]);
  ASSERT_EQ((unsigned char) 0x00, t[7]);

  t = (unsigned char *) &giant_no;
  ASSERT_EQ((unsigned char) 0xFE, t[0]);
  ASSERT_EQ((unsigned char) 0xDC, t[1]);
  ASSERT_EQ((unsigned char) 0x32, t[6]);
  ASSERT_EQ((unsigned char) 0x10, t[7]);

  // Convert back to host order.
  small_no = htonll(small_no);
  medium_no = htonll(medium_no);
  large_no = htonll(large_no);
  giant_no = htonll(giant_no);

  // Ensure the conversion back to host order worked.
  ASSERT_EQ(small, small_no);
  ASSERT_EQ(medium, medium_no);
  ASSERT_EQ(large, large_no);
  ASSERT_EQ(giant, giant_no);
}

}  // namespace hw3
