#pragma once
#include "api.h"
#include "subsystems/chassis/odometry.hpp"
class Chassis {
 public:
  Chassis(std::vector<int8_t> left_ports, std::vector<int8_t> right_ports,
          std::array<int, 2> left_encoder_ports,
          std::array<int, 2> center_encoder_ports, int imu_port,
          pros::motor_gearset_e gearset = pros::E_MOTOR_GEAR_BLUE);
  ~Chassis();

  void init();

  void move_motors();

  void tank(int left, int right);

 private:
  pros::Motor_Group left_motors;
  pros::Motor_Group right_motors;

  void chassis_task_function();

  pros::Task* chassis_task;

  Odometry odometry;
};
