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

#include <algorithm>

#include "./Histogram.h"

using std::sort;
using std::endl;
using std::cout;  // for debugging

// lec 12 exercise 1

// Add a word occurrence to the histogram.  Converts the word to
// lowercase before incorporating.
void Histogram::AddWord(string word) {
  // std::map overrides the [] operator, and does a nice thing: if the
  // key is not in the hashtable yet, it is created as a side-effect
  // of the lookup and initialized with a zero-equivalent.  So, this
  // lookup does exactly the right thing (return zero) if the word
  // isn't yet in the table!
  std::transform(word.begin(), word.end(), word.begin(), ::tolower);
  uint32_t oldval = histogram_data_[word];
  histogram_data_[word] = oldval + 1;
}

// This utility function is passed as an argument to std::sort from
// #include <algorithm> as a comparator.  It is used inside
// GetSortedData().
static bool CompareHistPair(pair<string, uint32_t> a,
                            pair<string, uint32_t> b) {
  // Deliberately reverse the comparison so we can sort in descending
  // order, instead sort()'s default of ascending order.
  return a.second > b.second;
}

// Return a vector of <word,count> pairs, sorted in descending order
// of count.
vector<pair<string, uint32_t> > Histogram::GetSortedData() const {
  vector<pair<string, uint32_t> > data;

  // Iterate through the map, inserting pairs into the "data" vector.
  // This is horrific, but because we declared GetSortedData() to be
  // a const function, the compiler prevents us from constructing a
  // regular iterator to a member variable, and instead we need to
  // construct a const_iterator.  Wow!!
  map<string, uint32_t>::const_iterator it = histogram_data_.begin();
  map<string, uint32_t>::const_iterator endit = histogram_data_.end();
  for (it = histogram_data_.begin(); it != histogram_data_.end(); it++) {
    pair<string, uint32_t> nextpair(it->first, it->second);
    data.push_back(nextpair);
  }

  // Sort the "data" vector.
  sort(data.begin(), data.end(), &CompareHistPair);
  return data;
}

// Override "<<" for std::ostream.
ostream &operator<<(ostream &out, const Histogram &pt) {
  vector<pair<string, uint32_t> > data = pt.GetSortedData();
  for (uint32_t i = 0; i < data.size(); i++) {
    string word = data[i].first;
    uint32_t count = data[i].second;
    out << word << " " << count << endl;
  }
  return out;
}
