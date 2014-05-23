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

// lec 12 exercise 1

#ifndef _LEC12_EX1_HISTOGRAM_H_
#define _LEC12_EX1_HISTOGRAM_H_

#include <stdint.h>  // for uint32_t
#include <iostream>  // for std::ostream
#include <string>    // for std::string
#include <vector>    // for std::vector
#include <map>       // for std::map
#include <utility>   // for std::pair

using std::string;
using std::ostream;
using std::vector;
using std::pair;
using std::map;

// A Histogram is a class that builds up a histogram of word
// occurrence frequency. Internally, it uses an STL map to store
// a map from word to integer count.
class Histogram {
 public:
  Histogram() { }

  // Add a word occurrence to the histogram.  Converts the word to
  // lowercase before incorporating.
  void AddWord(string word);

  // Return a vector of <word,count> pairs, sorted in descending order
  // of count.
  vector<pair<string, uint32_t> > GetSortedData() const;

  // Override "<<" for std::ostream.
  friend ostream &operator<<(ostream &out, const Histogram &pt);

 private:
  // Disable the copy constructor and assignment operator.
  Histogram(const Histogram &pt);
  Histogram &operator=(const Histogram &pt);

  // Our private member variable storing the histogram data.
  // We use an STL map from word-->count.
  map<string, uint32_t> histogram_data_;
};

#endif  // _LEC12_EX1_HISTOGRAM_H_
