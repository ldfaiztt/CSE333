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

extern "C" {
  #include "./HashTable.h"
  #include "./HashTable_priv.h"
  #include "./LinkedList.h"
  #include "./LinkedList_priv.h"
}
#include "./test_suite.h"
#include "./test_hashtable.h"

namespace hw1 {

// our payload structure
typedef struct payload_st {
  int magic_num;
  int payload_num;
} Payload;

// number of payload frees
static unsigned int num_payload_frees = 0U;

// our payload free test function
void TestPayloadFree(void *payload) {
  num_payload_frees++;
  ASSERT_EQ((static_cast<Payload *>(payload))->magic_num,
            static_cast<int>(0xDEADBEEF));
  free(payload);
}

TEST_F(Test_HashTable, HTSTestAllocFree) {
  // simple create / delete test
  HashTable ht = AllocateHashTable(3);
  ASSERT_EQ(static_cast<uint64_t>(0), ht->num_elements);
  ASSERT_EQ(static_cast<uint64_t>(3), ht->num_buckets);
  ASSERT_NE(static_cast<LinkedList *>(NULL), ht->buckets);
  ASSERT_EQ(static_cast<uint64_t>(0),
            NumElementsInLinkedList(ht->buckets[0]));
  ASSERT_EQ(static_cast<uint64_t>(0),
            NumElementsInLinkedList(ht->buckets[1]));
  ASSERT_EQ(static_cast<uint64_t>(0),
            NumElementsInLinkedList(ht->buckets[2]));
  FreeHashTable(ht, &TestPayloadFree);
  HW1Addpoints(10);
}

TEST_F(Test_HashTable, HTSTestInsertLookupRemove) {
  // create the table
  HashTable table = AllocateHashTable(3);

  // allocate and insert a bunch of elements
  uint64_t i;

  for (i = 0; i < 100; i++) {
    // do the insert
    Payload *np = static_cast<Payload *>(malloc(sizeof(Payload)));
    HTKeyValue old, newkv;
    assert(np != NULL);
    np->magic_num = 0xDEADBEEF;
    np->payload_num = static_cast<int>(i);
    newkv.key = i;
    newkv.value = static_cast<void *>(np);
    ASSERT_EQ(1, InsertHashTable(table, newkv, &old));

    // test double insert
    ASSERT_EQ(2, InsertHashTable(table, newkv, &old));
    ASSERT_EQ(i, old.key);
    ASSERT_EQ(static_cast<void *>(np), old.value);

    // test lookup
    old.key = 1;
    old.value = NULL;
    ASSERT_EQ(1, LookupHashTable(table, i, &old));
    ASSERT_EQ(i, old.key);
    ASSERT_EQ(static_cast<void *>(np), old.value);

    // test bad lookup
    ASSERT_EQ(0, LookupHashTable(table, i+1, &old));

    // test bad remove
    ASSERT_EQ(0, RemoveFromHashTable(table, i+1, &old));

    // test good remove and reinsert
    old.key = 1;
    old.value = NULL;
    ASSERT_EQ(1, RemoveFromHashTable(table, i, &old));
    ASSERT_EQ(i, old.key);
    ASSERT_EQ(static_cast<void *>(np), old.value);
    ASSERT_EQ(static_cast<uint64_t>(i), NumElementsInHashTable(table));
    ASSERT_EQ(1, InsertHashTable(table, newkv, &old));
    ASSERT_EQ(2, InsertHashTable(table, newkv, &old));
    ASSERT_EQ(static_cast<uint64_t>(i+1), NumElementsInHashTable(table));
  }
  HW1Addpoints(10);

  // delete every other key
  for (i = 0; i < 100; i += 2) {
    HTKeyValue old;

    ASSERT_EQ(1, RemoveFromHashTable(table, i, &old));
    ASSERT_EQ(i, old.key);
    TestPayloadFree(old.value);
    ASSERT_EQ(0, RemoveFromHashTable(table, i, &old));
  }
  ASSERT_EQ(table->num_elements, (uint64_t) 50);

  // delete the remaining keys
  for (i = 1; i < 100; i += 2) {
    HTKeyValue old;

    ASSERT_EQ(1, RemoveFromHashTable(table, i, &old));
    ASSERT_EQ(i, old.key);
    TestPayloadFree(old.value);
    ASSERT_EQ(0, RemoveFromHashTable(table, i, &old));
  }
  ASSERT_EQ(table->num_elements, (uint64_t) 0);

  // try a final add / remove pass
  for (i = 0; i < 100; i++) {
    // do the insert
    Payload *np = static_cast<Payload *>(malloc(sizeof(Payload)));
    HTKeyValue old, newkv;
    assert(np != NULL);
    np->magic_num = 0xDEADBEEF;
    np->payload_num = static_cast<int>(i);
    newkv.key = i;
    newkv.value = static_cast<void *>(np);
    ASSERT_EQ(1, InsertHashTable(table, newkv, &old));

    // test lookup
    old.key = 1;
    old.value = NULL;
    ASSERT_EQ(1, LookupHashTable(table, i, &old));
    ASSERT_EQ(old.key, i);
    ASSERT_EQ(old.value, static_cast<void *>(np));
  }
  ASSERT_EQ((uint64_t) 100, table->num_elements);

  // delete most of the remaining keys
  for (i = 0; i < 98; i++) {
    HTKeyValue old;

    ASSERT_EQ(1, RemoveFromHashTable(table, i, &old));
    ASSERT_EQ(i, old.key);
    TestPayloadFree(old.value);
    ASSERT_EQ(0, RemoveFromHashTable(table, i, &old));
  }
  ASSERT_EQ(static_cast<uint64_t>(2), table->num_elements);

  // delete the HT and the final keys
  num_payload_frees = 0;
  FreeHashTable(table, &TestPayloadFree);
  ASSERT_EQ(2U, num_payload_frees);
  HW1Addpoints(10);
}

TEST_F(Test_HashTable, HTSTestIterator) {
  HTKeyValue old, newkv;

  // create the table
  HashTable table = AllocateHashTable(3);

  // try using an iterator on an empty table
  HTIter it = HashTableMakeIterator(table);
  ASSERT_FALSE(it->is_valid);
  ASSERT_EQ(1, HTIteratorPastEnd(it));
  ASSERT_EQ(0, HTIteratorGet(it, &old));
  HTIteratorFree(it);
  HW1Addpoints(10);

  // allocate and insert a bunch of elements
  uint64_t i;

  for (i = 0; i < 100; i++) {
    // do the insert
    Payload *np = static_cast<Payload *>(malloc(sizeof(Payload)));
    assert(np != NULL);
    np->magic_num = 0xDEADBEEF;
    np->payload_num = static_cast<int>(i);
    newkv.key = i;
    newkv.value = static_cast<void *>(np);
    ASSERT_EQ(1, InsertHashTable(table, newkv, &old));
  }
  // create an iterator on the table
  it = HashTableMakeIterator(table);
  ASSERT_EQ(true, it->is_valid);
  HW1Addpoints(10);

  // iterate through, verifying each value is found exactly once
  int valarray[100] = { 0 };   // array of 100 0's
  for (i = 0; i < 100; i++) {
    Payload *op;

    ASSERT_EQ(0, HTIteratorPastEnd(it));
    ASSERT_EQ(1, HTIteratorGet(it, &old));
    ASSERT_EQ(0, valarray[static_cast<int>(old.key)]);
    valarray[static_cast<int>(old.key)] = 1;
    op = static_cast<Payload *>(old.value);
    ASSERT_EQ(static_cast<int>(0xDEADBEEF), op->magic_num);
    ASSERT_EQ(static_cast<int>(old.key), op->payload_num);
    if (i == 99) {
      ASSERT_EQ(0, HTIteratorNext(it));
      ASSERT_EQ(1, HTIteratorPastEnd(it));
    } else {
      ASSERT_EQ(1, HTIteratorNext(it));
      ASSERT_EQ(0, HTIteratorPastEnd(it));
    }
  }
  for (i = 0; i < 100; i++) {
    ASSERT_EQ(1, valarray[i]);
  }
  ASSERT_EQ(0, HTIteratorNext(it));
  HTIteratorFree(it);
  HW1Addpoints(20);

  // Iterate through again, deleting every third key.
  it = HashTableMakeIterator(table);
  ASSERT_EQ(true, it->is_valid);
  for (i = 0; i < 100; i++) {
    Payload *op;

    valarray[i] = 0;
    ASSERT_EQ(HTIteratorGet(it, &old), 1);
    if (static_cast<int>(old.key) % 3 == 0) {
      int oldnumelements, newnumelements;

      oldnumelements = static_cast<int>(NumElementsInHashTable(table));
      op = static_cast<Payload *>(old.value);
      ASSERT_EQ(static_cast<int>(old.key), op->payload_num);
      if (i == 99) {
        ASSERT_EQ(2, HTIteratorDelete(it, &old));
      } else {
        ASSERT_EQ(1, HTIteratorDelete(it, &old));
      }
      newnumelements = static_cast<int>(NumElementsInHashTable(table));
      ASSERT_EQ(oldnumelements-1, newnumelements);
      op = static_cast<Payload *>(old.value);
      free(op);
    } else {
      if (i == 99) {
        ASSERT_EQ(0, HTIteratorNext(it));
        ASSERT_EQ(1, HTIteratorPastEnd(it));
      } else {
        ASSERT_EQ(1, HTIteratorNext(it));
        ASSERT_EQ(0, HTIteratorPastEnd(it));
      }
    }
  }
  // Free the iterator
  HTIteratorFree(it);
  HW1Addpoints(10);

  // Iterate through one last time, making sure we get only
  // the non-zero mod 3 keys.
  it = HashTableMakeIterator(table);
  ASSERT_EQ(true, it->is_valid);
  for (i = 0; i < 66; i++) {
    ASSERT_EQ(1, HTIteratorGet(it, &old));
    valarray[static_cast<int>(old.key)] = 1;
    if (i == 65) {
      ASSERT_EQ(0, HTIteratorNext(it));
      ASSERT_EQ(1, HTIteratorPastEnd(it));
    } else {
      ASSERT_EQ(1, HTIteratorNext(it));
      ASSERT_EQ(0, HTIteratorPastEnd(it));
    }
  }
  for (i = 0; i < 100; i++) {
    if (i % 3 == 0) {
      ASSERT_EQ(0, valarray[i]);
    } else {
      ASSERT_EQ(1, valarray[i]);
    }
  }
  // Free the iterator
  HTIteratorFree(it);
  HW1Addpoints(10);

  // delete the HT and the final keys
  num_payload_frees = 0;
  FreeHashTable(table, &TestPayloadFree);
  ASSERT_EQ(66U, num_payload_frees);
  HW1Addpoints(10);
}

}  // namespace hw1
