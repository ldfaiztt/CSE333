#include <iostream>
#include <string>

template <class T, int N>
void printmultiple(const T &value1) {
  for (int i = 0; i < N; ++i)
    std::cout << value1 << std::endl;
}

int main(int argc, char **argv) {
  std::string h("hello");
  printmultiple<std::string,3>(h);
  printmultiple<const char *,4>("hi");
  printmultiple<int,5>(10);
  return 0;
}
