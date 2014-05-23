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

#include <assert.h>
#include <iostream>

#include "./ThreadPool.h"

extern "C" {
  #include "./libhw1/Assert333.h"
}

namespace hw4 {

// This is the thread start routine, i.e., the function that threads
// are born into.
void *ThreadLoop(void *tpool);

ThreadPool::ThreadPool(uint32_t num_threads) {
  // Initialize our member variables.
  num_threads_running_ = 0;
  killthreads_ = false;
  Assert333(pthread_mutex_init(&qlock_, NULL) == 0);
  Assert333(pthread_cond_init(&qcond_, NULL) == 0);

  // Allocate the array of pthread structures.
  thread_array_ = new pthread_t[num_threads];

  // Spawn the threads one by one, passing them a pointer to self
  // as the argument to the thread start routine.
  Assert333(pthread_mutex_lock(&qlock_) == 0);
  for (uint32_t i = 0; i < num_threads; i++) {
    Assert333(pthread_create(&(thread_array_[i]),
                             NULL,
                             &ThreadLoop,
                             static_cast<void *>(this)) == 0);
  }

  // Wait for all of the threads to be born and initialized.
  while (num_threads_running_ != num_threads) {
    Assert333(pthread_mutex_unlock(&qlock_) == 0);
    Assert333(pthread_mutex_lock(&qlock_) == 0);
  }
  Assert333(pthread_mutex_unlock(&qlock_) == 0);

  // Done!  The thread pool is ready, and all of the worker threads
  // are initialized and waiting on qcond_ to be notified of available
  // work.
}

ThreadPool:: ~ThreadPool() {
  Assert333(pthread_mutex_lock(&qlock_) == 0);
  uint32_t num_threads = num_threads_running_;

  // Tell all of the worker threads to kill themselves.
  killthreads_ = true;

  // Join with the running threads 1-by-1 until they have all died.
  for (uint32_t i = 0; i < num_threads; i++) {
    // Use a sledgehammer and broadcast every loop iteration, just to
    // be extra-certain that worker threads wake up and see the "kill
    // yourself" flag.
    Assert333(pthread_cond_broadcast(&qcond_) == 0);
    Assert333(pthread_mutex_unlock(&qlock_) == 0);
    Assert333(pthread_join(thread_array_[i], NULL) == 0);
    Assert333(pthread_mutex_lock(&qlock_) == 0);
  }

  // All of the worker threads are dead, so clean up the thread
  // structures.
  Assert333(num_threads_running_ == 0);
  if (thread_array_ != NULL) {
    delete[] thread_array_;
  }
  thread_array_ = NULL;
  Assert333(pthread_mutex_unlock(&qlock_) == 0);

  // Empty the task queue, serially issuing any remaining work.
  while (!work_queue_.empty()) {
    Task *nextTask = work_queue_.front();
    work_queue_.pop_front();
    nextTask->f_(nextTask);
  }
}

// Enqueue a Task for dispatch.
void ThreadPool::Dispatch(Task *t) {
  Assert333(pthread_mutex_lock(&qlock_) == 0);
  Assert333(killthreads_ == false);
  work_queue_.push_back(t);
  Assert333(pthread_cond_signal(&qcond_) == 0);
  Assert333(pthread_mutex_unlock(&qlock_) == 0);
}

// This is the main loop that all worker threads are born into.  They
// wait for a signal on the work queue condition variable, then they
// grab work off the queue.  Threads return (i.e., kill themselves)
// when they notice that killthreads_ is true.
void *ThreadLoop(void *tpool) {
  ThreadPool *pool = static_cast<ThreadPool *>(tpool);

  // Grab the lock, increment the thread count so that the ThreadPool
  // constructor knows this new thread is alive.
  Assert333(pthread_mutex_lock(&(pool->qlock_)) == 0);
  pool->num_threads_running_++;

  // This is our main thread work loop.
  while (pool->killthreads_ == false) {
    // Wait to be signaled that something has happened.
    Assert333(pthread_cond_wait(&(pool->qcond_), &(pool->qlock_)) == 0);

    // Keep trying to dequeue work until the work queue is empty.
    while (!pool->work_queue_.empty() && (pool->killthreads_ == false)) {
      ThreadPool::Task *nextTask = pool->work_queue_.front();
      pool->work_queue_.pop_front();

      // We picked up a Task, so invoke the task function with the
      // lock released, then check so see if more tasks are waiting to
      // be picked up.
      Assert333(pthread_mutex_unlock(&(pool->qlock_)) == 0);
      nextTask->f_(nextTask);
      Assert333(pthread_mutex_lock(&(pool->qlock_)) == 0);
    }
  }

  // All done, exit.
  pool->num_threads_running_--;
  Assert333(pthread_mutex_unlock(&(pool->qlock_)) == 0);
  return NULL;
}

}  // namespace hw4
