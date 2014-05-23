/*
 * Copyright 2011, 2013 Steven Gribble, Hal Perkins
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

#include <iostream>
#include <sstream>

#include "./Tracer.h"

using namespace std;

Tracer::Tracer() {
  id_ = Tracer::nextid_++;
  value_ = id_;
  cout << "Tracer" << PrintID() << endl;
}

Tracer::~Tracer() {
  cout << "~Tracer" << PrintID() << endl;
}

Tracer::Tracer(const Tracer &rhs) {
  id_ = Tracer::nextid_++;
  value_ = id_;
  cout << "TracerCopy[" << PrintID();
  cout << "<--" << rhs.PrintID() << "]" << endl;
  value_ = rhs.value_;
}

Tracer &Tracer::operator=(const Tracer &rhs) {
  cout << "Tracer" << PrintID() << "=" << rhs.PrintID() << endl;
  value_ = rhs.value_;
  return *this;
}

bool Tracer::operator<(const Tracer &rhs) const {
  cout << "Tracer" << PrintID() << "<" << rhs.PrintID() << endl;
  return value_ < rhs.value_;
}

std::string Tracer::PrintID(void) const {
  stringstream ss;
  string paren("("), comma(","), closeparen(")");
  ss << paren << id_ << comma << value_ << closeparen;
  return ss.str();
}

std::ostream &operator<<(std::ostream &out, const Tracer &rhs) {
  out << "(" << rhs.id_ << "," << rhs.value_ << ")";
  return out;
}

unsigned int Tracer::nextid_ = 0;
