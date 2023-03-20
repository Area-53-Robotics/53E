#include "subsystems/chassis/chassis.hpp"

#include <cmath>

#include "subsystems/chassis/odometry.hpp"
#include "subsystems/pid.hpp"
#include "utils.hpp"

Chassis::Chassis(std::vector<int8_t> left_ports,
                 std::vector<int8_t> right_ports, pros::motor_gearset_e gearset,
                 std::array<int, 2> left_encoder_ports,
                 std::array<int, 2> center_encoder_ports, int imu_port,
                 Pid::PidController linear_pid_options,
                 Pid::PidController rotational_pid_options)
    : left_motors(left_ports),
      right_motors(right_ports),
      current_mode(Mode::Idle),
      linear_pid(linear_pid_options),
      rotational_pid(rotational_pid_options),
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

void Chassis::init() {
  printf("Initializing chassis\n");
  // Start the chassis task
  odometry.init();
  chassis_task = new pros::Task([this] { this->chassis_task_function(); });
}

bool Chassis::settled() { return linear_pid.settled(); }

Point Chassis::get_position() { return odometry.get_position(); }

void Chassis::move_to_point(float x, float y, float theta, int max_speed) {
  Point current_position;
  int left_power;
  int right_power;
  bool close;
  float lead = 0.5;  // TODO: make this a config option
  while (!settled()) {
    current_position = odometry.get_position();
    /*
    carrot_point = Point(
        (target_point.x - distance * sin(target_point.rotation) * lead),
        (target_point.y - distance * cos(target_point.rotation) * lead),
        0.0);
        */

    double linear_error = odometry.get_linear_error(target_point);
    double rotational_error = odometry.get_rot_error(target_point) * 180 /
                              M_PI;  // The pid loop is tuned for degrees

    double linear_power = linear_pid.update(linear_error);
    double rotational_power = rotational_pid.update(rotational_error);

    if (linear_error < 7.5) {
      close = true;
    }

    left_power = limit(linear_power - rotational_power, -max_speed, max_speed);
    right_power = limit(linear_power + rotational_power, -max_speed, max_speed);
    // printf("%i, %i\n", left_power, right_power);

    //  Race conditions here I come
    left_motors.move(left_power);
    right_motors.move(right_power);
    pros::delay(20);
  }
  // Idk maybe this is a sign this should be it's own function
  printf("move exited\n");
}

void Chassis::tank(int left, int right) {
  left_motors.move(left);
  right_motors.move(right);
}

void Chassis::chassis_task_function() {}
