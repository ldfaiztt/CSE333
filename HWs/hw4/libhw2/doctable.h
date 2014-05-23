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

#ifndef _HW2_DOCTABLE_
#define _HW2_DOCTABLE_

#include <stdint.h>
#include "libhw1/HashTable.h"

// A DocTable is a table that maps file path+names to document IDs.  A
// "document ID" is a unique uint64_t integer assigned to a specific
// file/document.  In the inverted index, we refer to documents by
// document ID rather than file path+name, to save space.  Thus, we
// need to keep this mapping between document IDs and path+names.
//
// To hide the implementation of this mapping, we define a DocTable
// in a manner similar to how we did the LinkedList and HashTable
// in hw1.
struct doctablerecord_st;
typedef struct doctablerecord_st *DocTable;

// This function allocates and returns a new DocTable.
//
// Arguments: none.
//
// Returns NULL on error, non-NULL on success.
DocTable AllocateDocTable(void);

// Frees a previously allocated DocTable, including all
// strings stored inside of it.
//
// Arguments:
//
// - table: a previously allocated DocTable.
void FreeDocTable(DocTable table);

// Returns the number of mappings inside the DocTable.
//
// Arguments:
// - table: a DocTable
//
// Returns the number of mappings within the DocTable.
uint64_t DTNumDocsInDocTable(DocTable table);

// Add a new file path+name to the DocTable and return the docID
// that was chosen for it.
//
// Arguments:
//
// - table: the DocTable to add the filename to
//
// - docname: the file path+name, relative to the current working
//   directory, of the file to add to the DocTable, e.g.,
//   "foo/bar/baz.txt" means there is a "foo/" subdirectory
//   inside the current directory, and so on.  DTRegisterDocumentName
//   makes a copy of the docname, so the client retains ownership
//   of this parameter and is responsible for freeing it.
//
// Returns:
//
// - the docID that was chosen for the document.  If the
//   document already exists inside the DocTable, its existing
//   docID is returned.
uint64_t DTRegisterDocumentName(DocTable table, char *docname);

// Checks to see if the given document path+name has been
// registered, and if so, returns its docID.
//
// Arguments:
//
// - table: the DocTable to look up the docname in
//
// - docname: the file path+name to look up.  The client retains
//   ownership of this string.
//
// Returns:
//
// - if the file path+name was previously registered, returns
//   its docID.  If the file path+name was not previously
//   registered, returns 0, a special docID that is guaranteed
//   not to be registered to any document.
uint64_t DTLookupDocumentName(DocTable table, char *docname);

// Given a docID, if that docID has been bound to a document,
// returns a string containing the file path+name for that document.
// Note that the caller must not free() this string; the DocTable
// retains ownership of that memory.
//
// Arguments:
//
// - table: the DocTable to look up the docid in
//
// - docid: the docID to lookup
//
// Returns:
//
//  - NULL if the docID couldn't be found
//
//  - a string containing the file path+name for the document,
//    e.g., "foo/bar/baz.txt"
char *DTLookupDocID(DocTable table, uint64_t docid);

// In HW3, customers will need to directly access the
// docid_to_docname HashTable that is maintained internally.
// This function lets them access that.  That HashTable
// contains HTKeyValues (as do all HashTables); the key is
// the docid, and the value is an (unsigned char *) pointing
// to a C-style string containing the document name.
//
// Arguments:
//
// - table: the DocTable from which we return the docid_to_docname
//   hashtable.
//
// Returns:
//
// - the docid_to_docname HashTable
HashTable DTGetDocidTable(DocTable table);

#endif  // _HW2_DOCTABLE_
