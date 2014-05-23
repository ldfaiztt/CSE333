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

#include <unistd.h>

#include "./ThreadPool.h"
#include "./test_suite.h"
#include "./test_threadpool.h"

extern "C" {
  #include "./libhw1/Assert333.h"
}

namespace hw4 {

uint32_t workcount = 0;
static pthread_mutex_t mtx;

// This is the function that each dispatched thread from the thread
// pool is sent to execute.
void TestTaskFn(ThreadPool::Task *t) {
  Assert333(pthread_mutex_lock(&mtx) == 0);
  workcount++;
  Assert333(pthread_mutex_unlock(&mtx) == 0);

  if (workcount % 5 == 1) {
    usleep(250000);  // 0.25s
  }
  delete t;
}

TEST_F(Test_ThreadPool, TestThreadPoolBasic) {
  Assert333(pthread_mutex_init(&mtx, NULL) == 0);
  ThreadPool *tp = new ThreadPool(10);

  // Try dispatching some work.  Make sure we dispatch enough that
  // there will be a queue of pending tasks in the threadpool, so
  // that we can test the "delete before all tasks are done" case.
  for (int i = 0; i < 300; i++) {
    ThreadPool::Task *next_t = new ThreadPool::Task(TestTaskFn);

    tp->Dispatch(next_t);
  }
  usleep(1250000);  // 1.25s

  // Make sure that there are still tasks pending.
  ASSERT_GT((uint32_t) 300, workcount);

  // Kill off the threadpool, which should force the rest of the
  // pending tasks to be finished serially.
  delete tp;

  // Make sure all 300 tasks finished successfully.
  ASSERT_EQ((uint32_t) 300, workcount);
}

}  // namespace hw4
