// Base has a default constructor.
class Base {
 public:
  int y;
};

// Works.
class D1 : public Base {
 public:
  int z;
};

// Works.
class D2 : public Base {
 public:
  D2(int z) {
   this->z = z;
  }
  int z;
};

int main(int argc, char **argv) {
  Base b;    // OK
  D2 d2(1);  // OK
  D1 d1;     // compiler error here.
  return 0;
}
