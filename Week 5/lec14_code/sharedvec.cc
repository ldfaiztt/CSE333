#include <cstdlib>
#include <iostream>
#include <memory>
#include <vector>

using std::shared_ptr;
using std::vector;

int main(int argc, char **argv) {
  vector<shared_ptr<int> > vec;

  vec.push_back(shared_ptr<int>(new int(9)));
  vec.push_back(shared_ptr<int>(new int(5)));
  vec.push_back(shared_ptr<int>(new int(7)));

  // z is (a reference to) the (int pointed to by the shared_ptr
  // in vec[1])
  int &z = *vec[1];
  std::cout << "z is: " << z << std::endl;

  // works, since shared_ptrs can be copied
  shared_ptr<int> copied = vec[1];
  std::cout << "*copied: " << *copied << std::endl;

  // works, but now vec[1] has a null pointer.
  shared_ptr<int> moved = std::move(vec[1]);
  std::cout << "*moved: " << *moved << std::endl;
  std::cout << "vec[1].get(): " << vec[1].get() << std::endl;

  return EXIT_SUCCESS;
}
