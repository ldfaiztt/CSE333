#include <iostream>
#include <sstream>
#include <string>

#include "Complex.h"

namespace complex {

Complex::Complex(const double real, const double imag) {
  std::cout << "constructor(" << real << "," << imag << ")";
  std::cout << ", the constructed object is at " << this << std::endl;
  this->real_ = real;
  this->imag_ = imag;
}

Complex::Complex(const Complex &copyme) {
  std::cout << "copy constructor(copy " << &copyme << ")";
  std::cout << ", the constructed object is at " << this << std::endl;
  this->real_ = copyme.real_;
  this->imag_ = copyme.imag_;
}

Complex::~Complex() {
  std::cout << "destructor of object at " << this << std::endl;
}

Complex Complex::operator+(const Complex &a) const {
  Complex tmp(0,0);
  std::cout << "+: adding " << this << " to " << &a;
  std::cout << ", tmp is at " << &tmp << std::endl;
  tmp.real_ = this->real_ + a.real_;
  tmp.set_imag(this->imag_ + a.imag());
  return tmp;
}

Complex Complex::operator-(const Complex &a) const {
  Complex tmp(0,0);
  std::cout << "-: subtracting " << this << " from " << &a;
  std::cout << ", tmp is at " << &tmp << std::endl;
  tmp.real_ = this->real_ - a.real_;
  tmp.imag_ = this->imag_ - a.imag_;
  return tmp;
}

Complex &Complex::operator=(const Complex &a) {
  std::cout << "=operator: " << this << " = " << &a << std::endl;
  if (this != &a) {
    this->real_ = a.real_;
    this->imag_ = a.imag_;
  }
  return *this;
}

Complex &Complex::operator+=(const Complex &a) {
  std::cout << "+=operator: " << this << " += " << &a << std::endl;
  this->real_ += a.real_;
  this->imag_ += a.imag_;
  return *this;
}

Complex &Complex::operator-=(const Complex &a) {
  std::cout << "-=operator: " << this << " -= " << &a << std::endl;
  this->real_ -= a.real_;
  this->imag_ -= a.imag_;
  return *this;
}

std::ostream &operator<<(std::ostream &out, const Complex &a) {
  std::cout << "<<operator: from " << &a << std::endl;
  out << "(" << a.real_ << " + " << a.imag_ << "i)";
  return out;
}

std::istream &operator>>(std::istream &in, Complex &a) {
  std::cout << ">>operator: to " << &a << std::endl;

  double realtmp, imagtmp;
  // Make sure the next character is '('.
  if (in.peek() != '(') {
    in.setstate(std::ios_base::failbit);
    return in;
  }
  in.get();

  // Try to read the next thing as a double.
  if (!(in >> realtmp)) {
    return in;
  }

  // Read the next three chars (' + ').
  if (in.get() != ' ')
    return in;
  if (in.get() != '+')
    return in;
  if (in.get() != ' ')
    return in;

  // Try to read the next token as a double ending in 'i'.
  std::string x;
  if (!getline(in, x, 'i')) {
    return in;
  }

  std::stringstream ss(x);
  if (!(ss >> imagtmp)) {
    return in;
  }

  // Verify the next char is ')'.
  if (in.peek() != ')') {
    in.setstate(std::ios_base::failbit);
    return in;
  }
  in.get();

  a.real_ = realtmp;
  a.imag_ = imagtmp;
  return in;
}


}  // namespace complex
