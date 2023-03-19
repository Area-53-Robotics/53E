#include "subsystems/chassis/chassis.hpp"

#include "subsystems/chassis/odometry.hpp"

Chassis::Chassis(std::vector<int8_t> left_ports,
                 std::vector<int8_t> right_ports,
                 std::array<int, 2> left_encoder_ports,
                 std::array<int, 2> center_encoder_ports, int imu_port,
                 pros::motor_gearset_e gearset)
    : left_motors(left_ports),
      right_motors(right_ports),
      odometry(left_encoder_ports, center_encoder_ports, imu_port) {
  left_motors.set_gearing(gearset);
  right_motors.set_gearing(gearset);
}

Chassis::~Chassis() {
  // It's likely that this will never be called, since Chassis lives for the
  // whole program
  printf("Chassis task killed\n");
  if (chassis_task != nullptr) {
    chassis_task->remove();
  }
};

void Chassis::tank(int left, int right) {
  left_motors.move(left);
  right_motors.move(right);
}

void Chassis::chassis_task_function() {
  while (true) {
    pros::delay(20);
  }
}

void Chassis::init() {
  printf("Initializing chassis\n");
  // Start the chassis task
  odometry.init();
  chassis_task = new pros::Task([this] { this->chassis_task_function(); });
}
