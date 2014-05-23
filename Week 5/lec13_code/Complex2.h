#ifndef _COMPLEX_H_
#define _COMPLEX_H_

#include <iostream>

namespace complex {

class Complex {
 public:
  // Should operator+ return a reference or not?
  // (Answer: ?)
  Complex &operator+(const Complex &a) const {
    Complex tmp(0,0);
    tmp.real_ = this->real_ + a.real_;
    tmp.set_imag(this->imag_ + a.imag());
    return tmp;
  }

 private:
  double real_, imag_;
};  // class Complex

}  // namespace complex

#endif  // _COMPLEX_H_
