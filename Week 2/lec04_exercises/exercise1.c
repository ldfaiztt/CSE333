/*
 * Copyright 2011 Steven Gribble
 *
 *  This file is the solution to an exercise problem posed during
 *  one of the UW CSE 333 lectures (333exercises).
 *
 *  333exercises is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  333exercises is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with 333exercises.  If not, see <http://www.gnu.org/licenses/>.
 */

// Lecture 4 exercise 1

// Write and test a program that defines:
// - a new structured type Point
//   - represent it with floats for the x, y coordinate
// - a new structured type Rectangle
//   - assume its sides are parallel to the x-axis and y-axis
//   - represent it with the bottom-left and top-right Points
// - a function that computes/returns the area of a Rectangle
// - a function that tests whether a Point is in a Rectangle

#include <assert.h>  // needed for assert()

// let's use typedef to declare that "Point" is a new
// type, and that the meaning of a "Point" is the same
// as "struct Point_st { float x; float y; }"
typedef struct Point_st {
  float x;
  float y;
} Point;

// let's use typedef to declare that "Rectangle" is a new
// type, and that the meaning of a "Rectangle" is the same as
// "struct Rectangle_st { Point bottom_left; Point bottom_right; }"
typedef struct Rectangle_st {
  Point bottom_left;
  Point top_right;
} Rectangle;


// Declare a function prototype for RectangleArea.  We'll
// define the function somewhere below main().
//
// Arguments:   rect is the Rectangle whose area we'll compute.
// Returns:  the area of the rectangle, or -1.0 on error (i.e.,
//           the rectangle is ill-formed).
float RectangleArea(Rectangle rect);

// Declare a function prototype for PointInRect.  We'll
// define the function somwhere below main().
//
// Arguments: rect is a Rectangle, p is a Point.
// Returns: 1 if the point is in the Rectangle, 0 if
//          the point is not in the Rectangle, -1 if
//          the Rectangle is ill-formed.
int PointInRect(Rectangle rect, Point p);

// Here's a helper function that we use to make sure
// a rectangle is well-formed.
//
// Returns 1 if the rectangle is well-formed, 0 otherwise.
int IsRectSensible(Rectangle rect);

// Here's a helper function that tests for approximate
// equality of two floats.
#define EPSILON 0.00000001
int FloatEqualEpsilon(float x, float y);

// we'll write some test code in main.
int main(int argc, char **argv) {
  Rectangle bad_rect, line_rect, point_rect, good_rect;
  Point outside, border, inside;

  // make bad_rect's bottom_left be above and right of top_right
  bad_rect = (Rectangle) { {1, 1}, {0.1, 0.1} };

  // make line_rect be a line
  line_rect = (Rectangle) { {0.1, 0.1}, {0.1, 1} };

  // make zero_rect be a point
  point_rect = (Rectangle) { {0.1, 0.1}, {0.1, 0.1} };

  // make good_rect be nice
  good_rect = (Rectangle) { {0.1, 0.1}, {1, 1}};
  outside = (Point) {0, 0};
  border = (Point) {0.1, 0.5};
  inside = (Point) {0.5, 0.5};

  // our tests of the helper function
  assert(IsRectSensible(good_rect));
  assert(IsRectSensible(point_rect));
  assert(IsRectSensible(line_rect));
  assert(!IsRectSensible(bad_rect));

  // Our tests of RectangleArea.  Nasty issue: never
  // test a float for precise equality, since floats
  // are approximate representations.  Need to write our
  // own comparator that tests for a difference < epsilon.
  assert(FloatEqualEpsilon(RectangleArea(good_rect), 0.81));
  assert(FloatEqualEpsilon(RectangleArea(line_rect), 0.0));
  assert(FloatEqualEpsilon(RectangleArea(point_rect), 0.0));
  assert(FloatEqualEpsilon(RectangleArea(bad_rect), -1));

  // our tests of PointInRect
  assert(PointInRect(good_rect, inside));
  assert(PointInRect(good_rect, border));
  assert(PointInRect(line_rect, border));
  assert(!PointInRect(good_rect, outside));

  return 0;
}

float RectangleArea(Rectangle rect) {
  float area;

  // let's make sure that rect (which is passed-by-value,
  // i.e., is a copy) is sensible.
  if (!IsRectSensible(rect))
    return -1;

  // area is length * width
  area = (rect.top_right.x - rect.bottom_left.x) *
    (rect.top_right.y - rect.bottom_left.y);
  assert(area >= 0.0);
  return area;
}

int PointInRect(Rectangle rect, Point p) {
  // let's make sure that rect is sensible.
  if (!IsRectSensible(rect))
    return -1;

  // check the x-axis
  if (p.x < rect.bottom_left.x)
    return 0;
  if (p.x > rect.top_right.x)
    return 0;

  // check the y-axis
  if (p.y < rect.bottom_left.y)
    return 0;
  if (p.y > rect.top_right.y)
    return 0;

  // it's in!
  return 1;
}

int IsRectSensible(Rectangle rect) {
  // make sure the bottom_left field is actually
  // below and to the left of the top_right field.
  // (it's also OK if they are precisely the same
  // point -- that's a zero-area rectangle.)
  if (rect.bottom_left.x > rect.top_right.x)
    return 0;

  if (rect.bottom_left.y > rect.top_right.y)
    return 0;

  return 1;
}

int FloatEqualEpsilon(float x, float y) {
  if (x > y) {
    if (x - y < EPSILON)
      return 1;
    return 0;
  }

  if (y - x < EPSILON)
    return 1;
  return 0;
}
