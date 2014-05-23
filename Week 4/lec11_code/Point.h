#ifndef _POINT_H_
#define _POINT_H_

class Point {
 public:
  Point(const int x, const int y);  // constructor

  int get_x() const { return x_; }  // inline member function
  int get_y() const { return y_; }  // inline member function

  void CopyFrom(const Point &copy_from_me);    // update self
  double Distance(const Point &p) const;
  void SetLocation(const int x, const int y);

 private:
  int x_;  // data member
  int y_;  // data member

  // disable copy constructor and assignment operator
  Point(const Point &copyme);
  Point &operator=(const Point &rhs);
};  // class Point

#endif  // _POINT_H_
