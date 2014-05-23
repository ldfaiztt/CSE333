#include <iostream>
#include <cstdlib>

using namespace std;

int main(int argc, char **argv) {
  string hello("Hello");
  hello = hello + " there";
  cout << hello << endl;
  return EXIT_SUCCESS;
}
