#pragma once

class Point {
 public:
  Point();
  Point(double x, double y, double rotation);
  ~Point();

  float get_linear_dist(Point other);
  float get_rot_dist(Point other);

  double x;
  double y;
  double rotation;

 private:
};
