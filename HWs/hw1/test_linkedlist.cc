/*
 * Copyright 2012 Steven Gribble.
 *    [with contributions from cse333 students.]
 *
 *  This file is part of the UW CSE333 project sequence (333proj).
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

#include <stdint.h>
#include <unistd.h>
#include <errno.h>
#include <sys/select.h>

extern "C" {
  #include "./LinkedList.h"
  #include "./LinkedList_priv.h"
}

#include "./test_suite.h"
#include "./test_linkedlist.h"

namespace hw1 {

// static
uint64_t Test_LinkedList::kOne = 1;
uint64_t Test_LinkedList::kTwo = 2;
uint64_t Test_LinkedList::kThree = 3;
uint64_t Test_LinkedList::kFour = 4;
uint64_t Test_LinkedList::kFive = 5;

static unsigned int free_count = 0U;
void PayloadFreeFunction(void *payload) {
  // Do nothing but verify the payload is non-NULL and
  // increment the free count.
  ASSERT_NE(static_cast<void *>(NULL), payload);
  free_count++;
}

int TestPayloadComparator(void *p1, void *p2) {
  // A comparator used to test sort.
  uint64_t i1 = *reinterpret_cast<uint64_t*>(p1);
  uint64_t i2 = *reinterpret_cast<uint64_t*>(p2);

  if (i1 > i2)
    return 1;
  if (i1 < i2)
    return -1;
  return 0;
}

TEST_F(Test_LinkedList, TestLinkedListBasic) {
  // Try creating a list.
  LinkedList llp = AllocateLinkedList();
  ASSERT_NE((LinkedList) NULL, llp);
  ASSERT_EQ(0U, NumElementsInLinkedList(llp));
  ASSERT_EQ(NULL, llp->head);
  ASSERT_EQ(NULL, llp->tail);
  HW1Addpoints(5);

  // Try deleting the (empty) list.
  free_count = 0U;
  FreeLinkedList(llp, &PayloadFreeFunction);
  ASSERT_EQ(0U, free_count);
  llp = NULL;
  HW1Addpoints(5);
}

TEST_F(Test_LinkedList, TestLinkedListPushPop) {
  // Creating a list.
  LinkedList llp = AllocateLinkedList();
  ASSERT_NE(static_cast<LinkedList>(NULL), llp);
  ASSERT_EQ(0U, NumElementsInLinkedList(llp));
  ASSERT_EQ(NULL, llp->head);
  ASSERT_EQ(NULL, llp->tail);

  // Insert an element.
  ASSERT_TRUE(PushLinkedList(llp, reinterpret_cast<void *>(&kOne)));
  ASSERT_EQ(1U, NumElementsInLinkedList(llp));
  ASSERT_EQ(llp->head, llp->tail);
  ASSERT_EQ(NULL, llp->head->prev);
  ASSERT_EQ(NULL, llp->tail->next);
  ASSERT_EQ(kOne, *reinterpret_cast<uint64_t*>(llp->head->payload));
  HW1Addpoints(10);

  // Delete the element.
  void *payload_ptr;
  ASSERT_TRUE(PopLinkedList(llp, &payload_ptr));
  ASSERT_EQ(kOne, *reinterpret_cast<uint64_t*>(payload_ptr));
  ASSERT_EQ(0U, NumElementsInLinkedList(llp));
  HW1Addpoints(10);

  // Delete the element a second time.
  ASSERT_FALSE(PopLinkedList(llp, &payload_ptr));
  HW1Addpoints(5);

  // Insert two elements.
  ASSERT_TRUE(PushLinkedList(llp, reinterpret_cast<void *>(&kOne)));
  ASSERT_EQ(1U, NumElementsInLinkedList(llp));
  ASSERT_EQ(llp->head, llp->tail);
  ASSERT_EQ(NULL, llp->head->prev);
  ASSERT_EQ(NULL, llp->tail->next);
  ASSERT_EQ(kOne, *reinterpret_cast<uint64_t*>(llp->head->payload));

  ASSERT_TRUE(PushLinkedList(llp, reinterpret_cast<void *>(&kTwo)));
  ASSERT_EQ(2U, NumElementsInLinkedList(llp));
  ASSERT_NE(llp->head, llp->tail);
  ASSERT_EQ(NULL, llp->head->prev);
  ASSERT_EQ(NULL, llp->tail->next);
  ASSERT_EQ(llp->tail, llp->head->next);
  ASSERT_EQ(llp->head, llp->tail->prev);
  ASSERT_EQ(kTwo, *reinterpret_cast<uint64_t*>(llp->head->payload));
  ASSERT_EQ(kOne, *reinterpret_cast<uint64_t*>(llp->tail->payload));
  HW1Addpoints(10);

  // Delete the first element.
  ASSERT_TRUE(PopLinkedList(llp, &payload_ptr));
  ASSERT_EQ(kTwo, *reinterpret_cast<uint64_t*>(payload_ptr));
  ASSERT_EQ(1U, NumElementsInLinkedList(llp));
  ASSERT_EQ(llp->head, llp->tail);
  ASSERT_EQ(NULL, llp->head->prev);
  ASSERT_EQ(NULL, llp->tail->next);
  ASSERT_EQ(kOne, *reinterpret_cast<uint64_t*>(llp->head->payload));
  HW1Addpoints(10);

  // Delete the non-empty list.
  free_count = 0U;
  FreeLinkedList(llp, &PayloadFreeFunction);
  ASSERT_EQ(1U, free_count);
  llp = NULL;
}

TEST_F(Test_LinkedList, TestLinkedListAppendSlice) {
  // Creating a list.
  LinkedList llp = AllocateLinkedList();
  ASSERT_NE((LinkedList) NULL, llp);
  ASSERT_EQ(0U, NumElementsInLinkedList(llp));
  ASSERT_EQ(NULL, llp->head);
  ASSERT_EQ(NULL, llp->tail);

  // Insert an element.
  ASSERT_TRUE(AppendLinkedList(llp, reinterpret_cast<void *>(&kOne)));
  ASSERT_EQ(1U, NumElementsInLinkedList(llp));
  ASSERT_EQ(llp->head, llp->tail);
  ASSERT_EQ(NULL, llp->head->prev);
  ASSERT_EQ(NULL, llp->tail->next);
  ASSERT_EQ(kOne, *reinterpret_cast<uint64_t*>(llp->head->payload));
  HW1Addpoints(5);

  // Delete the element.
  void *payload_ptr;
  ASSERT_TRUE(SliceLinkedList(llp, &payload_ptr));
  ASSERT_EQ(kOne, *reinterpret_cast<uint64_t*>(payload_ptr));
  ASSERT_EQ(0U, NumElementsInLinkedList(llp));
  HW1Addpoints(5);

  // Delete the element a second time.
  ASSERT_FALSE(SliceLinkedList(llp, &payload_ptr));
  HW1Addpoints(5);

  // Insert two elements.
  ASSERT_TRUE(AppendLinkedList(llp, reinterpret_cast<void *>(&kOne)));
  ASSERT_EQ(1U, NumElementsInLinkedList(llp));
  ASSERT_EQ(llp->head, llp->tail);
  ASSERT_EQ(NULL, llp->head->prev);
  ASSERT_EQ(NULL, llp->tail->next);
  ASSERT_EQ(kOne, *reinterpret_cast<uint64_t*>(llp->head->payload));

  ASSERT_TRUE(AppendLinkedList(llp, reinterpret_cast<void *>(&kTwo)));
  ASSERT_EQ(2U, NumElementsInLinkedList(llp));
  ASSERT_NE(llp->head, llp->tail);
  ASSERT_EQ(NULL, llp->head->prev);
  ASSERT_EQ(NULL, llp->tail->next);
  ASSERT_EQ(llp->tail, llp->head->next);
  ASSERT_EQ(llp->head, llp->tail->prev);
  ASSERT_EQ(kOne, *reinterpret_cast<uint64_t*>(llp->head->payload));
  ASSERT_EQ(kTwo, *reinterpret_cast<uint64_t*>(llp->tail->payload));
  HW1Addpoints(5);

  // Delete the first element.
  ASSERT_TRUE(SliceLinkedList(llp, &payload_ptr));
  ASSERT_EQ(reinterpret_cast<void *>(&kTwo), payload_ptr);
  ASSERT_EQ(1U, NumElementsInLinkedList(llp));
  ASSERT_EQ(llp->head, llp->tail);
  ASSERT_EQ(NULL, llp->head->prev);
  ASSERT_EQ(NULL, llp->tail->next);
  ASSERT_EQ(kOne, *reinterpret_cast<uint64_t*>(llp->head->payload));
  HW1Addpoints(5);

  // Delete the non-empty list.
  free_count = 0U;
  FreeLinkedList(llp, &PayloadFreeFunction);
  ASSERT_EQ(1U, free_count);
  llp = NULL;
}

TEST_F(Test_LinkedList, TestLinkedListSort) {
  // Creating a list.
  LinkedList llp = AllocateLinkedList();
  ASSERT_NE((LinkedList) NULL, llp);
  ASSERT_EQ(0U, NumElementsInLinkedList(llp));
  ASSERT_EQ(NULL, llp->head);
  ASSERT_EQ(NULL, llp->tail);

  // Insert some elements.
  ASSERT_TRUE(AppendLinkedList(llp, reinterpret_cast<void *>(&kThree)));
  ASSERT_EQ(1U, NumElementsInLinkedList(llp));
  ASSERT_TRUE(AppendLinkedList(llp, reinterpret_cast<void *>(&kTwo)));
  ASSERT_EQ(2U, NumElementsInLinkedList(llp));
  ASSERT_TRUE(AppendLinkedList(llp, reinterpret_cast<void *>(&kOne)));
  ASSERT_EQ(3U, NumElementsInLinkedList(llp));

  // Sort ascending.
  SortLinkedList(llp, 1, &TestPayloadComparator);

  // Verify the sort.
  ASSERT_EQ(kOne, *reinterpret_cast<uint64_t*>(llp->head->payload));
  ASSERT_EQ(kTwo, *reinterpret_cast<uint64_t*>(llp->head->next->payload));
  ASSERT_EQ(kThree, *reinterpret_cast<uint64_t*>(llp->head->next->next->payload));
  ASSERT_EQ(NULL, llp->head->next->next->next);

  // Resort descending.
  SortLinkedList(llp, 0, &TestPayloadComparator);

  // Verify the sort.
  ASSERT_EQ(kThree, *reinterpret_cast<uint64_t*>(llp->head->payload));
  ASSERT_EQ(kTwo, *reinterpret_cast<uint64_t*>(llp->head->next->payload));
  ASSERT_EQ(kOne, *reinterpret_cast<uint64_t*>(llp->head->next->next->payload));
  ASSERT_EQ(NULL, llp->head->next->next->next);
  HW1Addpoints(5);

  // Delete the non-empty list.
  free_count = 0U;
  FreeLinkedList(llp, &PayloadFreeFunction);
  ASSERT_EQ(3U, free_count);
  llp = NULL;
}

TEST_F(Test_LinkedList, TestLLIteratorBasic) {
  // Create a linked list.
  LinkedList llp = AllocateLinkedList();

  // Make sure you can't create an iterator to an empty list.
  ASSERT_EQ(NULL, LLMakeIterator(llp, 0));
  HW1Addpoints(5);

  // Add some data to the list.
  ASSERT_TRUE(AppendLinkedList(llp, reinterpret_cast<void *>(&kThree)));
  ASSERT_TRUE(AppendLinkedList(llp, reinterpret_cast<void *>(&kTwo)));
  ASSERT_TRUE(AppendLinkedList(llp, reinterpret_cast<void *>(&kOne)));

  // Create the iterator.
  LLIter lli = LLMakeIterator(llp, 0);
  ASSERT_NE(static_cast<LLIter>(NULL), lli);
  ASSERT_TRUE(LLIteratorHasNext(lli));
  ASSERT_FALSE(LLIteratorHasPrev(lli));
  ASSERT_EQ(llp, lli->list);
  ASSERT_EQ(llp->head, lli->node);
  HW1Addpoints(5);

  // Navigate using the iterator.
  void *payload;
  ASSERT_FALSE(LLIteratorPrev(lli));
  ASSERT_TRUE(LLIteratorNext(lli));
  LLIteratorGetPayload(lli, &payload);
  ASSERT_EQ(kTwo, *reinterpret_cast<uint64_t*>(payload));
  ASSERT_TRUE(LLIteratorHasNext(lli));
  ASSERT_TRUE(LLIteratorHasPrev(lli));
  ASSERT_TRUE(LLIteratorNext(lli));
  LLIteratorGetPayload(lli, &payload);
  ASSERT_EQ(kOne, *reinterpret_cast<uint64_t*>(payload));
  ASSERT_FALSE(LLIteratorHasNext(lli));
  ASSERT_TRUE(LLIteratorHasPrev(lli));
  ASSERT_FALSE(LLIteratorNext(lli));
  ASSERT_TRUE(LLIteratorPrev(lli));
  LLIteratorGetPayload(lli, &payload);
  ASSERT_EQ(kTwo, *reinterpret_cast<uint64_t*>(payload));
  HW1Addpoints(10);

  // Do an insert-before from the middle element.
  ASSERT_TRUE(LLIteratorInsertBefore(lli, reinterpret_cast<void *>(&kFour)));
  LLIteratorGetPayload(lli, &payload);
  ASSERT_EQ(kTwo, *reinterpret_cast<uint64_t*>(payload));
  ASSERT_TRUE(LLIteratorPrev(lli));
  LLIteratorGetPayload(lli, &payload);
  ASSERT_EQ(kFour, *reinterpret_cast<uint64_t*>(payload));

  // Rewind to beginning, try insert-before.
  ASSERT_TRUE(LLIteratorPrev(lli));
  ASSERT_FALSE(LLIteratorHasPrev(lli));
  LLIteratorGetPayload(lli, &payload);
  ASSERT_EQ(kThree, *reinterpret_cast<uint64_t*>(payload));
  ASSERT_TRUE(LLIteratorInsertBefore(lli, reinterpret_cast<void *>(&kFive)));
  LLIteratorGetPayload(lli, &payload);
  ASSERT_EQ(kThree, *reinterpret_cast<uint64_t*>(payload));
  ASSERT_TRUE(LLIteratorPrev(lli));
  ASSERT_FALSE(LLIteratorHasPrev(lli));
  LLIteratorGetPayload(lli, &payload);
  ASSERT_EQ(kFive, *reinterpret_cast<uint64_t*>(payload));
  HW1Addpoints(10);

  // The list contains 5 elements. Try a delete from the front of the list.
  // (i.e., delete element 1/5.)
  free_count = 0;
  LinkedListNodePtr prev, next = lli->node->next;
  ASSERT_TRUE(LLIteratorDelete(lli, &PayloadFreeFunction));
  ASSERT_EQ(next, lli->node);
  ASSERT_EQ(NULL, lli->node->prev);
  ASSERT_EQ(4U, NumElementsInLinkedList(lli->list));
  ASSERT_EQ(1U, free_count);
  LLIteratorGetPayload(lli, &payload);
  ASSERT_EQ(kThree, *reinterpret_cast<uint64_t*>(payload));
  ASSERT_FALSE(LLIteratorHasPrev(lli));
  HW1Addpoints(10);

  // Delete the rest.
  // Move the iterator forward by one to test removing from the middle.
  // Deleting element 2/4
  ASSERT_TRUE(LLIteratorNext(lli));
  prev = lli->node->prev;
  next = lli->node->next;
  ASSERT_TRUE(LLIteratorDelete(lli, &PayloadFreeFunction));
  ASSERT_EQ(3U, NumElementsInLinkedList(lli->list));
  ASSERT_EQ(next, lli->node);
  ASSERT_EQ(prev, lli->node->prev);

  // Delete from the middle. Deleting element 2/3
  next = lli->node->next;
  prev = lli->node->prev;
  ASSERT_TRUE(LLIteratorDelete(lli, &PayloadFreeFunction));
  ASSERT_EQ(2U, NumElementsInLinkedList(lli->list));
  ASSERT_EQ(next, lli->node);
  ASSERT_EQ(prev, lli->node->prev);

  // Delete from the tail position. Deleting element 2/2.
  prev = lli->node->prev;
  ASSERT_TRUE(LLIteratorDelete(lli, &PayloadFreeFunction));
  ASSERT_EQ(1U, NumElementsInLinkedList(lli->list));
  ASSERT_EQ(NULL, lli->node->next);
  ASSERT_EQ(prev, lli->node);

  // Remove the remaining node from the list. Deleting element 1/1.
  ASSERT_FALSE(LLIteratorDelete(lli, &PayloadFreeFunction));
  ASSERT_EQ(0U, NumElementsInLinkedList(lli->list));
  ASSERT_EQ(NULL, lli->node);
  ASSERT_EQ(5U, free_count);

  // Free the iterator.
  LLIteratorFree(lli);
  HW1Addpoints(5);

  // Free the list.
  FreeLinkedList(llp, &PayloadFreeFunction);
}

}  // namespace hw1
