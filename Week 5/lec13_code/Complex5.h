#ifndef _COMPLEX_H_
#define _COMPLEX_H_

#include <iostream>

namespace complex {

class Complex {
 public:
  double real() const { return real_; };
  double imag() const { return imag_; };

 private:
  double real_, imag_;  // Member variables.
};  // class Complex

}  // namespace complex

// Should operator<< return a reference?
// (Answer: ?)
std::ostream &operator<<(std::ostream &out, const complex::Complex &a) {
  out << "(" << a.real() << " + " << a.imag() << "i)";
  return out;
}

#endif  // _COMPLEX_H_
