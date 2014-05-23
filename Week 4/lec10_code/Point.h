#ifndef _POINT_H_
#define _POINT_H_

class Point {
 public:
  Point(const int x, const int y);  // constructor
  int get_x() const { return x_; }  // inline member function
  int get_y() const { return y_; }  // inline member function
  double Distance(const Point &p) const;  // member function
  void SetLocation(const int x, const int y);  // member function

 private:
  int x_;  // data member
  int y_;  // data member
};  // class Point

#endif  // _POINT_H_

