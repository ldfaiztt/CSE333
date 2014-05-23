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

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "Assert333.h"
#include "HashTable.h"
#include "HashTable_priv.h"

// A private utility function to grow the hashtable (increase
// the number of buckets) if its load factor has become too high.
static void ResizeHashtable(HashTable ht);

// a free function that does nothing
static void NullFree(void *freeme) { }

// Search through a bucket to see if it contains the key.
// Return true if the bucket contains the key; false otherwise.
static bool BucketHasKey(LLIter lliter, uint64_t key, HTKeyValue **keyvalue);

HashTable AllocateHashTable(uint32_t num_buckets) {
  HashTable ht;
  uint32_t  i;

  // defensive programming
  if (num_buckets == 0) {
    return NULL;
  }

  // allocate the hash table record
  ht = (HashTable) malloc(sizeof(HashTableRecord));
  if (ht == NULL) {
    return NULL;
  }

  // initialize the record
  ht->num_buckets = num_buckets;
  ht->num_elements = 0;
  ht->buckets =
    (LinkedList *) malloc(num_buckets * sizeof(LinkedList));
  if (ht->buckets == NULL) {
    // make sure we don't leak!
    free(ht);
    return NULL;
  }
  for (i = 0; i < num_buckets; i++) {
    ht->buckets[i] = AllocateLinkedList();
    if (ht->buckets[i] == NULL) {
      // allocating one of our bucket chain lists failed,
      // so we need to free everything we allocated so far
      // before returning NULL to indicate failure.  Since
      // we know the chains are empty, we'll pass in a
      // free function pointer that does nothing; it should
      // never be called.
      uint32_t j;
      for (j = 0; j < i; j++) {
        FreeLinkedList(ht->buckets[j], NullFree);
      }
      free(ht);
      return NULL;
    }
  }

  return (HashTable) ht;
}

void FreeHashTable(HashTable table,
                   ValueFreeFnPtr value_free_function) {
  uint32_t i;

  Assert333(table != NULL);  // be defensive

  // loop through and free the chains on each bucket
  for (i = 0; i < table->num_buckets; i++) {
    LinkedList  bl = table->buckets[i];
    HTKeyValue *nextKV;

    // pop elements off the the chain list, then free the list
    while (NumElementsInLinkedList(bl) > 0) {
      Assert333(PopLinkedList(bl, (void **) &nextKV));
      value_free_function(nextKV->value);
      free(nextKV);
    }
    // the chain list is empty, so we can pass in the
    // null free function to FreeLinkedList.
    FreeLinkedList(bl, NullFree);
  }

  // free the bucket array within the table record,
  // then free the table record itself.
  free(table->buckets);
  free(table);
}

uint64_t NumElementsInHashTable(HashTable table) {
  Assert333(table != NULL);
  return table->num_elements;
}

uint64_t FNVHash64(unsigned char *buffer, unsigned int len) {
  // This code is adapted from code by Landon Curt Noll
  // and Bonelli Nicola:
  //
  // http://code.google.com/p/nicola-bonelli-repo/
  static const uint64_t FNV1_64_INIT = 0xcbf29ce484222325ULL;
  static const uint64_t FNV_64_PRIME = 0x100000001b3ULL;
  unsigned char *bp = (unsigned char *) buffer;
  unsigned char *be = bp + len;
  uint64_t hval = FNV1_64_INIT;

  /*
   * FNV-1a hash each octet of the buffer
   */
  while (bp < be) {
    /* xor the bottom with the current octet */
    hval ^= (uint64_t) * bp++;
    /* multiply by the 64 bit FNV magic prime mod 2^64 */
    hval *= FNV_64_PRIME;
  }
  /* return our new hash value */
  return hval;
}

uint64_t FNVHashInt64(uint64_t hashme) {
  unsigned char buf[8];
  int i;

  for (i = 0; i < 8; i++) {
    buf[i] = (unsigned char) (hashme & 0x00000000000000FFULL);
    hashme >>= 8;
  }
  return FNVHash64(buf, 8);
}

uint64_t HashKeyToBucketNum(HashTable ht, uint64_t key) {
  return key % ht->num_buckets;
}

