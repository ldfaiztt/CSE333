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
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#include "memindex.h"
#include "filecrawler.h"
#include "libhw1/Assert333.h"

static void Usage(void);

int main(int argc, char **argv) {
  if (argc != 2)
    Usage();

  // Implement searchshell!  We're giving you very few hints
  // on how to do it, so you'll need to figure out an appropriate
  // decomposition into functions as well as implementing the
  // functions.  There are several major tasks you need to build:
  //
  //  - crawl from a directory provided by argv[1] to produce and index
  //  - prompt the user for a query and read the query from stdin, in a loop
  //  - split a query into words (check out strtok_r)
  //  - process a query against the index and print out the results
  char input[1024];
  char *token;
  char *saveptr;
  DocTable doctable;
  MemIndex index;
  LinkedList searchresult;
  LLIter llit;
  SearchResult *rs;

  printf("Indexing \'%s\'\n", argv[1]);
  // crawl from directory argv[1]
  if (CrawlFileTree(argv[1], &doctable, &index) == 0) {
    // terminate the program if crawl failed
    Usage();
  }

  Assert333(doctable != NULL);
  Assert333(index != NULL);

  while (1) {
    // ask for user input
    printf("enter query:\n");
    if (fgets(input, 1024, stdin) != NULL) {
      // malloc space in order to store tokens
      // split from user input
      char **query = (char **) malloc(512 * sizeof(char *));
      Assert333(query != NULL);

      uint8_t qlen = 0;
      char *str = input;
      // whenever we see the space in the input, split it
      // and store it into array
      while (1) {
        token = strtok_r(str, " ", &saveptr);
        // jump out of loop if there are no more tokens
        if (token == NULL)
          break;
        query[qlen] = token;
        qlen++;
        str = NULL;
      }

      // replace last token's '\n' by '\0' since fgets
      // also read '\n' into input
      char *p = strchr(query[qlen - 1], '\n');
      if (p)
        *p = '\0';

      // search for the documents that contains
      // all the words in the query
      searchresult = MIProcessQuery(index, query, qlen);
      if (searchresult != NULL) {
        llit = LLMakeIterator(searchresult, 0);
        Assert333(llit != NULL);

        // print out all the matching documents under
        // the directory argv[1] and the rank for the query
        do {
          LLIteratorGetPayload(llit, (void **) &rs);
          printf("  %s (%u)\n", DTLookupDocID(doctable, rs->docid), rs->rank);
        } while (LLIteratorNext(llit));

        LLIteratorFree(llit);
      }

      free(query);
    }
  }

  FreeDocTable(doctable);
  FreeMemIndex(index);

  return EXIT_SUCCESS;
}

static void Usage(void) {
  fprintf(stderr, "Usage: ./searchshell <docroot>\n");
  fprintf(stderr,
          "where <docroot> is an absolute or relative " \
          "path to a directory to build an index under.\n");
  exit(-1);
}
