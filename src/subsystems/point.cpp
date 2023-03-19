#include "subsystems/point.hpp"

Point::Point() : x(0.0), y(0.0), rotation(0.0) {}

Point::Point(double x, double y, double rotation)
    : x(x), y(y), rotation(rotation){};

Point::~Point(){};
