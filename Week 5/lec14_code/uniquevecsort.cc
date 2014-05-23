#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <vector>

using std::unique_ptr;
using std::vector;

bool sortfunction(const unique_ptr<int>& x,
		  const unique_ptr<int>& y) {
  return *x < *y;
}

void printfunction(unique_ptr<int> &x) {
  std::cout << *x << std::endl;
}

int main(int argc, char **argv) {
  vector<unique_ptr<int> > vec;

  vec.push_back(unique_ptr<int>(new int(9)));
  vec.push_back(unique_ptr<int>(new int(5)));
  vec.push_back(unique_ptr<int>(new int(7)));

  // buggy: sorts based on the values of the ptrs
  std::sort(vec.begin(), vec.end());
  std::cout << "Sorted:" << std::endl;
  std::for_each(vec.begin(), vec.end(), &printfunction);

  // better: sorts based on the pointed-to values
  std::sort(vec.begin(), vec.end(), &sortfunction);
  std::cout << "Sorted:" << std::endl;
  std::for_each(vec.begin(), vec.end(), &printfunction);

  return EXIT_SUCCESS;
}
