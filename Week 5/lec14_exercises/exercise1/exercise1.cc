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

// lec 14 exercise 1

#include <boost/shared_ptr.hpp>
#include <iostream>
#include <stdlib.h>
#include "./Query.h"
#include "./PhrasedQuery.h"

using namespace lec14;

int main(int argc, char **argv) {
  // Test the Query class; create a query.
  Query *q = new Query();
  q->AddWord("ocean");
  q->AddWord("whale");
  std::cout << "'ocean whale' query:  '" << q->Print() << "'" << std::endl;

  // Exercise the methods of a Query object.
  std::list<std::string> qwords = q->get_query();
  std::list<std::string>::iterator it;
  for (it = qwords.begin(); it != qwords.end(); it++) {
    std::cout << "  " << *it;
  }
  std::cout << std::endl;
  Query q2 = Query();
  std::cout << "blank query:  '" << q2.Print() << "'" << std::endl;

  // Test the PhrasedQuery class; create a phrased query and populate it
  // with queries.
  Query firstphrase;
  firstphrase.AddWord("ocean");
  firstphrase.AddWord("whale");
  Query secondphrase;
  secondphrase.AddWord("happy");
  secondphrase.AddWord("days");
  PhrasedQuery *pq = new PhrasedQuery();
  pq->AddPhrase(firstphrase.get_query());
  pq->AddPhrase(secondphrase.get_query());
  pq->AddWord("hello");
  std::cout << "phrased query: '" << pq->Print() << "'" << std::endl;

  // Test out the methods of a PhrasedQuery.
  std::list<Query> pqqueries = pq->get_phrased_query();
  std::list<Query>::iterator it2;
  for (it2 = pqqueries.begin(); it2 != pqqueries.end(); it2++) {
    std::cout << "  " << (*it2).Print() << std::endl;
  }
  std::cout << std::endl;
  PhrasedQuery pq2 = PhrasedQuery();
  std::cout << "empty phrased query: '" << pq->Print() << "'" << std::endl;

  // Create a list of shared_ptrs of Queries.
  std::list<boost::shared_ptr<Query> > qlist;

  // Add in our Query and Phrased query.
  qlist.push_back(boost::shared_ptr<Query>(q));
  qlist.push_back(boost::shared_ptr<Query>(pq));

  // Print all the queries.
  std::cout << std::endl << "Printing shared_ptr list:" << std::endl;
  std::list<boost::shared_ptr<Query> >::iterator it3;
  for (it3 = qlist.begin(); it3 != qlist.end(); it3++) {
    std::cout << " " << (*it3)->Print() << std::endl;
  }

  return EXIT_SUCCESS;
}
