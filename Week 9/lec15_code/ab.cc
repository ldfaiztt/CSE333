/* CSE 333 lecture 15. ab.cc: essence of static vs dynamic dispatch.  HP 5/13 */

// What is the output from this program?

#include <iostream>
using namespace std;

class A {
public:
          void m1() { cout << "a1" << endl; }
  virtual void m2() { cout << "a2" << endl; }
};

class B : public A {
  void m1() { cout << "b1" << endl; }
  void m2() { cout << "b2" << endl; }
};

int main() {
  A* x = new B();
  x->m1();
  x->m2();

  return 0;
}
