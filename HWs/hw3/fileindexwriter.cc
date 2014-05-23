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

#include <cstdio>    // for (FILE *).
#include <cstring>   // for strlen(), etc.

#include "./fileindexutil.h"  // for many useful routines!
#include "./fileindexwriter.h"

// We need to peek inside the implementation of a HashTable so
// that we can iterate through its buckets and their chain elements.
extern "C" {
  #include "libhw1/HashTable_priv.h"
  #include "libhw1/Assert333.h"
}

namespace hw3 {

// Helper function to write the docid->filename mapping from the
// DocTable "dt" into file "f", starting at byte offset "offset".
// Returns the size of the written DocTable or 0 on error.
static uint32_t WriteDocTable(FILE *f, DocTable dt, uint32_t offset);

// Helper function to write the MemIndex "mi" into file "f", starting
// at byte offset "offset."  Returns the size of the written MemIndex
// or 0 on error.
static uint32_t WriteMemIndex(FILE *f, MemIndex mi, uint32_t offset);

// Helper function to write the index file's header into file "f".
// Returns the number of header bytes written on success, 0 on
// failure.  Will atomically write the MAGIC_NUMBER as the very last
// thing; as a result, if we crash part way through writing an index
// file, it won't contain a valid MAGIC_NUMBER and the rest of HW3
// will know to report an error.
static uint32_t WriteHeader(FILE *f,
                            uint32_t doct_size,
                            uint32_t memidx_size);

// A write_element_fn is used by WriteHashTable() to write a
// HashTable's HTKeyValue element into the index file at offset
// "offset".
//
// Returns the number of bytes written or 0 on error.
typedef uint32_t (*write_element_fn)(FILE *f,
                                     uint32_t offset,
                                     HTKeyValue *kv);

// Helper function to write a HashTable into file "f", starting at
// offset "offset".  The helper function "write_element_fn" is invoked
// to writes each HTKeyValue element within the HashTable into the
// file.
//
// Returns the total amount of data written, or 0 on failure.
static uint32_t WriteHashTable(FILE *f,
                               HashTable t,
                               uint32_t offset,
                               write_element_fn fn);

// Helper function used by WriteHashTable() to write out a bucket
// record (i.e., a "bucket_rec" within the hw3 diagrams).  Returns the
// amount of data written, or 0 on failure.
//
// "f" is the file to write into, "li" is the bucket chain linked
// list, "br_offset" is the offset of the 'bucket_rec' field to write
// into, and "b_offset" is the value of 'bucket offset' field to write
// within the bucket_rec field.
static uint32_t WriteBucketRecord(FILE *f,
                                  LinkedList li,
                                  uint32_t br_offset,
                                  uint32_t b_offset);

// Helper function used by WriteHashTable() to write out a bucket.
// Returns the amount of data written, or 0 on failure.
//
// "f" is the file to write into, "li" is the bucket chain linked list
// to write within the bucket, 'offset' is the offset of the bucket,
// and 'write_element_fn' is a helper function used to write the
// HTKeyValue into the element itself.
static uint32_t WriteBucket(FILE *f,
                            LinkedList li,
                            uint32_t offset,
                            write_element_fn fn);

uint32_t WriteIndex(MemIndex mi, DocTable dt, const char *filename) {
  uint32_t filesize = 0, dtres, mires, hres;
  FILE *f;

  // Do some sanity checking on the arguments we were given.
  Assert333(mi != NULL);
  Assert333(dt != NULL);
  Assert333(filename != NULL);

  // fopen() the file for writing; use mode "wb+" to indicate binary,
  // write mode, and to create/truncate the file.
  f = fopen(filename, "wb+");
  if (f == NULL)
    return 0;

  // write the document table using WriteDocTable().
  dtres = WriteDocTable(f, dt, FILEINDEX_HEADER_SIZE);
  if (dtres == 0) {
    fclose(f);
    unlink(filename);
    return 0;
  }
  filesize += dtres;

  // write the memindex using WriteMemIndex().
  // MISSING:
  mires = WriteMemIndex(f, mi, FILEINDEX_HEADER_SIZE + filesize);
  if (mires == 0) {
    fclose(f);
    unlink(filename);
    return 0;
  }
  filesize += mires;

  // write the header using WriteHeader().
  // MISSING:
  hres = WriteHeader(f, dtres, mires);
  if (hres == 0) {
    fclose(f);
    unlink(filename);
    return 0;
  }
  filesize += hres;

  // Clean up and return the total amount written.
  fclose(f);
  return filesize;
}

// This write_element_fn is used to write a docid->docname mapping
// element, i.e., an element of the "doctable" table.
static uint32_t WriteDocidDocnameFn(FILE *f,
                                    uint32_t offset,
                                    HTKeyValue *kv) {
  size_t res;
  uint64_t docid;
  uint16_t slen, slen_ho;
  char *filename;

  // fseek() to the provided offset.
  if (fseek(f, offset, SEEK_SET) != 0)
    return 0;

  // fwrite() the docid from "kv".  Remember to use htonll() to
  // convert the docid to network order before writing it.
  docid = htonll(kv->key);
  res = fwrite(&docid, 8, 1, f);
  if (res != 1)
    return 0;

  // fwrite() the filename size, in network order.  (Remember that the
  // filename is stored in kv->value.)
  // MISSING:
  filename = reinterpret_cast<char *>(kv->value);
  slen_ho = strlen(filename);

  // convert filename size to network order
  slen = htons(slen_ho);

  res = fwrite(&slen, sizeof(slen), 1, f);
  if (res != 1)
    return 0;

  // fwrite() the filename.  We don't write the null-terminator from
  // the string, just the characters.
  // MISSING:
  res = fwrite(filename, slen_ho, 1, f);
  if (res != 1)
    return 0;

  // calculate and return the total amount written.
  // MISSING (change this return to the correct thing):
  return 8 + sizeof(slen) + slen_ho;
}

static uint32_t WriteDocTable(FILE *f, DocTable dt, uint32_t offset) {
  // Use WriteHashTable() to write the docid->filename hash table.
  // You'll need to use DTGetDocidTable() to get the docID hash table
  // from dt, and you'll need to pass in WriteDocidDocnameFn as the
  // final parameter of WriteHashTable().
  return WriteHashTable(f,
                        DTGetDocidTable(dt),
                        offset,
                        &WriteDocidDocnameFn);
}

// This write_element_fn is used to write a DocID + position list
// element (i.e., an element of a nested docID table) into the file at
// offset 'offset'.
static uint32_t WriteDocPositionListFn(FILE *f,
                                       uint32_t offset,
                                       HTKeyValue *kv) {
  size_t res;

  // Extract the docID from the HTKeyValue.
  uint64_t docID_ho = kv->key;

  // Extract the positions LinkedList from the HTKeyValue.
  LinkedList positions = (LinkedList) kv->value;

  // Write the docID, in network order (use htonll(), since a
  // docID is 64 bits long).  You'll need to fseek() to the
  // right location in the file.
  // MISSING:
  // seek to right location to write
  res = fseek(f, offset, SEEK_SET);
  if (res != 0)
    return 0;

  // convert docID to network order
  uint64_t docID = htonll(docID_ho);

  // write docID
  res = fwrite(&docID, sizeof(docID), 1, f);
  if (res != 1)
    return 0;

  // Extract the number of positions in the positions list.
  uint32_t num_pos_ho = NumElementsInLinkedList(positions);

  // Write the number of positions, in network order.
  // MISSING:
  // convert number of positions to network order
  uint32_t num_pos = htonl(num_pos_ho);

  // write number of positions
  res = fwrite(&num_pos, sizeof(num_pos), 1, f);
  if (res != 1)
    return 0;

  // Loop through the positions list, writing each position out
  // from the payload.
  uint32_t i;
  LLIter it = LLMakeIterator(positions, 0);
  Assert333(it != NULL);
  void *payload;
  uint32_t pos, pos_ho;
  for (i = 0; i < num_pos_ho; i++) {
    // Get the next position from the list and write it out
    // in network order.
    // MISSING:
    // get the position and convert it to network order
    LLIteratorGetPayload(it, reinterpret_cast<void **>(&payload));
    pos_ho = (intptr_t) payload;
    pos = htonl(pos_ho);

    // write position
    res = fwrite(&pos, sizeof(pos), 1, f);
    if (res != 1) {
      LLIteratorFree(it);
      return 0;
    }

    // Iterate to the next position.
    LLIteratorNext(it);
  }
  LLIteratorFree(it);


  // Calculate and return the total amount of data written.
  // MISSING (fix this return value):
  return sizeof(docID) + sizeof(num_pos) + num_pos_ho * sizeof(pos);
}

// This write_element_fn is used to write a WordDocSet
// element into the file at position 'offset'.
static uint32_t WriteWordDocSetFn(FILE *f,
                                  uint32_t offset,
                                  HTKeyValue *kv) {
  size_t res;

  // Extract the WordDocSet from the HTKeyValue.
  WordDocSet *wds = static_cast<WordDocSet *>(kv->value);
  Assert333(wds != NULL);

  // Prepare the wordlen field and write it in network order.
  uint16_t wordlen, wordlen_ho;
  char *word;
  // MISSING:
  // seek to the offset to write
  res = fseek(f, offset, SEEK_SET);
  if (res != 0)
    return 0;

  // get the word length and convert it to network order
  word = wds->word;
  wordlen_ho = strlen(word);
  wordlen = htons(wordlen_ho);

  // write word length
  res = fwrite(&wordlen, sizeof(wordlen), 1, f);
  if (res != 1)
    return 0;

  // Write the word itself, excluding the NULL terminator.
  // MISSING:
  // seek to right place to write the word
  res = fseek(f, offset + 2 + 4, SEEK_SET);
  if (res != 0)
    return 0;

  // write the word
  res = fwrite(word, wordlen_ho, 1, f);
  if (res != 1)
    return 0;

  // Write the nested DocID->positions hashtable (i.e., the "docID
  // table" element in the diagrams).  Use WriteHashTable() to do it,
  // passing it the wds->docIDs table and using the
  // WriteDocPositionListFn helper function as the final parameter.
  uint32_t htlen_ho = WriteHashTable(f,
                                     wds->docIDs,
                                     offset + 6 + wordlen_ho,
                                     &WriteDocPositionListFn);

  // Write the "docID table length" field, in network order, in
  // the right place in the file.  (The docid table length is the
  // return value from WriteHashTable() above.)
  // MISSING:
  // seek to right place to write docID table length
  res = fseek(f, offset + 2, SEEK_SET);
  if (res != 0)
    return 0;

  // convert docID table length to network order
  uint32_t htlen = htonl(htlen_ho);

  res = fwrite(&htlen, sizeof(htlen), 1, f);
  if (res != 1)
    return 0;

  // Calculate and return the total amount of data written.
  // MISSING (fix this return value):
  return sizeof(wordlen) + sizeof(htlen) + wordlen_ho + htlen_ho;
}

static uint32_t WriteMemIndex(FILE *f, MemIndex mi, uint32_t offset) {
  // Use WriteHashTable() to write the MemIndex into the file.  You'll
  // need to use MIGetHashTable() to get the HashTable from the
  // MemIndex, and you'll need to pass in the WriteWordDocSetFn helper
  // function as the final argument.
  return WriteHashTable(f,
                        mi,
                        offset,
                        &WriteWordDocSetFn);
}

static uint32_t WriteHeader(FILE *f,
                            uint32_t doct_size,
                            uint32_t memidx_size) {
  // We need to calculate the checksum over the doctable and index
  // table.  (Note that the checksum does not include the index file
  // header, just these two tables.)  Use fseek() to seek to the right
  // location, and use a CRC32 object from fileindexutil.h to do the
  // CRC checksum calculation, feeding it characters that you read
  // from the index file using fread().  Note that you can always
  // read the unit test for the CRC class to learn how to use it!
  uint32_t crc, magicnum;
  uint32_t cslen = doct_size + memidx_size;
  CRC32 crcobj;
  uint32_t res, i;
  uint8_t next_char;

  // MISSING:
  // seek to head of doctable
  res = fseek(f, FILEINDEX_HEADER_SIZE, SEEK_SET);
  if (res != 0)
    return 0;

  // feed one character at a time to CRC32 object
  for (i = 0; i < cslen; i++) {
    res = fread(reinterpret_cast<void *>(&next_char), sizeof(next_char), 1, f);
    if (res != 1)
      return 0;

    crcobj.FoldByteIntoCRC(next_char);
  }

  // Write the header fields, except magic num, which we save for the
  // very last thing we write.  Be sure to convert the fields to
  // network order before writing them!
  // MISSING:

  // get the final CRC value and convert it to network order
  crc = crcobj.GetFinalCRC();
  crc = htonl(crc);

  // convert doct_size and memidx_size to network order
  doct_size = htonl(doct_size);
  memidx_size = htonl(memidx_size);

  // seek the position to write the header fields (except magic num)
  res = fseek(f, CHECKSUM_OFFSET, SEEK_SET);
  if (res != 0)
    return 0;

  // write "check_sum"
  res = fwrite(&crc, sizeof(crc), 1, f);
  if (res != 1)
    return 0;

  // write "doctable_size"
  res = fwrite(&doct_size, sizeof(doct_size), 1, f);
  if (res != 1)
    return 0;

  // write "index_size"
  res = fwrite(&memidx_size, sizeof(memidx_size), 1, f);
  if (res != 1)
    return 0;

  // Use fsync on the file to flush any not-yet-written data for the
  // file out of the operating system's file buffer cache to disk.
  // ("man fsync" and "man fileno").  This way, we ensure everything
  // is safely on disk before we write the magic number field.
  Assert333(fsync(fileno(f)) == 0);

  // Write the magic number field, in network order.
  if (fseek(f, MAGIC_NUMBER_OFFSET, SEEK_SET) != 0)
    return 0;
  magicnum = htonl(MAGIC_NUMBER);
  if (fwrite(&magicnum, 4, 1, f) != 1)
    return 0;

  // Use fsync again to flush the magic number field to disk.
  Assert333(fsync(fileno(f)) == 0);

  // We're done!  Return the number of header bytes written.
  return FILEINDEX_HEADER_SIZE;
}

static uint32_t WriteBucketRecord(FILE *f,
                                  LinkedList li,
                                  uint32_t br_offset,
                                  uint32_t b_offset) {
  uint32_t res;
  uint32_t chainlen, chainlen_ho;
  uint32_t bucketof;

  // fseek() to the "bucket_rec" record for this bucket.
  res = fseek(f, br_offset, SEEK_SET);
  if (res != 0)
    return 0;

  // Use NumElementsInLinkedLis() to figure out how many chained
  // elements are in this bucket.
  chainlen_ho = NumElementsInLinkedList(li);

  // Write the "chain len" and "bucket position" fields of the
  // bucket_rec, in network order.
  // MISSING:

  // convert "chain len" and "bucket position" to network order
  chainlen = htonl(chainlen_ho);
  bucketof = htonl(b_offset);

  // write "chain len"
  res = fwrite(&chainlen, sizeof(chainlen), 1, f);
  if (res != 1)
    return 0;

  // write "bucket position"
  res = fwrite(&bucketof, sizeof(bucketof), 1 , f);
  if (res != 1)
    return 0;

  // Calculate and return how many bytes we wrote.
  return 8;  // :)
}

static uint32_t WriteBucket(FILE *f,
                            LinkedList li,
                            uint32_t offset,
                            write_element_fn fn) {
  // Use NumElementsInLinkedList() to calculate how many elements are
  // in this bucket chain.
  uint32_t chainlen_ho = NumElementsInLinkedList(li);

  // "bucketlen" is our running calculation of how many bytes have
  // been written out for this bucket.
  uint32_t bucketlen = 4 * chainlen_ho;

  // Figure out the position of the next "element" in the bucket.
  uint32_t nextelpos = offset + bucketlen;

  uint32_t res;

  // Loop through the chain, writing each associated "element position"
  // header field for the bucket and then writing out the "element"
  // itself.  Be sure to write things in network order.  Use the
  // "fn" parameter to invoke the helper function that knows how to
  // write out the payload of each chain element into the "element"
  // fields of the bucket.
  if (chainlen_ho > 0) {
    LLIter it = LLMakeIterator(li, 0);
    Assert333(it != NULL);
    uint32_t j;
    for (j = 0; j < chainlen_ho; j++) {
      uint32_t ellen;
      HTKeyValue *kv;

      // MISSING:
      // convert element position to network order
      uint32_t nextelpos_no = htonl(nextelpos);

      // seek to offset position in order to write
      res = fseek(f, offset, SEEK_SET);
      if (res != 0) {
        LLIteratorFree(it);
        return 0;
      }

      // write element position
      res = fwrite(&nextelpos_no, sizeof(nextelpos_no), 1, f);
      if (res != 1) {
        LLIteratorFree(it);
        return 0;
      }

      LLIteratorGetPayload(it, reinterpret_cast<void **>(&kv));

      // use write_element_fn to write element itself
      ellen = fn(f, nextelpos, kv);
      if (ellen == 0) {
        LLIteratorFree(it);
        return 0;
      }

      offset += sizeof(nextelpos_no);

      // Advance to the next element in the chain, tallying up our
      // lengths.
      bucketlen += ellen;
      nextelpos += ellen;
      LLIteratorNext(it);
    }
    LLIteratorFree(it);
  }

  // Return the total amount of data written.
  return bucketlen;
}

// This is the main workhorse of the file.  It iterates through the
// buckets in the HashTable "t", writing the hash table out into
// the index file.
static uint32_t WriteHashTable(FILE *f,
                               HashTable t,
                               uint32_t offset,
                               write_element_fn fn) {
  HashTableRecord *ht = static_cast<HashTableRecord *>(t);
  uint32_t next_bucket_rec_offset = offset + 4;
  uint32_t next_bucket_offset;
  uint32_t i, res, numbucks;

  // fwrite() out the "num_buckets" (number of buckets) field, in
  // network order.
  numbucks = htonl(ht->num_buckets);
  res = fseek(f, offset, SEEK_SET);
  if (res != 0)
    return 0;
  res = fwrite(&numbucks, 4, 1, f);
  if (res != 1)
    return 0;

  // Figure out the offset of the first "bucket" field.  Each
  // bucket_rec  is 8 bytes, and there are ht->num_buckets of them.
  next_bucket_offset = next_bucket_rec_offset +
    (ht->num_buckets) * 8;

  // Loop through table's buckets, writing them out to the appropriate
  // "bucket_rec" and "bucket" fields within the file index.  Writing
  // a bucket means writing the bucket_rec, then writing the bucket
  // itself.  Use WriteBucketRecord() to write a bucket_rec, and
  // WriteBucket() to write a bucket.
  //
  // Be sure to handle the corner case where the bucket's chain is
  // empty.  For that case, you still have to write a "bucket_rec"
  // record for the bucket, but you won't write a "bucket".
  for (i = 0; i < ht->num_buckets; i++) {
    // MISSING:
    LinkedList li = (ht->buckets)[i];
    uint32_t chainlen_ho = NumElementsInLinkedList(li);
    res = WriteBucketRecord(f, li, next_bucket_rec_offset, next_bucket_offset);
    if (res == 0)
      return 0;
    next_bucket_rec_offset += res;

    if (chainlen_ho != 0) {
      // only write bucket if the bucket's chain is not empty
      res = WriteBucket(f, li, next_bucket_offset, fn);
      if (res == 0)
        return 0;
      next_bucket_offset += res;
    }
  }

  // Calculate and return the total number of bytes written.
  return (next_bucket_offset - offset);
}

}  // namespace hw3
