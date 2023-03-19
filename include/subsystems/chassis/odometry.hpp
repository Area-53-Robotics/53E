#pragma once
#include "api.h"
#include "pros/adi.hpp"
#include "subsystems/point.hpp"

class Odometry {
 public:
  Odometry(std::array<int, 2> left_encoder_ports,
           std::array<int, 2> center_encoder_ports, int imu_port);
  ~Odometry();

  void init();

  Point get_position();
  double get_x();
  double get_y();
  double get_rot();

 private:
  pros::ADIEncoder left_encoder;
  pros::ADIEncoder center_encoder;
  pros::Imu imu;

  Point current_position;

  pros::Task* odom_task;
  void odom_task_function();
};
