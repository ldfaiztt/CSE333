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
#include <string.h>

#include "memindex.h"
#include "libhw1/Assert333.h"
#include "libhw1/HashTable.h"

// This helper function is passed to SortLinkedList();
// it is the comparator that compares the rank of two
// search results while sorting the result list.
static int MISearchListComparator(void *e1, void *e2) {
  SearchResult *sr1 = (SearchResult *) e1;
  SearchResult *sr2 = (SearchResult *) e2;

  if (sr1->rank > sr2->rank)
    return 1;
  if (sr1->rank < sr2->rank)
    return -1;
  return 0;
}

// Used by MIListFree() to free a linked list of positions.
static void MINullFree(void *ptr) { }

// Frees a linked list of positions.
static void MIListFree(void *ptr) {
  LinkedList list = (LinkedList) ptr;
  FreeLinkedList(list, &MINullFree);
}

// Frees a WordDocSet structure.
static void MIFree(void *ptr) {
  WordDocSetPtr wd = (WordDocSetPtr) ptr;
  free(wd->word);
  FreeHashTable(wd->docIDs, &MIListFree);
  free(wd);
}

MemIndex AllocateMemIndex(void) {
  // Happily, HashTables dynamically resize themselves
  // now, so we can start by allocating a small hashtable.
  HashTable mi = AllocateHashTable(128);
  return mi;
}

void FreeMemIndex(MemIndex index) {
  FreeHashTable(index, &MIFree);
}

uint64_t MINumWordsInMemIndex(MemIndex index) {
  return NumElementsInHashTable(index);
}

int MIAddPostingList(MemIndex index, char *word, uint64_t docid,
                     LinkedList positions) {
  uint64_t wordkey = FNVHash64((unsigned char *) word, strlen(word));
  HTKeyValue kv, hitkv;
  WordDocSet *wds;
  int res;

  // STEP 1.  Remove this "return 1;".  We added this in
  // here so that your filecrawler unit tests would pass
  // even though you hadn't yet finished the memindex.c
  // implementation.

  // return 1;

  // First, we have to see if the word we're being handed
  // already exists in the inverted index.
  res = LookupHashTable(index, wordkey, &kv);
  if (res == 0) {
    // No, this is the first time the inverted index has
    // seen this word.  We need to malloc and prepare a
    // new WordDocSet structure.  After malloc'ing it,
    // we need to:
    //   (1) insert the word into the WordDocSet,
    //   (2) allocate a new hashtable for the docID->positions mapping,
    //   (3) insert that hashtable into the WordDocSet, and
    //   (4) insert the the new WordDocSet into the inverted
    //       index (i.e., into the "index" table).

    // STEP 2.
    wds = (WordDocSet *) malloc(sizeof(WordDocSet));
    Assert333(wds != NULL);

    wds->word = word;

    wds->docIDs = AllocateHashTable(128);
    Assert333(wds->docIDs != NULL);

    kv.key = wordkey;
    kv.value = (void *) wds;
    res = InsertHashTable(index, kv, &hitkv);
    Assert333(res == 1);
  } else {
    // Yes, this word already exists in the inverted index.
    // So, there's no need to insert it again; we can go
    // ahead and free the word.
    free(word);

    // Instead of allocating a new WordDocSet, we'll
    // use the one that's already in the inverted index.
    wds = (WordDocSet *) kv.value;
  }

  // Verify that the docID doesn't exist in the WordDocSet.
  res = LookupHashTable(wds->docIDs, docid, &hitkv);
  Assert333(res == 0);

  // Insert a new entry into the wds->docIDs hash table.
  // The entry's key is this docID and the entry's value
  // is the "positions" word positions list we were passed
  // as an argument.

  // STEP 3.
  kv.key = docid;
  kv.value = (void *) positions;
  res = InsertHashTable(wds->docIDs, kv, &hitkv);
  Assert333(res == 1);

  return 1;
}

