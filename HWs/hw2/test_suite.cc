/*
 * Copyright 2012 Steven Gribble
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

#include "gtest/gtest.h"

using std::cout;
using std::endl;

unsigned int hw2_maxpoints = 270;
unsigned int hw2_points = 0;

void HW2ResetPoints() {
  hw2_points = 0;
}

void HW2Addpoints(unsigned int points) {
  hw2_points += points;
  cout << " (" << hw2_points << "/" << hw2_maxpoints << ")" << endl;
}

class HW2Environment : public ::testing::Environment {
 public:

  virtual void SetUp() {
    // Code here is run once for the entire test suite.
    cout << "HW2: there are " << hw2_maxpoints;
    cout << " points available." << endl;
  }
  virtual void TearDown() {
    // Code here is run once for the entire test suite.
    cout << endl;
    cout << "You earned " << hw2_points << " out of ";
    cout << hw2_maxpoints << " points available (";
    cout << ((100.0*hw2_points) / hw2_maxpoints) << "%)" << endl;
    cout << endl;
  }
};

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  ::testing::AddGlobalTestEnvironment(new HW2Environment);
  return RUN_ALL_TESTS();
}
