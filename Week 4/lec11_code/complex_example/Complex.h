#ifndef _COMPLEX_H_
#define _COMPLEX_H_

#include <iostream>

namespace complex {

class Complex {
  // Style tip: always put your public members before private members.
 public:
  Complex(const double real, const double imag);  // Constructor.
  Complex(const Complex& copyme);     // Copy constructor.
  ~Complex();  // Destructor.

  // Accessors / mutators, defined inline.
  double real() const { return real_; }
  double imag() const { return imag_; }
  void set_real(const double real) { real_ = real; }
  void set_imag(const double imag) { imag_ = imag; }

  // Override the "+", "-", "=", "+=", and "-=" operators.
  Complex operator+(const Complex &a) const;
  Complex operator-(const Complex &a) const;
  Complex &operator=(const Complex &a);
  Complex &operator+=(const Complex &a);
  Complex &operator-=(const Complex &a);

  // Override "<<" for ostream, ">>" for istream.  Note that
  // these are global functions, not member functions.
  friend std::ostream &operator<<(std::ostream &out, const Complex &a);
  friend std::istream &operator>>(std::istream &in, Complex &a);

 private:
  double real_, imag_;  // Member variables.
};  // class Complex

}  // namespace complex

#endif  // _COMPLEX_H_
