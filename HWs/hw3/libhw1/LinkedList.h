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
 *  along with 333proj. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _HW1_LINKEDLIST_H_
#define _HW1_LINKEDLIST_H_

#include <stdbool.h>  // for bool type (true, false)
#include <stdint.h>   // for uint64_t

// A LinkedList is a doubly-linked list.  We provide the interface to the
// LinkedList here; your job is to fill in the implementation holes that we
// left in LinkedList.c.

// To hide the implementation of LinkedList, we declare the "struct ll_head"
// structure here, but we *define* the structure in the internal header
// LinkedList_priv.h. This lets us define a pointer to LinkedList as a new
// type while leaving the implementation details opaque to the customer.
struct ll_head;
typedef struct ll_head *LinkedList;

// When a customer frees a linked list, they need to pass a pointer to a
// function that frees the payload of a linked list node. We invoke the
// pointed-to function once for each node in the linked list, before the
// LinkedListPtr itself is freed.
typedef void(*LLPayloadFreeFnPtr)(void *payload);

// When sorting a linked list or comparing two elements of a linked list,
// customers must pass in a comparator function.  The function accepts two
// payload pointers as arguments and returns an integer that is:
//
//    -1  if payload_a < payload_b
//     0  if payload_a == payload_b
//    +1  if payload_a > payload_b
typedef int(*LLPayloadComparatorFnPtr)(void *payload_a, void *payload_b);

// Allocate and return a new linked list.  The caller takes responsibility for
// eventually calling FreeLinkedList to free memory associated with the list.
//
// Arguments: none.
//
// Returns: NULL on error, non-NULL on success.
LinkedList AllocateLinkedList(void);

// Free a linked list that was previously allocated by AllocateLinkedList.
//
// Arguments:
//
// - list: the linked list to free.  It is unsafe to use "list" after this
//   function returns.
//
// - payload_free_function: a pointer to a payload freeing function; see above
//   for details on what this is.
void FreeLinkedList(LinkedList list,
                    LLPayloadFreeFnPtr payload_free_function);

// Return the number of elements in the linked list.
//
// Arguments:
//
// - list:  the list to query
//
// Returns:
//
// - list length
uint64_t NumElementsInLinkedList(LinkedList list);

// Adds a new element to the head of the linked list.
//
// Arguments:
//
// - list: the LinkedList to push onto
//
// - payload: the payload to push; it's up to the caller to interpret and
//   manage the memory of the payload.
//
// Returns false on failure, true on success.
bool PushLinkedList(LinkedList list, void *payload);

// Pop an element from the head of the linked list.
//
// Arguments:
//
// - list: the LinkedList to pop from
//
// - payload_ptr: a return parameter that is set by the callee; on success,
//   the payload is returned through this parameter.
//
// Returns false on failure, true on success.
bool PopLinkedList(LinkedList list, void **payload_ptr);

// Adds a new element to the tail of the linked list.
//
// Arguments:
//
// - list: the LinkedList to push onto
//
// - payload: the payload to push; it's up to the caller to interpret and
//   manage the memory of the payload.
//
// Returns false on failure, true on success.
bool AppendLinkedList(LinkedList list, void *payload);

// Pop an element from the tail of the linked list.
//
// Arguments:
//
// - list: the LinkedList to pop from
//
// - payload_ptr: a return parameter that is set by the callee; on success,
//   the payload is returned through this parameter.
//
// Returns false on failure, true on success.
bool SliceLinkedList(LinkedList list, void **payload_ptr);

// Sorts a LinkedList in place.
//
// Arguments:
//
// - list: the list to sort
//
// - ascending: if 0, sorts descending, else sorts ascending.
//
// - comparator_function:  this argument is a pointer to a payload comparator
//   function; see above.
void SortLinkedList(LinkedList list, unsigned int ascending,
                    LLPayloadComparatorFnPtr comparator_function);

