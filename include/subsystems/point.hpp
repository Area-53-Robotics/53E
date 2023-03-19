#pragma once

class Point {
 public:
  Point();
  Point(double x, double y, double rotation);
  ~Point();

  double get_linear_error(Point target);
  double get_rot_error(Point target);

  double x;
  double y;
  double rotation;

 private:
};
