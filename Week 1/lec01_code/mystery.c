#include <stdio.h>
#include <stdlib.h>

int verify_something(void) {
  return 0;
}

unsigned char *mystery_function(unsigned short bufsize) {
  unsigned char *tmp_buf;

  if (bufsize == 0)
    return NULL;

  tmp_buf = malloc(bufsize);
  if (tmp_buf == NULL)
    return NULL;

  if (verify_something() == 0) // something bad happened
    return NULL;

  return tmp_buf;
}

int main(int argc, char **argv) {
  unsigned char *buf;

  buf = mystery_function(50);
  if (buf != NULL)
    free(buf);
  return 0;
}
