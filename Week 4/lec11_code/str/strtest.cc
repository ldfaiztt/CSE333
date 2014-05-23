// CSE 333 Lecture 11 demo: strtest.cc
// Perkins

// Test program for a simple string class.
// Demonstrates string class with constructors, destructors,
// and assignment.  Trace output from Str.cc will show when
// the various constructors and destructor are called.

#include <iostream>
using namespace std;

#include "Str.h"

// print message to show progress
void here(int n) {
  cout << "main: " << n << endl;
}

// id(x) == x (tests copy construtor)
Str id(Str s) {
  return s;
}

// create some strings and play with them
int main() {
  // local variables in main's stack frame
  // (destructor is called when main exits)
  Str s1, s2;            // default constructors
  Str hello("hello");    // c-string constructor
  Str howdy = hello;     // copy constructor

  here(1);

  // get c-string from Str
  char *hi = howdy.c_str();
  cout << hi << endl;
  delete [] hi;

  here(2);

  // test append (constructs a Str and destructs it)
  hello.append(" there");
  cout << hello << endl;
  cout << "  length is " << hello.length() << endl;

  here(3);

  // assignment operator and Str(char *) constructor
  s1 = "howdy";
  cout << s1 << endl;

  here(4);

  // copy constructors
  s2 = id(hello);
  cout << s2 << endl;

  here(5);

  // heap allocated Str object
  // (uses copy constructor)
  // (destructor called when object deleted)
  // (same general idea as a Java String, but in C++)
  Str * h = new Str(hello);
  h->append(" y'all");
  cout << *h << endl;
  cout << "  length is " << h->length() << endl;
  delete h;

  here(6);

  // Enough already!!
  return 0;
}

