#ifndef _COMPLEX_H_
#define _COMPLEX_H_

#include <iostream>

namespace complex {

class Complex {
 public:
  // Copy constructor -- should we pass a reference or not?
  // (Answer: ?)
  Complex(const Complex& copyme) {
    real_ = copyme.real_;
    imag_ = copyme.image_;
  }

 private:
  double real_, imag_;
};  // class Complex

}  // namespace complex

#endif  // _COMPLEX_H_