int InsertHashTable(HashTable table,
                    HTKeyValue newkeyvalue,
                    HTKeyValue *oldkeyvalue) {
  uint32_t insertbucket;
  LinkedList insertchain;

  Assert333(table != NULL);
  ResizeHashtable(table);

  // calculate which bucket we're inserting into,
  // grab its linked list chain
  insertbucket = HashKeyToBucketNum(table, newkeyvalue.key);
  insertchain = table->buckets[insertbucket];

  // Step 1 -- finish the implementation of InsertHashTable.
  // This is a fairly complex task, so you might decide you want
  // to define/implement a helper function hat helps you find
  // and optionally remove a key within a chain, rather than putting
  // all that logic inside here. You might also find that your helper
  // can be reused in step 2 and 3.

  // allocate space for new key/value
  HTKeyValue *newpayload = (HTKeyValue *) malloc(sizeof(HTKeyValue));
  if (newpayload == NULL)
    // out of memory
    return 0;

  // make a copy of new key/value passed in
  newpayload->key = newkeyvalue.key;
  newpayload->value = newkeyvalue.value;

  // no need to search through if the bucket contains the newkeyvalue.key
  // when the size of the bucket is 0, so add to the bucket directly
  if (NumElementsInLinkedList(insertchain) == 0) {
    // push newkeyvalue to the bucket, return 0 if push failed
    if (!PushLinkedList(insertchain, (void *) newpayload)) {
      free(newpayload);
      return 0;
    }

    table->num_elements += 1;
    // push succeeded
    return 1;
  }

  // make an iterator for the bucket
  LLIter lliter = LLMakeIterator(insertchain, 0UL);

  if (lliter == NULL) {
    free(newpayload);
    // out of memory
    return 0;
  }

  HTKeyValue *oldpayload;  // variable to store key/value

  // check if the bucket contains newkeyvalue.key
  if (BucketHasKey(lliter, newkeyvalue.key, &oldpayload)) {
    // get here if the bucket contains newkeyvalue.key

    // append new key/value to the bucket, return 0 if push failed
    if (!AppendLinkedList(insertchain, (void *) newpayload)) {
      free(newpayload);
      LLIteratorFree(lliter);
      return 0;
    }

    // copy the old key/value to the return parameter oldkeyvalue
    oldkeyvalue->key = oldpayload->key;
    oldkeyvalue->value = oldpayload->value;

    // free the ollpayload since we malloc when we inserted it
    free(oldpayload);

    // detele oldkeyvalue from the bucket
    LLIteratorDelete(lliter, &NullFree);

    LLIteratorFree(lliter);
    // append succeed
    return 2;
  }

  LLIteratorFree(lliter);
  // push newkeyvalue to the bucket, return 0 if push failed
  if (!AppendLinkedList(insertchain, (void *) newpayload)) {
    free(newpayload);
    return 0;
  }

  table->num_elements += 1;
  // push succeed
  return 1;
}

int LookupHashTable(HashTable table,
                    uint64_t key,
                    HTKeyValue *keyvalue) {
  Assert333(table != NULL);

  // Step 2 -- implement LookupHashTable.
  uint32_t lookupbucket;
  LinkedList lookupchain;

  // calculate which bucket we're looking into,
  // grab its linked list chain
  lookupbucket = HashKeyToBucketNum(table, key);
  lookupchain = table->buckets[lookupbucket];

  // key will not be in the bucket if the bucket is empty,
  // so return 0
  if (NumElementsInLinkedList(lookupchain) == 0)
    return 0;

  LLIter lliter = LLMakeIterator(lookupchain, 0UL);

  if (lliter == NULL)
    // out of memory
    return -1;

  HTKeyValue *payload;  // variable to store key/value
  if (BucketHasKey(lliter, key, &payload)) {
    // if key is found in the bucket, copy the
    // key/value to the return parameter payload
    keyvalue->key = payload->key;
    keyvalue->value = payload->value;

    LLIteratorFree(lliter);
    // lookup succeed
    return 1;
  }

  LLIteratorFree(lliter);
  // return 0 if key is not found
  return 0;
}

