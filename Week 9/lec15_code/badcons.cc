// Base has no default constructor
class Base {
 public:
  Base(int x) : y(x) { }
  int y;
};

// Compiler error when you try to instantiate a D1, as D1’s
// synthesized default constructor needs to invoke Base's default
// constructor.
class D1 : public Base {
 public:
  int z;
};

// Works.
class D2 : public Base {
 public:
  D2(int z) : Base(z+1) {
   this->z = z;
  }
  int z;
};

int main(int argc, char **argv) {
  Base b(1);  // OK
  D2 d2(1);   // OK
  D1 d1;      // compiler error here.
  return 0;
}
