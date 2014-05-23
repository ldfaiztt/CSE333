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

#include <stdint.h>
#include <unistd.h>
#include <iostream>
#include <string>

#include "./HttpUtils.h"
#include "./ServerSocket.h"
#include "./ThreadPool.h"
#include "./test_suite.h"

#include "./test_serversocket.h"

namespace hw4 {

static uint16_t portnum;

void TestSSThreadFn(ThreadPool::Task *t) {
  // Create the server socket.
  int listen_fd;
  std::cout << "Creating ss on " << portnum << std::endl;
  ServerSocket ss(portnum);
  std::cout << "Doing BAL" << std::endl;
  ASSERT_TRUE(ss.BindAndListen(AF_UNSPEC, &listen_fd));

  // Accept a connection.
  int accept_fd;
  uint16_t cport;
  std::string caddr, cdns, saddr, sdns;
  std::cout << "Doing accept..." << std::endl;
  ASSERT_TRUE(ss.Accept(&accept_fd, &caddr, &cport, &cdns, &saddr, &sdns));

  // It worked!
  std::cout << "Accept succeeded." << std::endl;
  close(accept_fd);
  return;
}

TEST_F(Test_ServerSocket, TestServerSocketBasic) {
  // Create a threadpool, and dispatch a thread to go listen on a
  // server socket on a random port.
  portnum = GetRandPort();
  ThreadPool tp(2);
  ThreadPool::Task tsk(&TestSSThreadFn);
  tp.Dispatch(&tsk);

  // Give the thread a chance to create the socket.
  sleep(1);

  // Connect to the socket, using hw2's SocketClient.
  std::cout << "attempting to connect to 127.0.0.1 port "
            << portnum << std::endl;
  int cfd = -1;
  ASSERT_TRUE(ConnectToServer("127.0.0.1", portnum, &cfd));
  ASSERT_LE(0, cfd);
  HW4Addpoints(20);
}

}  // namespace hw4