int RemoveFromHashTable(HashTable table,
                        uint64_t key,
                        HTKeyValue *keyvalue) {
  Assert333(table != NULL);

  // Step 3 -- implement RemoveFromHashTable.
  uint32_t removebucket;
  LinkedList removechain;

  // calculate which bucket we're removing from,
  // grab its linked list chain
  removebucket = HashKeyToBucketNum(table, key);
  removechain = table->buckets[removebucket];

  // key will not be in the bucket if the bucket is empty,
  // so return 0
  if (NumElementsInLinkedList(removechain) == 0)
    return 0;

  // get an iterator for the bucket
  LLIter lliter = LLMakeIterator(removechain, 0UL);

  if (lliter == NULL)
    // out of memory
    return -1;

  HTKeyValue* payload;  // variable to store key/value

  if (BucketHasKey(lliter, key, &payload)) {
    // if key is in the bucket, copy the key/value
    // to return parameter keyvalue
    keyvalue->key = payload->key;
    keyvalue->value = payload->value;

    // since we allocate space when we inserted, we need to
    // free the space while we are deleting the node
    free(payload);

    // delete the key from the bucket
    LLIteratorDelete(lliter, &NullFree);
    LLIteratorFree(lliter);

    table->num_elements -= 1;
    // remove succeed
    return 1;
  }

  LLIteratorFree(lliter);
  // key was not found
  return 0;
}

HTIter HashTableMakeIterator(HashTable table) {
  HTIterRecord *iter;
  uint32_t      i;

  Assert333(table != NULL);  // be defensive

  // malloc the iterator
  iter = (HTIterRecord *) malloc(sizeof(HTIterRecord));
  if (iter == NULL) {
    return NULL;
  }

  // if the hash table is empty, the iterator is immediately invalid,
  // since it can't point to anything.
  if (table->num_elements == 0) {
    iter->is_valid = false;
    iter->ht = table;
    iter->bucket_it = NULL;
    return iter;
  }

  // initialize the iterator.  there is at least one element in the
  // table, so find the first element and point the iterator at it.
  iter->is_valid = true;
  iter->ht = table;
  for (i = 0; i < table->num_buckets; i++) {
    if (NumElementsInLinkedList(table->buckets[i]) > 0) {
      iter->bucket_num = i;
      break;
    }
  }
  Assert333(i < table->num_buckets);  // make sure we found it.
  iter->bucket_it = LLMakeIterator(table->buckets[iter->bucket_num], 0UL);
  if (iter->bucket_it == NULL) {
    // out of memory!
    free(iter);
    return NULL;
  }
  return iter;
}

void HTIteratorFree(HTIter iter) {
  Assert333(iter != NULL);
  if (iter->bucket_it != NULL) {
    LLIteratorFree(iter->bucket_it);
    iter->bucket_it = NULL;
  }
  iter->is_valid = false;
  free(iter);
}

int HTIteratorNext(HTIter iter) {
  Assert333(iter != NULL);

  // Step 4 -- implement HTIteratorNext.

  // if the table is empty or the iterator is past the end of the table
  // after moving to the next element, return 0
  if (!(iter->is_valid))
    return 0;

  // if the current bucket has next element,
  // move to the next element and return 1
  if (LLIteratorHasNext(iter->bucket_it)) {
    LLIteratorNext(iter->bucket_it);
    return 1;
  }

  // if the current bucket is the last bucket of the table,
  // set is_valid to false and return 0
  if (iter->bucket_num == (iter->ht->num_buckets) - 1) {
    iter->is_valid = false;
    return 0;
  }

  uint64_t i;  // bucket number
  // find the next non-empty bucket
  for (i = iter->bucket_num + 1; i < iter->ht->num_buckets; i++) {
    if (NumElementsInLinkedList(iter->ht->buckets[i]) > 0) {
      iter->bucket_num = i;
      break;
    }
  }

  // if there is no non-empty bucket left to be iterated through,
  // set is_valid to false and return 0
  if (i == iter->ht->num_buckets) {
    iter->is_valid = false;
    return 0;
  }

  // if we find the next non-empty bucket, free the current
  // LinkedList iterator and make a new LinkedList iterator
  // for that non-empty bucket we found
  LLIteratorFree(iter->bucket_it);
  iter->bucket_it = LLMakeIterator(iter->ht->buckets[iter->bucket_num], 0UL);


  if (iter->bucket_it == NULL) {
    // out of memory
    iter->is_valid = false;
    return 0;
  }

  // succeed to move to the next element
  return 1;
}

