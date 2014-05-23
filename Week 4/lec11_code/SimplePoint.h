#ifndef _SIMPLEPOINT_H_
#define _SIMPLEPOINT_H_

class SimplePoint {
 public:

  // Note that no constructors are declared/defined, so C++
  // synthesizes a default constructor for us, as well as
  // a copy constructor.  The default constructor initializes
  // all member variables to 0 (i.e., x_, y_).  The copy
  // constructor does a shallow copy of all member variables.

  int get_x() const { return x_; }  // inline member function
  int get_y() const { return y_; }  // inline member function

  double Distance(const SimplePoint &p) const;
  void SetLocation(const int x, const int y);

  // Note that the "=" (assignment) operator is not overloaded,
  // C++ synthesizes a default operator implementation for us
  // that does a shallow copy of all member variables (x_ and y_).

 private:
  int x_;  // data member
  int y_;  // data member
};  // class Point

#endif  // _SIMPLEPOINT_H_