// Linked lists support the notion of an iterator, similar to Java iterators.
// You use an iterator to navigate back and forth through the linked list and
// to insert/remove elements from the list.  You use LLMakeIterator() to
// manufacture a new iterator and LLIteratorFree() to free an iterator when
// you're done with it.
//
// If you use a LinkedList*() function to mutate a linked list, any iterators
// you have on that list become dangerous to use (so dangerous that arbitrary
// memory corruption can occur). Thus, you should only use LLIterator*()
// functions in between the manufacturing and freeing of an iterator.
struct ll_iter;
typedef struct ll_iter *LLIter;  // same trick to hide implementation.

// Manufacture an iterator for the list.  Customers can use the iterator to
// advance forwards or backwards through the list, kind of like a cursor.
// Caller is responsible for eventually calling LLIteratorFree to free memory
// associated with the iterator.
//
// Arguments:
//
// - list: the list from which we'll return an iterator
//
// - pos: where to start (0 = head, 1 = tail)
//
// Returns NULL on failure (out of memory, empty list) or non-NULL on success.
LLIter LLMakeIterator(LinkedList list, int pos);

// When you're done with an iterator, you must free it by calling this
// function.
//
// Arguments:
//
// - iter: the iterator to free. Don't use it after freeing it.
void LLIteratorFree(LLIter iter);

// Test whether the iterator can advance forward.
//
// Arguments:
//
// - iter: the iterator
//
// Returns:
//
// - true if the iterator can advance (is not at tail)
//
// - false if the iterator cannot advance (is at the tail)
bool LLIteratorHasNext(LLIter iter);

// Advance the iterator, i.e. move to the next node in the
// list.
//
// Arguments:
//
// - iter: the iterator
//
// Returns:
//
// true: if the iterator has been advanced to the next node
//
// false: if the iterator is at the last node and cannot
// be advanced
bool LLIteratorNext(LLIter iter);

// Test whether the iterator can advance backwards.
//
// Arguments:
//
// - iter: the iterator
//
// Returns:
//
// - true if the iterator can advance (is not at head)
//
// - false if the iterator cannot advance (is at the head)
bool LLIteratorHasPrev(LLIter iter);

// Rewind the iterator, i.e. move to the previous node in the
// list.
//
// Arguments:
//
// - iter: the iterator
//
// Returns:
//
// true: if the iterator has been shifted to the previous node
//
// false: if the iterator is at the first node and cannot be
// shifted back any more
bool LLIteratorPrev(LLIter iter);

// Returns the payload of the list node that the iterator currently
// points at.
//
// Arguments:
//
// - iter: the iterator to fetch the payload from.
//
// - payload: a "return parameter" through which the payload is returned.
void LLIteratorGetPayload(LLIter iter, void **payload);

// Delete the node the iterator is pointing to.  After deletion, the iterator:
//
// - is invalid and cannot be used (but must be freed), if there was only one
//   element in the list
//
// - the successor of the deleted node, if there is one.
//
// - the predecessor of the deleted node, if the iterator was pointing at
//   the tail.
//
// Arguments:
//
// - iter:  the iterator to delete from
//
// - payload_free_function: invoked to free the payload
//
// Returns:
//
// - false if the deletion succeeded, but the list is now empty
//
// - true if the deletion succeeded, and the list is still non-empty
bool LLIteratorDelete(LLIter iter,
                      LLPayloadFreeFnPtr payload_free_function);

// Insert an element right before the node that the interator points
// to.  (If you want to insert at the end of a list, use
// AppendLinkedList.)
//
// Arguments:
//
// - iter: the iterator to insert through
//
// - payload: the payload to insert
//
// Returns:
//
// - false on failure (out of memory)
//
// - true on success; the iterator still points to the same node,
//   not to the inserted node.
bool LLIteratorInsertBefore(LLIter iter, void *payload);

#endif  // _HW1_LINKEDLIST_H_
