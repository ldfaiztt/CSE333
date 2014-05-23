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

#ifndef _HW2_FILECRAWLER_H
#define _HW2_FILECRAWLER_H

#include "memindex.h"
#include "doctable.h"

// CrawlFileTree crawls the file system subtree rooted at directory "rootdir".
// For each file that it encounters, it scans the file to test whether it
// contains ASCII text data.  If so, it indexes the file.
//
// Arguments:
//
// - rootdir: the directory that should serve as the root of the crawl.
//
// Returns:
//
// - doctable: an output parameter through which a DocTable is returned.
//   All indexed files are represented in the DocTable.
//
// - index: an output parameter through which an inverted index (i.e.,
//   a MemIndex) is returned.  All indexed files are represented in
//   the inverted index.
//
// - returns 0 on failure (nothing is allocated), 1 on success.
int CrawlFileTree(char *rootdir, DocTable *doctable, MemIndex *index);

#endif  // _HW2_FILECRAWLER_H
