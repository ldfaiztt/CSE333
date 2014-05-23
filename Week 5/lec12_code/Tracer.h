#ifndef _TRACER_H_
#define _TRACER_H_

#include <iostream>
#include <string>

// This class is useful when you are exploring the behavior of STL
// containers.  The class gives each instance that is manufactured
// using the default constructor a unique ID and a current value.  The
// current value is initialized to be the unique ID.
//
// Whenever an object is manufactured using the copy constructor, its
// value is copied from the argument.  Similarly, whenever an object
// is the target of an assignment operator, then its value is copied
// from the source.
//
// Finally, objects print messages out whenever important events
// happen, including default construction, copy construction,
// destruction, assignment, and "less than" operator invocation.
// (Less than is used as a comparator for things like sorting or
// inserting into the right sorted spot in a map.)
class Tracer {
 public:
  // Constructors.
  Tracer();
  ~Tracer();
  Tracer(const Tracer &rhs);

  // Assignment operator.
  Tracer &operator=(const Tracer &rhs);

  // Less-than comparison operator.
  bool operator<(const Tracer &rhs) const;

  // << operator
  friend std::ostream &operator<<(std::ostream &out, const Tracer &rhs);

 private:
  // Return "(id_,value_)" as a string
  std::string PrintID(void) const;

  // This static (class member) tracks the next id_ to hand out.
  static unsigned int nextid_;
  unsigned int id_;
  unsigned int value_;
};

#endif  // _TRACER_H_
