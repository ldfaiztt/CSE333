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

// lec 11 exercise 2

#ifndef _LEC11_EX2_GETWORD_H_
#define _LEC11_EX2_GETWORD_H_

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// A "GetWord" is a class that can be used to open a file and
// read successive white-space-separated, ASCII words from
// the file.
class GetWord {
 public:
  // Constructor.  Throws an exception on error.
  GetWord(string filename) : filename_(filename) {
    // We'll temporarily elevate the exceptions bitmask on
    // f_ so that an exception is thrown if we encounter an
    // error while opening filename.
    f_.exceptions(ifstream::failbit);

    // Try to open filename_.
    f_.open(filename_.c_str(), ifstream::in);

    // Clear the exceptions bitmask, so no more exceptions
    // are thrown.
    f_.exceptions(ifstream::goodbit);
  }

  // Destructor.
  ~GetWord() {
    if (f_.is_open())
      f_.close();
  }

  // Get the next word from the file.  Returns a non-empty
  // string if there is a next word, or an empty string
  // if we've hit EOF.
  string GetNextWord();

 private:
  // Disable the copy constructor and assignment operator.
  GetWord(const GetWord &gw);
  GetWord &operator=(const GetWord &gw);

  string filename_;
  ifstream f_;
};

#endif  // _LEC11_EX2_GETWORD_H_
