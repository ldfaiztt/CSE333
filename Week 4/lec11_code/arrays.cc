#include <iostream>
#include "Point.h"

using namespace std;

int main(int argc, char **argv) {
  int stack_int;      // stack-allocated int.
  int *heap_int = new int;  // heap-allocated, uninitialized int

  int stack_arr[10];  // stack-allocated array of 10 uninitialized ints
  int *heap_arr = new int[10];  // heap-alloc'ed array of 10 uninital. ints

  // initialize array elements to zeros.
  int *heap_init_arr = new int[10]();  // heap-alloc array of 10 ints

  // error, can only initialize arrays using default constructor.
  int *heap_init_error = new int[10](12);

  Point stack_point(1,2);  // stack-allocated Point object.
  Point *heap_point = new Point(1,2);  // heap allocated Point object.

  // would be OK if we had a default constructor for Points, but
  // since we don't, the compiler complains.
  Point *error_point_arr = new Point[10]();  // heap-alloc, initialized.

  // error, can only initialize arrays using default constructor.
  Point *error2_point_arr = new Point[10](1,2);

  delete heap_int;         // correct
  delete heap_point;       // correct
  delete heap_arr;         // incorrect!  should be delete[] heap_arr.
  delete[] heap_init_arr;  // correct

  return 0;
}
