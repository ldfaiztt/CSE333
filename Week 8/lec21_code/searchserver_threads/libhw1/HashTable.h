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

#ifndef _HW1_HASHTABLE_H_
#define _HW1_HASHTABLE_H_

#include <stdbool.h>    // for bool, true, false
#include <stdint.h>     // so we can use uint64_t, etc.

// A HashTable is a simple chained hash table with a static number of buckets.
// We provide the interface; your job is to provide the implementation.
//
// To hide the implementation of HashTable, we declare the "struct htrec"
// structure here, but we define the structure in the internal header
// HashTable_priv.h.  This lets us define a pointer to the HashTableRecord as
// a new "HashTable" type, but leave the implementation details of HashTable
// opaque to the customer.
struct htrec;
typedef struct htrec *HashTable;

// When freeing a HashTable, customers need to pass a pointer to a function
// that frees the payload.  The pointed-to function is invoked once for each
// value in the HashTable.
typedef void(*ValueFreeFnPtr)(void *value);

// Allocate and return a new HashTable.
//
// Arguments:
//
// - num_buckets:  the number of buckets the hash table should
//   initially contain.  Remember that this is a chained hash
//   table, so as the load factor approaches 1, linked lists hanging
//   off of each bucket will start to grow.  This implementation
//   will dynamically resize the hashtable when the load factor
//   exceeds 3.  It will multiple the number of buckets in the
//   hashtable by 3, so that post-resize load factor is 1/3.
//
// Returns NULL on error, non-NULL on success.
HashTable AllocateHashTable(uint32_t num_buckets);

// Free a HashTable.
//
// Arguments:
//
// - table:  the HashTable to free.  It is unsafe to use table
//   after this function returns.
//
// - value_free_function:  this argument is a pointer to a value
//   freeing function; see above for details.
void FreeHashTable(HashTable table, ValueFreeFnPtr value_free_function);

// Figure out the number of elements in the hash table.
//
// Arguments:
//
// - table:  the table to query
//
// Returns:
//
// - table size (>=0); note that this is an unsigned 64-bit integer.
uint64_t NumElementsInHashTable(HashTable table);

// HashTables store key/value pairs.  We'll define a key to be an
// unsigned 64-bit integer; it's up to the customer to figure out how
// to produce an appropriate hash key, but below we provide an
// implementation of FNV hashing to help them out.  We'll define
// a value to be a (void *), so that customers can pass in pointers to
// arbitrary structs as values, but of course we have to worry about
// memory management as a side-effect.
typedef struct {
  uint64_t   key;    // the key in the key/value pair
  void      *value;  // the value in the key/value pair
} HTKeyValue, *HTKeyValuePtr;

// This is an implementation of FNV hashing.  Customers
// can use it to hash an arbitrary sequence of bytes into
// a 64-bit key suitable for using as a hash key.
//
// If you're curious, you can read about FNV hashing here:
//
//  http://en.wikipedia.org/wiki/Fowler–Noll–Vo_hash_function
//
// Arguments:
//
// - buffer: a pointer to a len-size buffer of unsigned chars
//
// - len: how many bytes are in the buffer
//
// Returns:
//
// - a nicely distributed 64-bit hash value suitable for
//   use in a HTKeyValue
uint64_t FNVHash64(unsigned char *buffer, unsigned int len);

// This is a convenience routine to produce a nice, evenly
// distributed 64-bit hash key from a potentially poorly
// distributed 64 bit number.  It uses FNVHash64 to get its
// job done.
//
// Arguments:
//
// - hashme:  a 64-bit integer to hash
//
// Returns:
//
// - a nicely distributed 64-bit hash value suitable for
//   use in a HTKeyValue
uint64_t FNVHashInt64(uint64_t hashme);

// Inserts a key,value pair into the HashTable.
//
// Arguments:
//
// - table: the HashTable to insert into
//
// - newkeyvalue: the HTKeyValue to insert into the table
//
// - oldkeyval: if the key in newkeyvalue is already present
//   in the HashTable, that old key/value is replaced with
//   newkeyvalue.  In that case, the old key/value is returned via
//   this return parameter to the caller.  It's up to the caller
//   to free any allocated memory associated with oldkeyvalue->value.
//
// Returns:
//
//  - 0 on failure (e.g., out of memory)
//
//  - +1 if the newkeyvalue was inserted and there was no
//    existing key/value with that key
//
//  - +2 if the newkeyvalue was inserted and an old key/value
//    with the same key was replaced and returned through
//    the oldkeyval return parameter.  In this case, the caller assumes
//    ownership of oldkeyvalue.
int InsertHashTable(HashTable table,
                    HTKeyValue newkeyvalue,
                    HTKeyValue *oldkeyvalue);

