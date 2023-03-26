#pragma once
class Point {
 public:
  Point(double x = 0.0, double y = 0.0, double rotation = 0.0);

  float get_linear_dist(Point other);
  float get_rot_dist(Point other);
  double x;
  double y;
  double rotation;
};
