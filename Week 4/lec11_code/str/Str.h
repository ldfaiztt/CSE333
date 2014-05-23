// CSE 333 Lecture 11 demo: Str.h
// Perkins

// Specification of a simple string class.
// A Str object wraps an ordinary C-string to make a C++ object with
// some basic operations.  Each str owns a dynamically allocated char
// array that holds the underlying \0-terminated C string.

#ifndef _STR_H_
#define _STR_H_

#include <iostream>    // for stream output

class Str {
 public:
  // constructors
  // create empty string
  Str();

  // create Str from c-string s
  Str(const char *s);

  // copy constructor - initialize this to be a copy of s
  Str(const Str &s);

  // destructor
  ~Str();

  // return length of this string
  int length() const;

  // return a new c-string allocated on the heap with
  // a copy of this Str's string data
  char * c_str() const;

  // append contents of s to the end of this string
  void append(const Str &s);

  // string assignment
  Str & operator=(const Str &s);

  // stream output (global function, not class member)
  friend std::ostream &operator<<(std::ostream &out, const Str &s);

 private:
  // Str representation
  char *st_;        // c-string on heap with data bytes terminated by \0
};

#endif
