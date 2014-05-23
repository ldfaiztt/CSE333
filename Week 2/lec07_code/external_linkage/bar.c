#include <stdio.h>

// The global variable "counter" is defined and initialized
// in the other source file (foo.c).  Here, we are declaring
// it, and forcing it to have external linkage (i.e., to
// tell the compiler that it is defined in some other file)
// by using the "extern" storage class specifier.
//
// By default, variables are assumed to have external linkage,
// i.e., extern is default and strictly speaking not needed.
// But, it is considered good practice to be explicit and
// include it, since it makes the code much more readable.
extern int counter;

void bar(void) {
  counter++;
  printf("(bar): incremented counter is %d\n", counter);
}