// Looks up a key in the HashTable, and if it is
// present, returns the key/value associated with it.
//
// Arguments:
//
// - table: the HashTable to look in
//
// - key: the key to look up
//
// - keyvalue: if the key is present, a copy of the key/value is
//   returned to the caller via this return parameter.  Note that the
//   key/value is left in the HashTable, so it is not safe for the
//   caller to free keyvalue->value.
//
// Returns:
//
//  - -1 if there was an error (e.g., out of memory)
//
//  - 0 if the key wasn't found in the HashTable
//
//  - +1 if the key was found, and therefore the associated key/value
//    was returned to the caller via that keyvalue return parameter.
int LookupHashTable(HashTable table,
                    uint64_t key,
                    HTKeyValue *keyvalue);

// Removes a key/value from the HashTable and returns it to the
// caller.
//
// Arguments:
//
// - table: the HashTable to look in
//
// - key: the key to look up
//
// - keyvalue: if the key is present, a copy of key/value is returned
//   to the caller via this return parameter and the key/value is
//   removed from the HashTable.  Note that the caller is responsible
//   for managing the memory associated with keyvalue->value from
//   this point on.
//
// Returns:
//  - -1 on error (e.g., out of memory)
//
//  - 0 if the key wasn't found in the HashTable
//
//  - +1 if the key was found, and therefore (a) the associated
//    key/value was returned to the caller via that keyvalue return
//    parameter, and (b) that key/value was removed from the
//    HashTable.
int RemoveFromHashTable(HashTable table,
                        uint64_t key,
                        HTKeyValue *keyvalue);

// HashTables support the notion of an iterator, similar to
// Java iterators.  You use an iterator to iterate forward
// through the HashTable.   The order in which the iterator
// goes through the HashTable is undefined, and not necessarily
// deterministic; all that is promised is that each key/value
// is visited exactly once.  Also, if the customer uses a
// HashTable function to mutate the hash table, any existing
// iterators become dangerous to use and should be freed.
struct ht_itrec;
typedef struct ht_itrec *HTIter;  // same trick to hide implementation.

// Manufacture an iterator for the table.  If there are
// elements in the hash table, the iterator is initialized
// to point at the "first" one.  If there are no elements
// in the hash table, the iterator is unusable and
//
// Arguments:
//
// - table:  the table from which to return an iterator
//
// Returns NULL on failure, non-NULL on success.
HTIter HashTableMakeIterator(HashTable table);

// When you're done with a hash table iterator, you need to free it
// by calling this function.
//
// Arguments:
//
// - iter: the iterator to free.  It is not safe to use
//   the iterator after freeing it.
void HTIteratorFree(HTIter iter);

// Move the iterator to the next element of the table.
//
// Arguments:
//
// - iter: the iterator to move
//
// Returns:
//
// - +1 on success
//
// - 0 if the iterator cannot be moved forward to the next
//   valid element, either because the table is empty, or
//   because the iterator (after moving it forward) is past the
//   end of the table.  In either case, the iterator is no
//   longer usable.
int HTIteratorNext(HTIter iter);

// Tests to see whether the iterator is past the end
// of the table.
//
// Arguments:
//
// - iter: the iterator to test
//
// Returns:
//
// - +1 if iter is past the end of the table or the table is empty.
//
// - 0 if iter is not at the end of the table (and therefore
//   the table is non-empty).
int HTIteratorPastEnd(HTIter iter);

// Returns a copy of the key/value that the iterator is currently
// pointing at.
//
// Arguments:
//
// - iter: the iterator to fetch the key/value from
//
// - keyvalue: a return parameter through which the key/value
//   is returned.
//
// Returns:
//
// - 0 if the iterator is not valid or the table is empty
//
// - +1 on success.
int HTIteratorGet(HTIter iter, HTKeyValue *keyvalue);

// Returns a copy of key/value that the iterator is currently
// pointing at, and removes that key/value from the
// hashtable.  The caller assumes ownership of any memory
// pointed to by the value.  As well, this advances
// the iterator to the next element in the hashtable.
//
// Arguments:
//
// - iter: the iterator to fetch the key/value from
//
// - keyvalue: a return parameter through which the key/value
//   is returned.
//
// Returns:
//
// - 0 if the iterator is not valid or the table is empty
//
// - +1 on success, and the iterator is still valid.
//
// - +2 on success, but the iterator is now invalid because
//   it has advanced past the end of the hash table.
int HTIteratorDelete(HTIter iter, HTKeyValue *keyvalue);

#endif  // _HW1_HASHTABLE_H_
