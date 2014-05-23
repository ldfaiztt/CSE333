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

#ifndef _LEC14_EX1_QUERY_H_
#define _LEC14_EX1_QUERY_H_

namespace lec14 {

// A "Query" is a base class that contains a query, i.e., a list
// of single-word strings.
class Query {
 public:
  // Constructs an empty query; use AddWord() to add a word to the
  // query.
  Query() { }

  // Constructs a query with the given list of words.
  Query(std::list<std::string> initial_wordlist);

  // Make the destructor virtual; this is good hygiene, since it
  // guarantees that the full class hierarchy below Query has virtual
  // destructors.
  virtual ~Query() { }

  // Adds a word to the query.  If the word already exists as part
  // of the query, this doesn't add it.
  virtual void AddWord(std::string word);

  // Return a string with the query.
  virtual std::string Print() const;

  // Returns a copy of the query.
  virtual std::list<std::string> get_query() const;

 private:
  // The list of words in this query.
  std::list<std::string> wordlist_;
};  // class Query

}  // namespace lec14

#endif  // _LEC14_EX1_QUERY_H_
