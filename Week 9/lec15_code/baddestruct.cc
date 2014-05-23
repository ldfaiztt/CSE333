#include <iostream>

class Base {
 public:
  Base() { std::cout << "Base()" << std::endl; x = new int; }
  ~Base() { std::cout << "~Base()" << std::endl; delete x; }
  int *x;
};

class D1 : public Base {
 public:
  D1() { std::cout << "D1()" << std::endl; y = new int; }
  ~D1() { std::cout << "~D1()" << std::endl; delete y; }
  int *y;
};

int main(int argc, char **argv) {
  Base *b = new Base;
  Base *dptr = (Base *) new D1;

  delete b;    // ok
  delete dptr; // leaks Base::x

  return 0;
}
