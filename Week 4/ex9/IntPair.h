/*
 * Copyright 2013 Chun-Wei Chen
 * 1267040
 * mijc0517@cs
 * 07/17/13
 */

#ifndef _INTPAIR_H_
#define _INTPAIR_H_

class IntPair {
 public:
  // Constructs an IntPair with two int values x and y.
  IntPair(int x, int y);
  // Gets the values stored in this IntPair.
  void Get(int *x, int *y);
  // Sets the values stored in this IntPair.
  void Set(int x, int y);

 private:
  int x_;
  int y_;
};

#endif
