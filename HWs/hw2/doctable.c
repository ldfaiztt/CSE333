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
#include <string.h>

#include "doctable.h"
#include "libhw1/Assert333.h"
#include "libhw1/HashTable.h"

// This structure represents a DocTable; it contains two hash tables, one
// mapping from docid to docname, and one mapping from docname to docid.
typedef struct doctablerecord_st {
  HashTable docid_to_docname;  // mapping docid to docname
  HashTable docname_to_docid;  // mapping docname to docid
  uint64_t max_id;             // max docID allocated so far
} DocTableRecord;

DocTable AllocateDocTable(void) {
  DocTableRecord *dt = (DocTableRecord *) malloc(sizeof(DocTableRecord));
  Assert333(dt != NULL);

  dt->docid_to_docname = AllocateHashTable(1024);
  dt->docname_to_docid = AllocateHashTable(1024);
  dt->max_id = 0;

  Assert333(dt->docid_to_docname != NULL);
  Assert333(dt->docname_to_docid != NULL);
  return dt;
}

void FreeDocTable(DocTable table) {
  Assert333(table != NULL);

  // STEP 1.
  FreeHashTable(table->docid_to_docname, &free);
  FreeHashTable(table->docname_to_docid, &free);

  free(table);
}

uint64_t DTNumDocsInDocTable(DocTable table) {
  Assert333(table != NULL);
  return NumElementsInHashTable(table->docid_to_docname);
}

uint64_t DTRegisterDocumentName(DocTable table, char *docname) {
  // Allocate space for the docid.
  char       *doccopy;
  uint64_t   *docid = (uint64_t *) malloc(sizeof(uint64_t));
  uint64_t   res;
  HTKeyValue kv, oldkv;
  int retval;

  // Make a copy of the docname.
  doccopy = (char *) malloc(1+strlen(docname));
  if (doccopy != NULL) {
    strncpy(doccopy, docname, 1+strlen(docname));
  }
  Assert333(table != NULL);
  Assert333(doccopy != NULL);
  Assert333(docid != NULL);

  // Check to see if the document already exists; if so,
  // free up the malloc'ed space and return the existing docid

  // STEP 2.
  // use the hash value of the document name to check if
  // the document already exists.
  res = FNVHash64((unsigned char *) doccopy, strlen(doccopy));
  retval = LookupHashTable(table->docname_to_docid, res, &oldkv);
  Assert333(retval != -1);

  if (retval == 1) {
    free(doccopy);
    free(docid);
    // get the docid stored in oldkv's value and return it to the caller
    return *((uint64_t *) oldkv.value);
  }

  // allocate the next docID
  table->max_id += 1;
  *docid = table->max_id;

  // Set up the key/value for the docid_to_docname mapping, and
  // do the insert.

  // STEP 3.
  kv.key = *docid;
  kv.value = doccopy;
  retval = InsertHashTable(table->docid_to_docname, kv, &oldkv);
  Assert333(retval == 1);

  // Set up the key/value for the docname_to_docid mapping, and
  // do the insert.

  // STEP 4.
  kv.key = res;
  kv.value = docid;
  retval = InsertHashTable(table->docname_to_docid, kv, &oldkv);
  Assert333(retval == 1);

  return *docid;
}

uint64_t DTLookupDocumentName(DocTable table, char *docname) {
  uint64_t key;
  HTKeyValue kv;
  int res;

  Assert333(table != NULL);
  Assert333(docname != NULL);

  // Lookup the FNVHash64() or the docname in the
  // docname_to_docid table within dt, and return
  // either "0" if the docname isn't found or the
  // docID if it is.

  // STEP 5.
  key = FNVHash64((unsigned char *) docname, strlen(docname));
  res = LookupHashTable(table->docname_to_docid, key, &kv);
  Assert333(res != -1);

  if (res == 0)
    return 0;
  return *((uint64_t *) kv.value);
}

char *DTLookupDocID(DocTable table, uint64_t docid) {
  HTKeyValue kv;
  int res;

  Assert333(table != NULL);
  Assert333(docid != 0);

  // Lookup the docid in the docid_to_docname table,
  // and either return the string (i.e., the (char *)
  // saved in the value field for that key) or
  // NULL if the key isn't in the table.

  // STEP 6.
  res = LookupHashTable(table->docid_to_docname, docid, &kv);
  Assert333(res != -1);

  if (res == 0)
    return NULL;
  return ((char *) kv.value);
}

HashTable DTGetDocidTable(DocTable table) {
  Assert333(table != NULL);
  return table->docid_to_docname;
}
