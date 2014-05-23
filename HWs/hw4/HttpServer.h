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

#ifndef _HW4_HTTPSERVER_H_
#define _HW4_HTTPSERVER_H_

#include <stdint.h>
#include <string>
#include <list>

#include "./ThreadPool.h"
#include "./ServerSocket.h"

namespace hw4 {

// The HttpServer class contains the main logic for the web server.
class HttpServer {
 public:
  // Creates a new HttpServer object for port "port" and serving
  // files out of path "staticfile_dirpath".  The indices for
  // query processing are located in the "indices" list. The constructor
  // does not do anything except memorize these variables.
  explicit HttpServer(uint16_t port,
                      std::string staticfile_dirpath,
                      std::list<std::string> indices)
    : ss_(port), staticfile_dirpath_(staticfile_dirpath),
    indices_(indices), kNumThreads(100) { }

  // The destructor closes the listening socket if it is open and
  // also kills off any threads in the threadpool.
  virtual ~HttpServer(void) { }

  // Creates a listening socket for the server and launches it, accepting
  // connections and dispatching them to worker threads.  Returns
  // "true" if the server was able to start and run, "false" otherwise.
  // The server continues to run until the secret "kill me" URL is
  // visited.
  bool Run(void);

 private:
  ServerSocket ss_;
  std::string staticfile_dirpath_;
  std::list<std::string> indices_;
  const int kNumThreads;
};

class HttpServerTask : public ThreadPool::Task {
 public:
  explicit HttpServerTask(ThreadPool::thread_task_fn f)
    : ThreadPool::Task(f) { }

  int client_fd;
  uint16_t cport;
  std::string caddr, cdns, saddr, sdns;
  std::string basedir;
  std::list<std::string> *indices;
};

}  // namespace hw4

#endif  // _HW4_HTTPSERVER_H_
