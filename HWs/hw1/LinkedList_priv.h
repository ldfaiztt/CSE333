/*
 * Copyright 2012 Steven Gribble
 *
 *  This file is part of the UW CSE333 project sequence (333proj).
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

#ifndef _HW1_LINKEDLIST_PRIV_H_
#define _HW1_LINKEDLIST_PRIV_H_

#include <stdint.h>      // for uint64_t
#include "./LinkedList.h"  // for LinkedList and LLIter

// This file defines the internal structures associated with our LinkedList
// implementation.  Customers should not include this file or assume anything
// based on its contents.  Instead, we have broken these out into this file so
// that the unit test code for LinkedList has access to it, allowing unit
// tests to peek inside the implementation to check pointers and fields for
// correctness.

// This struct represents an individual node within a linked list.  A node
// contains next and prev pointers as well as a customer-supplied payload
// pointer.
typedef struct ll_node {
  void           *payload;  // customer-supplied payload pointer
  struct ll_node *next;     // next node in list, or NULL
  struct ll_node *prev;     // prev node in list, or NULL
} LinkedListNode, *LinkedListNodePtr;

// This struct represents the entire linked list.  We provided a struct
// declaration (but not definition) in LinkedList.h; this is the associated
// definition.  This struct contains metadata about the linked list.
typedef struct ll_head {
  uint64_t          num_elements;  //  # elements in the list
  LinkedListNodePtr head;  // head of linked list, or NULL if empty
  LinkedListNodePtr tail;  // tail of linked list, or NULL if empty
} LinkedListHead;

// This struct represents the state of an iterator.  We expose the struct
// declaration in LinkedList.h, but not the definition, similar to what we did
// above for the linked list itself.
typedef struct ll_iter {
  LinkedList        list;  // the list we're for
  LinkedListNodePtr node;  // the node we are at, or NULL if broken
} LLIterSt;

#endif  // _HW1_LINKEDLIST_PRIV_H_
