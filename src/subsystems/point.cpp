#include "subsystems/point.hpp"

#include <cmath>

Point::Point(double x, double y, double rotation)
    : x(x), y(y), rotation(rotation){};


float Point::get_linear_dist(Point other) {
  return std::hypot(this->x - other.x, this->y - other.y);
}

float Point::get_rot_dist(Point other) {
  return std::atan2(other.y - this->y, other.x - this->x);
}
