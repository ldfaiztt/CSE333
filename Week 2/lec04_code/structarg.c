#include <stdio.h>

// Point is a (struct point_st)
// PointPtr is a (struct point_st *)
typedef struct point_st {
  int x, y;
} Point, *PointPtr;

void DoubleXBroken(Point p) {
  p.x *= 2;
}

void DoubleXWorks(PointPtr p) {
  p->x *= 2;
}

int main(int argc, char *argv) {
  Point a = {1,1};

  DoubleXBroken(a);
  printf("(%d,%d)\n", a.x, a.y);

  DoubleXWorks(&a);
  printf("(%d,%d)\n", a.x, a.y);

  return 0;
}
