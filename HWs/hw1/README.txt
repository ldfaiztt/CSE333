/*
 * Copyright 2012 Steven Gribble
 *
 *  This file is part of the UW CSE 333 project sequence (333proj).
 *
 *  333proj is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published
 *  by the Free Software Foundation, either version 3 of the License,
 *  or (at your option) any later version.
 *
 *  333proj is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with 333proj.  If not, see <http://www.gnu.org/licenses/>.
 */

Inside this directory, you'll find the following:

 - Makefile: the gnu Makefile to compile hw1; to run it, just type
   "make" at the command line

 - Makefile.coverage: recompiles test_suite with gcov's code
   coverage instrumentation, and generates the coverage data.
   Once you have your code working, type "make -f Makefile.coverage"
   to produce the data, then look at LinkedList.c.gcov and
   HashTable.c.gcov to see the actual coverage data.

 - LinkedList.h: the public header for the doubly-linked list module.
   This header contains all of the definitions, typedefs, and function
   prototypes upon which customers depend.

 - LinkedList_priv.h: a private header to expose some of the internal
   implementation details of the linked list module.  The unit test
   code uses this private header to get access to those internals.

 - LinkedList.c: the implementation of the linked list module.

 - HashTable.h, HashTable_priv.h, HashTable.c: similar to the linked list
   files, but for a chained hash table implementation.

 - test_*.cc, test_*.h: the unit test code.  Look at test_linkedlist.cc
   for an example of the unit tests that exercise the linked list.

After you compile, you'll have access to two executables:

 - test_suite:  run the unit tests against your code.  This will
   crash out and print an error if a unit test fails.  Once you're
   able to make it all the way through, your code is doing pretty
   well. Try to come up with other test cases we might not have
   implemented, of course.

 - example_program_ll, example_program_ht:  exercises the linked list
   and AVL tree code, respectively.


