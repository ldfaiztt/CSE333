#include <stdio.h>
#include <stdlib.h>

// a complex number is a + bi
typedef struct complex_st {
  double real;  // real component
  double imag;  // imaginary component
} Complex, *ComplexPtr;

Complex AddComplex(Complex x, Complex y) {
  Complex retval;

  retval.real = x.real + y.real;
  retval.imag = x.imag + y.imag;
  return retval;
}

Complex MultiplyComplex(Complex x, Complex y) {
  Complex retval;

  retval.real = (x.real * y.real) - (x.imag * y.imag);
  retval.imag = (x.imag * y.real) - (x.real * y.imag);
  return retval;
}

ComplexPtr AllocComplex(double real, double imag) {
  Complex *retval = (Complex *) malloc(sizeof(Complex));
  if (retval != NULL) {
    retval->real = real;
    retval->imag = imag;
  }
  return retval;
}

int main(int argc, char **argv) {
  Complex a = {1, 2};
  Complex b = {3, 4};
  Complex c, *d;

  c = AddComplex(a, b);
  c = MultiplyComplex(a, c);
  d = AllocComplex(c.real, c.imag);
  if (d != NULL) {
    printf("%lf + %lfi\n", d->real, d->imag);
  }
  free(d);
  return 0;
}
