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

#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <iostream>
#include "./fileindexwriter.h"

extern "C" {
  #include "./libhw2/filecrawler.h"
  #include "./libhw2/doctable.h"
  #include "./libhw2/memindex.h"
}

void Usage(char *filename) {
  std::cerr << "Usage: " << filename;
  std::cerr << " crawlrootdir indexfilename" << std::endl;
  std::cerr << "where:" << std::endl;
  std::cerr << "  crawlrootdir is the name of a directory to crawl";
  std::cerr << std::endl;
  std::cerr << "  indexfilename is the name of the index file to create";
  std::cerr << std::endl;
  exit(EXIT_FAILURE);
}

// This program links together the HW2 CrawlFileTree() from
// filecrawler.c with the HW3 WriteIndexFile() from
// fileindexwrite.cc. Using them, the program crawls the file system
// subtree specified by argv[1], builds up an in-memory index, and then
// writes it out to the index file specified by argv[2].
int main(int argc, char **argv) {
  uint32_t idxlen;
  DocTable dt;
  MemIndex idx;

  // Make sure the user provided us the right command-line options.
  if (argc != 3)
    Usage(argv[0]);

  // Try to crawl.
  std::cout << "Crawling " << argv[1] << "..." << std::endl;
  if (CrawlFileTree(argv[1], &dt, &idx) != 1)
    Usage(argv[0]);

  // Try to write out the index file.
  std::cout << "Writing index to " << argv[2];
  std::cout << "..." << std::endl;
  idxlen = hw3::WriteIndex(idx, dt, argv[2]);
  if (idxlen == 0) {
    FreeDocTable(dt);
    FreeMemIndex(idx);
    return EXIT_FAILURE;
  }

  // All done!  Clean up.
  std::cout << "Done. Cleaning up memory." << std::endl;
  FreeDocTable(dt);
  FreeMemIndex(idx);
  return EXIT_SUCCESS;
}
