#include <stdio.h>

int main(int argc, char **argv) {
  // a 2 row, 3 column array of doubles
  double grid[2][3];

  // a 3 row, 5 column array of ints
  int matrix[3][5] = {
    {0, 1, 2, 3, 4},
    {0, 2, 4, 6, 8},
    {1, 3, 5, 7, 9}
  };

  grid[0][2] = (double) matrix[2][4];  // which val?
  printf("%lf\n", grid[0][2]);
  return 0;
}
