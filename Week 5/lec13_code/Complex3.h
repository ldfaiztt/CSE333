#ifndef _COMPLEX_H_
#define _COMPLEX_H_

#include <iostream>

namespace complex {

class Complex {
 public:
  // Should the assignment operator return a reference?
  // (Answer: ?)
  Complex &operator=(const Complex &a) {
    if (this != &a) {
      this->real_ = a.real_;
      this->imag_ = a.imag_;
    }
    return *this;
  }

 private:
  double real_, imag_;
};  // class Complex

}  // namespace complex

#endif  // _COMPLEX_H_
