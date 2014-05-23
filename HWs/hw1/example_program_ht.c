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

#include "Assert333.h"
#include "HashTable.h"

typedef struct {
  int num;
} ExampleValue, *ExampleValuePtr;

// prototype of our free function
void ExampleValueFree(void *value);

// our main function; here, we demonstrate how to use some
// of the hash table functions
int main(int argc, char **argv) {
  ExampleValuePtr evp;
  HashTable ht;
  HTIter iter;
  HTKeyValue kv, old_kv;
  int i;

  // allocate a hash table with 10,000 initial buckets
  ht = AllocateHashTable(10000);
  Assert333(ht != NULL);

  // insert 20,000 elements (load factor = 2.0)
  for (i = 0; i < 20000; i++) {
    evp = (ExampleValuePtr) malloc(sizeof(ExampleValue));
    Assert333(evp != NULL);
    evp->num = i;

    // make sure HT has the right # of elements in it to start
    Assert333(NumElementsInHashTable(ht) == (uint64_t) i);

    // insert a new element
    kv.key = FNVHashInt64(i);
    kv.value = (void *) evp;
    Assert333(InsertHashTable(ht, kv, &old_kv) == 1);

    // make sure hash table has right # of elements post-insert
    Assert333(NumElementsInHashTable(ht) == (uint64_t) (i+1));
  }

  // look up a few values
  Assert333(LookupHashTable(ht, FNVHashInt64(100), &kv) == 1);
  Assert333(kv.key == FNVHashInt64(100));
  Assert333(((ExampleValuePtr) kv.value)->num == 100);

  Assert333(LookupHashTable(ht, FNVHashInt64(18583), &kv) == 1);
  Assert333(kv.key == FNVHashInt64(18583));
  Assert333(((ExampleValuePtr) kv.value)->num == 18583);

  // make sure non-existent value cannot be found
  Assert333(LookupHashTable(ht, FNVHashInt64(20000), &kv) == 0);

  // delete a value
  Assert333(RemoveFromHashTable(ht, FNVHashInt64(100), &kv) == 1);
  Assert333(kv.key == FNVHashInt64(100));
  Assert333(((ExampleValuePtr) kv.value)->num == 100);
  ExampleValueFree(kv.value);   // since we malloc'ed it, we must free it

  // make sure it's deleted
  Assert333(LookupHashTable(ht, FNVHashInt64(100), &kv) == 0);
  Assert333(NumElementsInHashTable(ht) == (uint64_t) 19999);

  // loop through using an iterator
  i = 0;
  iter = HashTableMakeIterator(ht);
  Assert333(iter != NULL);

  while (HTIteratorPastEnd(iter) == 0) {
    Assert333(HTIteratorGet(iter, &kv) == 1);
    Assert333(kv.key != FNVHashInt64(100));   // we deleted it

    // advance the iterator
    HTIteratorNext(iter);
    i++;
  }
  Assert333(i == 19999);

  // free the iterator
  HTIteratorFree(iter);

  // free the hash table
  FreeHashTable(ht, &ExampleValueFree);
  return 0;
}

void ExampleValueFree(void *value) {
  Assert333(value != NULL);
  free(value);
}