LinkedList MIProcessQuery(MemIndex index, char *query[], uint8_t qlen) {
  LinkedList retlist;
  HTKeyValue kv;
  WordDocSet *wds;
  int res;
  uint64_t wordkey;

  // If the user provided us with an empty search query, return NULL
  // to indicate failure.
  if (qlen == 0)
    return NULL;

  // Allocate a linked list to store our search results.  A search
  // result is just a list of SearchResult structures.
  retlist = AllocateLinkedList();
  Assert333(retlist != NULL);

  // The most interesting part of Part C starts here...!
  //
  // Look up the first query word (query[0]) in the inverted
  // index.  For each document that matches, allocate a SearchResult
  // structure.  Initialize that SearchResult structure with the
  // docID, and the initial computed rank for the document.  (The
  // initial computed rank is the number of times the word appears
  // in that document.)
  //
  // Then, append the SearchResult structure onto retlist.
  //
  // If there are no matching documents, free retlist and return NULL.

  // STEP 4.
  wordkey = FNVHash64((unsigned char *) query[0], strlen(query[0]));
  res = LookupHashTable(index, wordkey, &kv);
  Assert333(res != -1);

  // no matching documents found
  if (res == 0) {
    FreeLinkedList(retlist, &free);
    return NULL;
  }

  // create an iterator to iterate through matching documents
  wds = (WordDocSet *) (kv.value);
  HTIter htit = HashTableMakeIterator(wds->docIDs);
  Assert333(htit != NULL);

  while (!HTIteratorPastEnd(htit)) {
    // get the document and position list for the query word
    res = HTIteratorGet(htit, &kv);
    Assert333(res == 1);

    // initialize SearchResult with the document's id and rank
    SearchResult *sr = (SearchResult *) malloc(sizeof(SearchResult));
    Assert333(sr != NULL);
    sr->docid = kv.key;
    sr->rank = (uint32_t) NumElementsInLinkedList((LinkedList) kv.value);

    // add SearchResult of the document into retlist
    Assert333(AppendLinkedList(retlist, sr));
    HTIteratorNext(htit);
  }
  HTIteratorFree(htit);

  // Great; we have our search results for the first query
  // word.  If there is only one query word, we're done!
  // Sort the result list and return it to the caller.
  if (qlen == 1) {
    SortLinkedList(retlist, 0, &MISearchListComparator);
    return retlist;
  }

  // OK, there are additional query words.  Handle them one
  // at a time.
  int i;
  for (i = 1; i < qlen; i++) {
    LLIter llit;
    int j, ne;

    // Look up the next query word (query[i]) in the inverted index.
    // If there are no matches, it means the overall query
    // should return no documents, so free retlist and return NULL.

    // STEP 5.
    wordkey = FNVHash64((unsigned char *) query[i], strlen(query[i]));
    res = LookupHashTable(index, wordkey, &kv);
    Assert333(res != -1);

    // no matching documents found
    if (res == 0) {
      FreeLinkedList(retlist, &free);
      return NULL;
    }

    // There are matches.  We're going to iterate through
    // the docIDs in our current search result list, testing each
    // to see whether it is also in the set of matches for
    // the query[i].
    //
    // If it is, we leave it in the search
    // result list and we update its rank by adding in the
    // number of matches for the current word.
    //
    // If it isn't, we delete that docID from the search result list.
    wds = (WordDocSet *) kv.value;
    llit = LLMakeIterator(retlist, 0);
    ne = NumElementsInLinkedList(retlist);
    for (j = 0; j < ne; j++) {
      // STEP 6.
      SearchResult *sr;
      LLIteratorGetPayload(llit, (void **) &sr);
      // check if the document currently in the retlist
      // is also in the WordDocSet of the word query[i]
      res = LookupHashTable(wds->docIDs, sr->docid, &kv);
      Assert333(res != -1);

      if (res == 0) {
        // delete the document which doesn't contain the word query[i]
        res = LLIteratorDelete(llit, &free);
      } else {
        // update the rank of the document's search result
        // by number of appearance of the word query[i] in the document
        sr->rank += (uint32_t) NumElementsInLinkedList((LinkedList) kv.value);
        LLIteratorNext(llit);
      }
    }
    LLIteratorFree(llit);
  }

  // We've finished processing all of the query words.
  // If there are no documents left in our query result list,
  // free retlist and return NULL.
  if (NumElementsInLinkedList(retlist) == 0) {
    FreeLinkedList(retlist, &free);
    return NULL;
  }

  // Sort the result list by rank and return it to the caller.
  SortLinkedList(retlist, 0, &MISearchListComparator);
  return retlist;
}
