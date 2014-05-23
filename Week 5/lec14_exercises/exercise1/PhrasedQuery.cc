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

#include <sstream>

#include "./Query.h"
#include "./PhrasedQuery.h"

namespace lec14 {

PhrasedQuery::PhrasedQuery(std::list<Query> initial_phraselist) {
  querylist_ = initial_phraselist;
}

void PhrasedQuery::AddWord(std::string word) {
  Query newq;
  newq.AddWord(word);
  querylist_.push_back(newq);
}

void PhrasedQuery::AddPhrase(std::list<std::string> query) {
  Query newq(query);
  querylist_.push_back(newq);
}

std::string PhrasedQuery::Print() const {
  std::stringstream ss;
  std::list<Query>::const_iterator it;

  for (it = querylist_.begin(); it != querylist_.end(); it++) {
    std::string nexts;
    Query nextq = *it;

    std::list<std::string> qlist = nextq.get_query();
    if (qlist.size() > 1) {
      nexts = "\"" + nextq.Print() + "\"";
    } else {
      nexts = nextq.Print();
    }

    if (it == querylist_.begin()) {
      ss << nexts;
    } else {
      ss << " " << nexts;
    }
  }
  return ss.str();
}

std::list<Query> PhrasedQuery::get_phrased_query() const {
  return querylist_;
}

}  // namespace lec14
