#include <stdio.h>
#include <limits.h>
#include <float.h>

int main(int argc, char **argv) {
  char c = 'x';
  short int si = -1;    // can also declare as "short si = -1;"
  unsigned short int usi = 1;
  int i = 1;
  unsigned int ui = 1;
  long int li;          // can also declare as "long li;"
  long long int lli;
  float f = 5.1;
  double d = 5.1;
  long double ld = 5.1;
  char *ptr = &c;

  printf("char: size=%zu, max=%c, min=%c\n",
         sizeof(c), CHAR_MAX, CHAR_MIN) ;

  printf("short: size=%zu, max=%hd, min=%hd\n",
         sizeof(si), SHRT_MAX, SHRT_MIN);

  printf("unsigned short: size=%zu, max=%hu, min=%hu\n",
         sizeof(usi), USHRT_MAX, 0);

  printf("int: size=%zu, max=%d, min=%d\n",
         sizeof(i), INT_MAX, INT_MIN);

  printf("unsigned int: size=%zu, max=%u, min=%u\n",
         sizeof(ui), UINT_MAX, 0);

  printf("long int: size=%zu, max=%ld, min=%ld\n",
         sizeof(li), LONG_MAX, LONG_MIN);

  printf("long long int: size=%zu, max=%lld, min=%lld\n",
         sizeof(lli), LLONG_MAX, LLONG_MIN);

  printf("float: size=%zu, max=%g, min=%g\n",
         sizeof(f), FLT_MAX, FLT_MIN);

  printf("double: size=%zu, max=%g, min=%g\n",
         sizeof(d), DBL_MAX, DBL_MIN);

  printf("long double: size=%zu, max=%Lg, min=%Lg\n",
         sizeof(ld), LDBL_MAX, LDBL_MIN);

  printf("ptr: size=%zu, value=%p\n", sizeof(ptr), ptr);

  return 0;
}
