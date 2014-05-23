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

#include <sstream>
#include <cctype>

#include "GetWord.h"

using namespace std;

string GetWord::GetNextWord() {
  stringstream ss;
  string retstr = "";

  // Zoom ahead to the start of the next word, or return
  // empty string if we hit EOF first.
  while (f_.good()) {
    char c;

    c = f_.peek();
    if (!f_.good())
      return retstr;
    if (isalnum(c))
      break;
    f_.get(c);
  }

  // Keep chomping until we hit the end of the word or EOF.
  while (f_.good()) {
    char c;

    f_.get(c);
    if (f_.good()) {
      if (isalnum(c))
        ss << c;
      else
        break;
    }
  }

  // Done with the word; return it.
  return ss.str();
}
