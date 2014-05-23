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

// Lecture 14 exercise 2

#ifndef _LEC14_EX2_TRIPLE_H_
#define _LEC14_EX2_TRIPLE_H_

namespace lec14 {

// A "Triple" is a templated class that contains three things.
template <class T1, class T2, class T3> class Triple {
 public:
  // Constructs a triple given three things as arguments.
  Triple(const T1 &first, const T2 &second, const T3 &third)
    : first_(first), second_(second), third_(third) { }

  // Constructs a triple given a triple as an argument.
  template <class U1, class U2, class U3>
    Triple(const Triple<U1, U2, U3> &t)
    : first_(t.first_), second_(t.second_), third_(t.third_) { }

  // Constructs a triple given no arguments.
  Triple() : first_(T1()), second_(T2()), third_(T3()) { }

  // The data members.
  T1 first_;
  T2 second_;
  T3 third_;

  // Some useful typedefs.
  typedef T1 first_type;
  typedef T2 second_type;
  typedef T3 third_type;
};  // class Query

}  // namespace lec14

#endif  // _LEC14_EX2_TRIPLE_H_
