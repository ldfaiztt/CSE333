#include <cstdlib>
#include <iostream>
#include <memory>
#include <map>

using std::unique_ptr;
using std::map;

struct MapComp {
  bool operator()(const unique_ptr<int> &lhs,
                  const unique_ptr<int> &rhs) const {
    return *lhs < *rhs;
  }
};

int main(int argc, char **argv) {
  // Create the map
  map<unique_ptr<int>,int,MapComp> a_map;

  // Create the three unique_ptrs that will be keys
  unique_ptr<int> a(new int(5));
  unique_ptr<int> b(new int(9));
  unique_ptr<int> c(new int(7));

  // Transfer ownership of the unique_ptrs into the
  // map using std::move; after this, a, b, and c
  // will contain NULL.
  a_map[std::move(a)] = 25;
  a_map[std::move(b)] = 81;
  a_map[std::move(c)] = 49;

  // Iterate through the map, printing out the values.
  map<unique_ptr<int>,int>::iterator it;
  for (it = a_map.begin(); it != a_map.end(); it++) {
    std::cout << "key: " << *(it->first);
    std::cout << " value: " << it->second;
    std::cout << std::endl;
  }

  return EXIT_SUCCESS;
}
