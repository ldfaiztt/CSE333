#include <iostream>
#include <sstream>

#include "Tracer.h"

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
