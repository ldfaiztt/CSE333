#include <iostream>
#include <cstdlib>

// C++'s iomanip.h header defines a bunch of useful stream manipulator
// functions.  These manipulators can be used to modify the formatting
// used when inputting or outputting data, similar to how printf's
// format string lets you specify different kinds of conversions.
#include <iomanip>

using namespace std;

int main(int argc, char **argv) {
  // setw(x) sets the field with to x for the next item
  // sent to the stream.
  cout << "Hi! " << setw(4) << 5 << " " << 5 << endl;

  // hex tells the stream to output integers in hexadecimal;
  // it remains active until you set it back to some other
  // base using dec or oct.
  cout << hex << 16 << " " << 13 << endl;
  cout << dec << 16 << " " << 13 << endl;
  return EXIT_SUCCESS;
}
