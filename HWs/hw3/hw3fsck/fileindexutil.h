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

#ifndef _HW3_FILEINDEXUTIL_H_
#define _HW3_FILEINDEXUTIL_H_

#include <stdint.h>     // [C++ doesn't yet standardize <cstdint>.]
#include <arpa/inet.h>  // For htonl(), etc.
#include <unistd.h>     // for dup().
#include <cstdio>       // for fdopen(), (FILE *).
#include <string>       // for string.
#include <sstream>       // for stringstream

using namespace std;

// This header file declares a set of useful #defines, macros, utility
// functions, and utility classes that are used broadly within HW3.

namespace hw3 {

// These defines are used to avoid hard-coding the length of the file
// header and the offsets of fields within it.
#define FILEINDEX_HEADER_SIZE 16   // size of header
#define MAGIC_NUMBER_OFFSET 0      // offset of magic number
#define CHECKSUM_OFFSET 4          // offset of the checksum
#define DTSIZE_OFFSET 8            // offset of the doctable size field
#define IDXSIZE_OFFSET 12          // offset of the index size field

// This magic number is the first four bytes of a valid index file.
// The magic number is written to and index file last, and thus plays
// the role of a commit record.
#define MAGIC_NUMBER ((uint32_t) 0xCAFEF00D)

// We'll need to convert 64 bit integers from host order to big endian
// order and back, since we store content in big endian in files. The
// <arpa/inet.h> header declares routines for converting 16-bit and
// 32-bit numbers, but we need one for 64 bit numbers. ("man htonl").
// So, we define the following (crazy looking!) macros to do the
// 64-bit conversion.  Note that "network order" means big endian, and
// "host order" means whatever order the computer we're executing on
// is in.  So, htonll() means convert from host order to big endian;
// this has no side-effects on a big endian machine, but swaps the
// byte order on a little endian machine.
//
// Bonus marks for grokking what these macros do!  (Bonus bonus marks
// for grokking what "grok" means. ;)
#define ntohll(x) \
  ( ((uint64_t) (ntohl((uint32_t)((x << 32) >> 32) )) << 32) |   \
    ntohl(((uint32_t)(x >> 32))) )
#define htonll(x) (ntohll(x))

// A CRC32 object is used to calculate a checksum over a sequence of
// bytes.  A checksum is a mathematical operation that calculates a
// signature of some byte array; if the byte array gets corrupted, the
// checksum won't match, so it is used to validate the integrity of
// the byte array.  To calculate a checksum, instantiatea CRC32
// object and invoke FoldByteIntoCRC() repeatedly, once for each byte
// in the sequence.  Lastly, invoke GetFinalCRC() to retrieve the
// checksum for that byte sequence.  After you've called
// GetFinalCRC(), you cannot fold any additional bytes into that CRC32
// instance, so you probably want to dispose of it.
//
// If you're curious, you can read about CRCs on wikipedia:
//
//   http://en.wikipedia.org/wiki/Cyclic_redundancy_check
//
class CRC32 {
 public:
  CRC32(void);

  // Use this function to fold the next byte into the CRC.
  void FoldByteIntoCRC(const uint8_t nextbyte);

  // Once you're done folding bytes into the CRC, use this function to
  // get the final 32-bit CRC value.
  uint32_t GetFinalCRC(void);

 private:
  // Initialize the table_ to the appropriate values according to the
  // CRC32 algorithm.  Needs to be called once.
  void Initialize(void);

  // This private member variable holds the CRC calculation state.
  uint32_t crc_state_;

  // This bool indicates whether or not the CRC has been finalized.
  bool finalized_;

  // Here, the "static" specifier indicates that the variable table_,
  // which is an array of 256 uint32_t's, is associated  with the
  // CRC32 *class* rather than with each CRC32 object instance.  CRC32
  // object instances can access it, but there is a single copy of
  // this table_, no matter how many object instances exist.  C++
  // initializes the table to all zeroes.
  static uint32_t table_[256];

  // This indicates whether the static table_ has been initialized.
  static bool table_is_initialized_;
};

// This macro is a useful way of disabling copy constructors and
// assignment operators.  It should be used in the private:
// declarations for a class.  Lifted from Google's C++ style guide;
// thanks, Google!  (See DocTableReader.h for an example of how
// to use this.)
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)

// This function makes a copy of a (FILE *); it is helpful for
// avoiding potential race conditions involved with threads sharing a
// (FILE *), if you're dealing with multi-threaded code.
FILE *FileDup(FILE *f);

// Check16 checks a 16-bit field within the index file to compare
// its actual value against an expected value.  If they match,
// Check16 returns true.  If they don't match, Check16 returns
// false and prints a message based on fieldname.  As well, Check16
// also tests to see if the field is correct but swapped endianness,
// and adapts the error message if so.
//
// Check32 and Check64 are similar, but for 32-bit and 64-bit fields.
bool Check16(uint16_t expected, uint16_t actual, string fieldname);
bool Check32(uint32_t expected, uint32_t actual, string fieldname);
bool Check64(uint64_t expected, uint64_t actual, string fieldname);

// CheckLT16 checks a 16-bit field within the index file to compare
// its actual value against an expected value.  If expected < actual,
// CheckLT16 returns true.  If they don't match, CheckLT16 returns
// false and prints a message based on fieldname.
//
// CheckLT32 and CheckLT64 are similar, but for 32-bit and 64-bit fields.
bool CheckLT16(uint16_t smaller, uint16_t bigger, string fieldname);
bool CheckLT32(uint32_t smaller, uint32_t bigger, string fieldname);
bool CheckLT64(uint64_t smaller, uint64_t bigger, string fieldname);

// Update a set of global variables that Check* uses to print a nice
// status message.
void UpdateGlobals(string context1 = string(""),
                   string context2 = string(""),
                   string context3 = string(""));

template <class T> std::string to_string (const T& t) {
  std::stringstream ss;
  ss << t;
  return ss.str();
}

}  // namespace hw3

#endif  // _HW3_FILEINDEXUTIL_H_
