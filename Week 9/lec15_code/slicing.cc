class Base {
 public:
  Base(int x) : x_(x) { }
  int x_;
};

class Dr : public Base {
 public:
  Dr(int y) : Base(16), y_(y) { }
  int y_;
};

main() {
  Base b(1);
  Dr d(2);
  b = d;  // what happens to y_?
  // d = b;  // would be a compiler error
}
