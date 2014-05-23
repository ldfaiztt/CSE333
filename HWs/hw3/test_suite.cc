/*
 * Copyright 2011 Steven Gribble
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

#include <iostream>
#include "gtest/gtest.h"

using std::cout;
using std::endl;

unsigned int hw3_maxpoints = 180;
unsigned int hw3_points = 0;

void HW3Addpoints(unsigned int points) {
  hw3_points += points;
  cout << " (" << hw3_points << "/" << hw3_maxpoints << ")" << endl;
}

class HW3Environment : public ::testing::Environment {
 public:

  virtual void SetUp() {
    // Code here is run once for the entire test suite.
    cout << "HW3: there are " << hw3_maxpoints << " available." << endl;
  }
  virtual void TearDown() {
    // Code here is run once for the entire test suite.
    cout << endl;
    cout << "You earned " << hw3_points << " out of ";
    cout << hw3_maxpoints << " available (";
    cout << (100.0*hw3_points) / hw3_maxpoints << "%)" << endl;
    cout << endl;
  }
};

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  ::testing::AddGlobalTestEnvironment(new HW3Environment);
  return RUN_ALL_TESTS();
}
