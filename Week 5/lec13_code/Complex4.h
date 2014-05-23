#ifndef _COMPLEX_H_
#define _COMPLEX_H_

#include <iostream>

namespace complex {

class Complex {
 public:
  // Should += return a reference?
  // (Answer: ?)
  Complex &operator+=(const Complex &a) {
    this->real_ += a.real_;
    this->imag_ += a.imag_;
    return *this;
  }

 private:
  double real_, imag_;
};  // class Complex

}  // namespace complex

#endif  // _COMPLEX_H_