int HTIteratorPastEnd(HTIter iter) {
  Assert333(iter != NULL);

  // Step 5 -- implement HTIteratorPastEnd.

  // the iterator is past the end of the table if its is_valid is
  // false, or the table is empty. iterator's is_valid in both
  // case are false
  if (!(iter->is_valid))
    return 1;

  // not past the end of the table
  return 0;
}

int HTIteratorGet(HTIter iter, HTKeyValue *keyvalue) {
  Assert333(iter != NULL);

  // Step 6 -- implement HTIteratorGet.

  HTKeyValue *payload;  // variable to store key/value

  if (iter->is_valid) {
    // get the key/value the iterator is pointing at and store in payload
    LLIteratorGetPayload(iter->bucket_it, (void **) &payload);

    // copy the key/value store in payload to return parameter keyvalue
    keyvalue->key = payload->key;
    keyvalue->value = payload->value;

    // get succeed
    return 1;
  }

  // return 0 if the iterator is not valid or the table is empty
  return 0;
}

int HTIteratorDelete(HTIter iter, HTKeyValue *keyvalue) {
  HTKeyValue kv;
  int res, retval;

  Assert333(iter != NULL);

  // Try to get what the iterator is pointing to.
  res = HTIteratorGet(iter, &kv);
  if (res == 0)
    return 0;

  // Advance the iterator.
  res = HTIteratorNext(iter);
  if (res == 0) {
    retval = 2;
  } else {
    retval = 1;
  }
  res = RemoveFromHashTable(iter->ht, kv.key, keyvalue);
  Assert333(res == 1);
  Assert333(kv.key == keyvalue->key);
  Assert333(kv.value == keyvalue->value);

  return retval;
}

static void ResizeHashtable(HashTable ht) {
  // Resize if the load factor is > 3.
  if (ht->num_elements < 3 * ht->num_buckets)
    return;

  // This is the resize case.  Allocate a new hashtable,
  // iterate over the old hashtable, do the surgery on
  // the old hashtable record and free up the new hashtable
  // record.
  HashTable newht = AllocateHashTable(ht->num_buckets * 9);

  // Give up if out of memory.
  if (newht == NULL)
    return;

  // Loop through the old ht with an iterator,
  // inserting into the new HT.
  HTIter it = HashTableMakeIterator(ht);
  if (it == NULL) {
    // Give up if out of memory.
    FreeHashTable(newht, &NullFree);
    return;
  }

  while (!HTIteratorPastEnd(it)) {
    HTKeyValue item, dummy;

    Assert333(HTIteratorGet(it, &item) == 1);
    if (InsertHashTable(newht, item, &dummy) != 1) {
      // failure, free up everything, return.
      HTIteratorFree(it);
      FreeHashTable(newht, &NullFree);
      return;
    }
    HTIteratorNext(it);
  }

  // Worked!  Free the iterator.
  HTIteratorFree(it);

  // Sneaky: swap the structures, then free the new table,
  // and we're done.
  {
    HashTableRecord tmp;

    tmp = *ht;
    *ht = *newht;
    *newht = tmp;
    FreeHashTable(newht, &NullFree);
  }

  return;
}

static bool BucketHasKey(LLIter lliter,
                         uint64_t key,
                         HTKeyValue **keyvalue) {
  Assert333(lliter != NULL);

  while (true) {
    LLIteratorGetPayload(lliter, (void **) keyvalue);

    // key is found
    if ((*keyvalue)->key == key)
      return true;

    // jump out of the loop if current node is the last node of the list
    // and key is not found in the list
    if (!LLIteratorHasNext(lliter))
      break;

    // advance to the next node
    LLIteratorNext(lliter);
  }

  // key is not found
  return false;
}
