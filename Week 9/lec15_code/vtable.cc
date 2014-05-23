class Base {
 public:
  virtual void fn1() {};
  virtual void fn2() {};
};

class Dr1: public Base {
 public:
  virtual void fn1() {};
};

main() {
 Dr1   d1;
 d1.fn1();
 Base *ptr = &d1;
 ptr->fn1();
}
