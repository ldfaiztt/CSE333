#include <iostream>
#include <memory>

using std::shared_ptr;
using std::weak_ptr;

int main(int argc, char **argv) {
  weak_ptr<int> w;

  {
    shared_ptr<int> x;
    {
      shared_ptr<int> y(new int(10));
      w = y;
      x = w.lock();
      std::cout << *x << std::endl;
    }
    std::cout << *x << std::endl;
  }
  shared_ptr<int> a = w.lock();
  std::cout << a << std::endl;
  return 0;
}
