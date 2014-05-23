/*
 * Copyright 2013 Chun-Wei Chen
 * 1267040
 * mijc0517@cs
 * 07/17/13
 */

#include "./IntPair.h"

IntPair::IntPair(int x, int y) {
  x_ = x;
  y_ = y;
}

void IntPair::Get(int *x, int *y) {
  *x = x_;
  *y = y_;
}

void IntPair::Set(int x, int y) {
  x_ = x;
  y_ = y;
}
