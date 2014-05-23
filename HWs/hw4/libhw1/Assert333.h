/*
 * Copyright 2012 Steven Gribble
 *
 *  This file is part of the UW CSE333 project sequence (333proj).
 *
 *  333proj is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published
 *  by the Free Software Foundation, either version 3 of the License,
 *  or (at your option) any later version.
 *
 *  333proj is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with 333proj. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _HW1_ASSERT333_H_
#define _HW1_ASSERT333_H_

// A wrapper for assert that permits side-effects within the
// Assert333() statement.  Borrowed from:
//
//   http://www.acm.uiuc.edu/sigops/roll_your_own/2.a.html

void AssertionFailure(const char *exp, const char *file,
                      const char *basefile, int line);

#define Assert333(exp) if (exp) ; \
  else AssertionFailure(#exp, __FILE__, __BASE_FILE__, __LINE__)

#endif  // _HW1_ASSERT333_H_
