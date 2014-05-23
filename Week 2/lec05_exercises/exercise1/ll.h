/*
 * Copyright 2011 Steven Gribble
 *
 *  This file is the solution to an exercise problem posed during
 *  one of the UW CSE 333 lectures (333exercises).
 *
 *  333exercises is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  333exercises is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with 333exercises.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _LL_H_
#define _LL_H_

// A "Node" is the structure we use as a node in a linked
// list.
typedef struct Node {
  void *element;      // the payload of the node
  struct Node *next;  // the next node in the list, or NULL if at tail
} Node;

// Allocate and push a new node onto the head of the linked list.
// Deliberately crashes with a failed assertion if there is
// an out-of-memory error.
//
// Arguments:
//
// - head:    the current head of the linked list
// - element: the payload of the new node
//
//
// Returns:
//
// - the new head of the linked list
Node *Push(Node *head, void *element);

// Pop and deallocate the node that is at the head of the
// linked list.
//
// Arguments:
//
// - old_head: the current head of the linked list
//
// - new_head: a return parameter through which the new
//   head of the linked list is returned if the pop
//   operation was successful.
//
// Returns:
//
// - the payload (i.e., element field) of the node that
//   was popped and deallocated, or NULL if the linked
//   was empty (i.e., old_head was NULL).  If the linked
//   list was null.
void *Pop(Node *old_head, Node **new_head);

// Returns the number of elements in a linked list.
//
// Arguments:
//
// - head: the head of the linked list
//
// Returns:
//
// - the number of elements in the linked list otherwise
unsigned int NumElements(Node *head);

#endif  // _LL_H_
