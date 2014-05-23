// CSE 333 Lecture 11 demo: Str.cc
// Perkins

// Implementation of a simple string class.

#include <cstring>
#include <iostream>
#include "Str.h"

using namespace std;

// Print trace messages to show when functions get called.
#define TRACE(what)  cout << "Str::" << what << " called" << endl

// constructors

Str::Str() {
  TRACE("default constructor");
  // allocate empty string
  st_ = new char[1];
  st_[0] = '\0';
}

Str::Str(const char *s) {
  TRACE("c-string constructor");
  int len = strlen(s);
  st_ = new char[len+1];
  strcpy(st_, s);
}

Str::Str(const Str &s) {
  TRACE("copy constructor");
  int len = strlen(s.st_);
  st_ = new char[len+1];
  strcpy(st_, s.st_);
}

// destructor
Str::~Str() {
  TRACE("destructor");
  delete [] st_;
}

// operations

int Str::length() const {
  return strlen(st_);
}

char * Str::c_str() const {
  char * result = new char[strlen(st_)+1];
  strcpy(result, st_);
  return result;
}


void Str::append(const Str &s) {
  char *newst = new char[strlen(st_) + strlen(s.st_) + 1];
  strcpy(newst, st_);
  strcat(newst, s.st_);
  delete [] st_;
  st_ = newst;
}

Str & Str::operator=(const Str &s) {
  TRACE("assignment");
  // do nothing if trying to assign a string to itself
  if (this == &s) {
    return *this;
  }

  // Allocate space for data if source length is different
  if (strlen(st_) != strlen(s.st_)) {
    delete [] st_;
    st_ = new char[strlen(s.st_)+1];
  }

  // copy characters and return
  strcpy(st_, s.st_);
  return *this;
}

// stream output
ostream &operator<<(ostream &out, const Str &s) {
  out << s.st_;
  return out;
}
