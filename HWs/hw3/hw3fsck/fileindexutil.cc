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

#include <assert.h>  // for assert()
#include <iostream>  // for std::cout / std::endl

#include "./fileindexutil.h"

namespace hw3 {

// Initialize the "CRC32::table_is_initialized" static member variable.
bool CRC32::table_is_initialized_ = false;

// We need this declaration here so we can refer to the table_ below.
uint32_t CRC32::table_[256];

static uint32_t CRC32Reflect(uint32_t reflectme, const char c) {
  uint32_t val = 0;
  int position;

  // Swap bit 0 for bit 7, bit 1 For bit 6, etc....
  for (position = 1; position < (c + 1); position++) {
    if (reflectme & 1) {
      val |= (1 << (c - position));
    }
    reflectme >>= 1;
  }
  return val;
}

CRC32::CRC32(void) {
  if (!table_is_initialized_) {
    // Yes, there is a potential race condition if multiple threads
    // construct the very first CRC32() objects simultaneously.  We'll
    // live with it. ;)
    Initialize();
    table_is_initialized_ = true;
  }

  // Prep the CRC32 state.
  finalized_ = false;
  crc_state_ = 0xFFFFFFFF;
}

void CRC32::FoldByteIntoCRC(const uint8_t nextbyte) {
  assert(finalized_ != true);
  crc_state_ =
    (crc_state_ >> 8) ^ this->table_[(crc_state_ & 0xFF) ^ nextbyte];
}

uint32_t CRC32::GetFinalCRC(void) {
  if (!finalized_) {
    finalized_ = true;
    crc_state_ ^= 0xffffffff;
  }
  return crc_state_;
}

void CRC32::Initialize(void) {
  uint32_t polynomial = 0x04C11DB7;
  uint32_t codes, position;

  // Initialize the CRC32 lookup table; the table's 256 values
  // represent ASCII character codes.
  for (codes = 0; codes <= 0xFF; codes++) {
    CRC32::table_[codes] = CRC32Reflect(codes, 8) << 24;
    for (position = 0; position < 8; position++) {
      table_[codes] =
        (table_[codes] << 1) ^
        ((table_[codes] & (1 << 31)) ? polynomial : 0);
    }
    this->table_[codes] = CRC32Reflect(table_[codes], 32);
  }
}

FILE *FileDup(FILE *f) {
  // Duplicate the underlying file descriptor using dup().
  int newfd = dup(fileno(f));
  assert(newfd != -1);

  // Use fdopen() to open a new (FILE *) for the dup()'ed descriptor.
  FILE *retfile = fdopen(newfd, "rb");
  assert(retfile != NULL);

  // Return the new (FILE *).
  return retfile;
}

string c1, c2, c3;

void UpdateGlobals(string s1, string s2, string s3) {
  c1 = s1;
  c2 = s2;
  c3 = s3;
}

void PrintContext() {
  cout << c1 << c2 << c3;
  if (c1 != string(""))
    cout << endl;
}

bool Check16(uint16_t expected, uint16_t actual, string fieldname) {
  if (expected == actual)
    return true;

  PrintContext();
  cout << hex;
  cout << fieldname << ": expected " << expected;
  cout << ", but actually is " << actual << ".";
  if (ntohs(actual) == expected) {
    cout << "  Note: you likely ";
    cout << "forgot an endianness conversion, since ntohs(actual) ";
    cout << "== expected.";
  }
  cout << endl;
  return false;
}

bool Check32(uint32_t expected, uint32_t actual, string fieldname) {
  if (expected == actual)
    return true;

  PrintContext();
  cout << hex;
  cout << fieldname << ": expected " << expected;
  cout << ", but actually is " << actual << ".";
  if (ntohl(actual) == expected) {
    cout << "  Note: you likely ";
    cout << "forgot an endianness conversion, since ntohl(actual) ";
    cout << "== expected.";
  }
  cout << endl;
  return false;
}

bool Check64(uint64_t expected, uint64_t actual, string fieldname) {
  if (expected == actual)
    return true;

  PrintContext();
  cout << hex;
  cout << fieldname << ": expected " << expected;
  cout << ", but actually is " << actual << ".";
  if (ntohll(actual) == expected) {
    cout << "  Note: you likely ";
    cout << "forgot an endianness conversion, since ntohll(actual) ";
    cout << "== expected.";
  }
  cout << endl;
  return false;
}

bool CheckLT16(uint16_t smaller, uint16_t bigger, string fieldname) {
  if (smaller < bigger)
    return true;

  PrintContext();
  cout << hex;
  cout << fieldname << ": expected " << smaller;
  cout << " < " << bigger << ".";
  if (ntohs(smaller) == bigger) {
    cout << "  Note: there is a chance that you ";
    cout << "forgot an endianness conversion, since ntohs(" << smaller;
    cout << ") = " << ntohs(smaller) << " < " << bigger << ".";
  }
  cout << endl;
  return false;
}
bool CheckLT32(uint32_t smaller, uint32_t bigger, string fieldname) {
  if (smaller < bigger)
    return true;

  PrintContext();
  cout << hex;
  cout << fieldname << ": expected " << smaller;
  cout << " < " << bigger << ".";
  if (ntohl(smaller) == bigger) {
    cout << "  Note: it's possible that you ";
    cout << "forgot an endianness conversion, since ntohl(" << smaller;
    cout << ") = " << ntohl(smaller) << " < " << bigger << ".";
  }
  cout << endl;
  return false;
}
bool CheckLT64(uint64_t smaller, uint64_t bigger, string fieldname) {
  if (smaller < bigger)
    return true;

  PrintContext();
  cout << hex;
  cout << fieldname << ": expected " << smaller;
  cout << " < " << bigger << ".";
  if (ntohll(smaller) == bigger) {
    cout << "  Note: it's possible that you ";
    cout << "forgot an endianness conversion, since ntohll(" << smaller;
    cout << ") = " << ntohll(smaller) << " < " << bigger << ".";
  }
  cout << endl;
  return false;
}


}  // namespace hw3
