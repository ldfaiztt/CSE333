/*
 * Copyright 2013 John Zahorjan
 *
 *  This file is part of the UW CSE 333 course exercises (333exer).
 *
 *  333exer is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  333exer is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with 333exer.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>       // for printf
#include <stdlib.h>      // for EXIT_SUCCESS
#include <inttypes.h>    // for uint8_t, PRIx8, etc.

// Print byteLen in decimal and byteLen bytes in hex starting at pData
void DumpHex(void *pData, int byteLen) {
  uint8_t* ptr = (unsigned char*)pData;

  printf("The %d bytes starting at 0x%"PRIxPTR " are: ",
              byteLen, (uintptr_t)pData);
  for (int i = 0; i < byteLen; i++) {
    printf("%s%02" PRIx8, (i > 0 ? " " : ""), ptr[i]);
  }
  printf("\n");
}

int main(int argc, char **argv) {
  char     charVal = '0';
  int32_t  intVal = 1;
  float    floatVal = 1.0;
  double   doubleVal  = 1.0;
  typedef struct {
    char    charVal;
    int32_t intVal;
    float   floatVal;
    double  doubleVal;
  } Ex2Struct;
  Ex2Struct structVal = { '0', 1, 1.0, 1.0 };

  DumpHex(&charVal, sizeof(char));
  DumpHex(&intVal, sizeof(int32_t));
  DumpHex(&floatVal, sizeof(float));
  DumpHex(&doubleVal, sizeof(double));
  DumpHex(&structVal, sizeof(structVal));

  return EXIT_SUCCESS;
}
