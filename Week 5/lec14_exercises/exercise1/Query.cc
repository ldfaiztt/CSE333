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

// Lecture 14 exercise 1

#include <cctype>
#include <algorithm>
#include <sstream>

#include "./Query.h"

namespace lec14 {

Query::Query(std::list<std::string> initial_wordlist) {
  // Make sure all of the words are lower-cased as we insert them into
  // our wordlist_.
  std::list<std::string>::iterator it;
  for (it = initial_wordlist.begin();
       it != initial_wordlist.end();
       it++) {
    std::string word = *it;
    std::transform(word.begin(), word.end(), word.begin(),
                   (int(*)(int)) std::tolower);
    wordlist_.push_back(word);
  }
}


void Query::AddWord(std::string word) {
  // Convert the word to lowercase.
  std::transform(word.begin(), word.end(), word.begin(),
                 (int(*)(int)) std::tolower);

  // Test to see if the word already exists.
  std::list<std::string>::iterator it;
  for (it = wordlist_.begin(); it != wordlist_.end(); it++) {
    std::string next = *it;
    if (next == word)
      return;
  }

  // We don't yet have the word in the query, so add it.
  wordlist_.push_back(word);
}

std::string Query::Print() const {
  std::stringstream ss;

  std::list<std::string>::const_iterator it;
  for (it = wordlist_.begin(); it != wordlist_.end(); it++) {
    std::string next = *it;
    if (it == wordlist_.begin()) {
      ss << next;
    } else {
      ss << " " << next;
    }
  }
  return ss.str();
}

std::list<std::string> Query::get_query() const {
  return wordlist_;
}

}  // namespace lec14
