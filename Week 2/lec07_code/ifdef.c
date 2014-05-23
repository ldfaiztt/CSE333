/* CSE 333 Lecture 7 demo: ifdef.c */
/* Perkins */

/* Demonstrate conditional compilation, in this case for debugging. */

/* If TRACE is defined at compile time these macros will expand     */
/* to print statements, otherwise they will expand to "nothing"     */
/* and effectively not appear in the program.  TRACE can be defined */
/* either with #define or with -DTRACE on the gcc compile command.  */

/* #ifdef and related macros are widely used in C code particularly */
/* to adapt code to different platforms.  But they make code hard   */
/* to understand if not used carefully and are best avoided unless  */
/* there is good reason to use them and they are used carefully.    */

#include <stdio.h>
#include <stddef.h>

// #define TRACE   

#ifdef TRACE
#define ENTER(f) printf("Entering %s\n", f);
#define EXIT(f)  printf("Exiting  %s\n", f);
#else
#define ENTER(f)
#define EXIT(f)
#endif

// print n
void pr(int n) {
  ENTER("pr");
  printf("n = %d\n", n);
  EXIT("pr");
}

int main() {
  pr(17);
  pr(42);
  return 0;
}

