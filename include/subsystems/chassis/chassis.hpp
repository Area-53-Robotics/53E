#pragma once
#include "api.h"
#include "subsystems/chassis/odometry.hpp"
#include "subsystems/pid.hpp"
class Chassis {
 public:
  Chassis(std::vector<int8_t> left_ports, std::vector<int8_t> right_ports,
          pros::motor_gearset_e gearset, std::array<int, 2> left_encoder_ports,
          std::array<int, 2> center_encoder_ports, int imu_port,
          Pid::PidController linear_pid_options,
          Pid::PidController rotation_pid_options);
  ~Chassis();

  void init();

  bool settled();

  Point get_position();

  void move_to_point(float x, float y, float theta, int max_speed);

  void tank(int left, int right);

  enum class Mode {
    Moving,
    Idle,
  };

  Mode current_mode;

 private:
  pros::Motor_Group left_motors;
  pros::Motor_Group right_motors;

  void chassis_task_function();
  pros::Task* chassis_task;

  Point target_point;

  Pid linear_pid;
  Pid rotational_pid;
  Odometry odometry;
};
