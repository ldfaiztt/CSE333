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

#include <list>    // for std::list
#include <string>  // for std::string

#include "./Query.h"

#ifndef _LEC14_EX1_PHRASED_QUERY_
#define _LEC14_EX1_PHRASED_QUERY_

namespace lec14 {

// A "PhrasedQuery" is a derived class that contains a phrased query,
// i.e., a list of Queries, each of which might be a single word and
// each of which might have multiple words as a phrase.
class PhrasedQuery : public Query {
 public:
  // Constructs an empty phrased query; use AddWord() or AddPhrase()
  // to add a word or a phrase to the query.
  PhrasedQuery() { }

  // Constructs a query with the given list of words.
  PhrasedQuery(std::list<Query> initial_phraselist);

  // Make the destructor virtual; this is good hygiene, since it
  // guarantees that the full class hierarchy below Query has virtual
  // destructors.
  virtual ~PhrasedQuery() { }

  // Adds a word to the phrased query.  If the word already exists as
  // part of the query, this doesn't add it.
  virtual void AddWord(std::string word);

  // Adds a phrase to the phrased query.
  virtual void AddPhrase(std::list<std::string> query);

  // Prints the phrased query.
  virtual std::string Print() const;

  // Gets a copy of the phrased query.
  std::list<Query> get_phrased_query() const;

 private:
  // The list of queries in this phrased query.
  std::list<Query> querylist_;
};  // class PhrasedQuery

}  // namespace lec14

#endif  // _LEC14_EX1_PHRASED_QUERY_
