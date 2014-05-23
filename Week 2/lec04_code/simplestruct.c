struct Point {
  float x, y;
};

int main(int argc, char **argv) {
  struct Point p1 = {0.0, 0.0};  // p1 is stack allocated
  struct Point *p1_ptr = &p1;

  p1.x = 1.0;
  p1_ptr->y = 2.0;
  return 0;
}
