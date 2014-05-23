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

#include <iostream>
#include <algorithm>

#include "./QueryProcessor.h"

extern "C" {
  #include "libhw1/Assert333.h"
}

namespace hw3 {

// Finds the intersection of two lists. There is an intersection if
// both lists contain a pair with the same first element. Returns
// a list conatins all the intersection. The second elements in
// the pairs of the returned list are the sum of counterparts in
// original lists.
static list<pair<uint64_t, uint32_t> > ListIntersection(
       const list<pair<uint64_t, uint32_t> > &l1,
       const list<pair<uint64_t, uint32_t> > &l2);

QueryProcessor::QueryProcessor(list<string> indexlist, bool validate) {
  // Stash away a copy of the index list.
  indexlist_ = indexlist;
  arraylen_ = indexlist_.size();
  Assert333(arraylen_ > 0);

  // Create the arrays of DocTableReader*'s. and IndexTableReader*'s.
  dtr_array_ = new DocTableReader *[arraylen_];
  itr_array_ = new IndexTableReader *[arraylen_];

  // Populate the arrays with heap-allocated DocTableReader and
  // IndexTableReader object instances.
  list<string>::iterator idx_iterator = indexlist_.begin();
  for (uint32_t i = 0; i < arraylen_; i++) {
    FileIndexReader fir(*idx_iterator, validate);
    dtr_array_[i] = new DocTableReader(fir.GetDocTableReader());
    itr_array_[i] = new IndexTableReader(fir.GetIndexTableReader());
    idx_iterator++;
  }
}

QueryProcessor::~QueryProcessor() {
  // Delete the heap-allocated DocTableReader and IndexTableReader
  // object instances.
  Assert333(dtr_array_ != NULL);
  Assert333(itr_array_ != NULL);
  for (uint32_t i = 0; i < arraylen_; i++) {
    delete dtr_array_[i];
    delete itr_array_[i];
  }

  // Delete the arrays of DocTableReader*'s and IndexTableReader*'s.
  delete[] dtr_array_;
  delete[] itr_array_;
  dtr_array_ = static_cast<DocTableReader **>(NULL);
  itr_array_ = static_cast<IndexTableReader **>(NULL);
}

vector<QueryProcessor::QueryResult>
QueryProcessor::ProcessQuery(const vector<string> &query) {
  Assert333(query.size() > 0);
  vector<QueryProcessor::QueryResult> finalresult;

  // MISSING:
  uint32_t i;
  for (i = 0; i < arraylen_; i++) {
    DocTableReader *dtr = dtr_array_[i];
    IndexTableReader *itr = itr_array_[i];
    list<pair<uint64_t, uint32_t> > result;

    // find the documents in this index file
    // that contain query[0]
    DocIDTableReader *didtr = itr->LookupWord(query[0]);

    // no match found in this index file, search the next index file
    if (didtr == NULL)
      continue;

    // get a list of documents (docIDs) with the ranks that contain query[0]
    result = didtr->GetDocIDList();

    // done with the DocIDTableReader, delete it
    delete didtr;

    // if there's only one query word
    if (query.size() == 1) {
      string filename;
      list<pair<uint64_t, uint32_t> >::iterator it;
      for (it = result.begin(); it != result.end(); it++) {
        // translate docIDs found into file name and store it
        // with the rank into final result
        Assert333(dtr->LookupDocID(it->first, &filename));
        QueryResult qr;
        qr.document_name = filename;
        qr.rank = it->second;
        finalresult.push_back(qr);
      }

      // Done with this index file. Search query[0] in the next index file.
      continue;
    }

    // search the rest of the query words word by word
    // if there are more than one query word
    uint32_t j;
    for (j = 1; j < query.size(); j++) {
      list<pair<uint64_t, uint32_t> > partialresult;

      // search for query[j] in this index file
      didtr = itr->LookupWord(query[j]);

      // if no match found for query[j], clear the result
      // found for previous query words and start search
      // the next index file
      if (didtr == NULL) {
        result.clear();
        break;
      }

    // get a list of documents (docIDs) with the ranks that contain query[j]
      partialresult = didtr->GetDocIDList();

      // done with the DocIDTableReader, delete it
      delete didtr;

      // store the documents that contains all query[0] to query[j] to result
      result = ListIntersection(result, partialresult);

      // no need to search for the rest of query words
      // if no match found for query[0] to query[j]
      if (result.size() == 0)
        break;
    }

    // if there are matches found
    if (result.size() != 0) {
      string filename;
      list<pair<uint64_t, uint32_t> >::iterator it;
      for (it = result.begin(); it != result.end(); it++) {
        // translate the docIDs found into file name and
        // store it into final result
        Assert333(dtr->LookupDocID(it->first, &filename));
        QueryResult qr;
        qr.document_name = filename;
        qr.rank = it->second;
        finalresult.push_back(qr);
      }
    }
  }

  // Sort the final results.
  std::sort(finalresult.begin(), finalresult.end());
  return finalresult;
}

static list<pair<uint64_t, uint32_t> > ListIntersection(
       const list<pair<uint64_t, uint32_t> > &l1,
       const list<pair<uint64_t, uint32_t> > &l2) {
  list<pair<uint64_t, uint32_t> > result;
  list<pair<uint64_t, uint32_t> >::const_iterator it1;
  list<pair<uint64_t, uint32_t> >::const_iterator it2;

  for (it1 = l1.begin(); it1 != l1.end(); it1++) {
    for (it2 = l2.begin(); it2 != l2.end(); it2++) {
      // if intersection found, append docID and sum of the ranks to result
      if (it1->first == it2->first) {
        uint32_t total_rank = it1->second + it2->second;
        result.push_back(pair<uint64_t, uint32_t>(it1->first, total_rank));
        break;
      }
    }
  }

  return result;
}
}  // namespace hw3
