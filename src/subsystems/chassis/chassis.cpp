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
      linear_pid_controller(linear_pid_options),
      rotational_pid_controller(rotational_pid_options),
      odometry(left_encoder_ports, center_encoder_ports, imu_port) {
  left_motors.set_gearing(gearset);
  right_motors.set_gearing(gearset);
  left_motors.set_brake_modes(pros::E_MOTOR_BRAKE_BRAKE);
  right_motors.set_brake_modes(pros::E_MOTOR_BRAKE_BRAKE);
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

Point Chassis::get_position() { return odometry.get_position(); }

void Chassis::turn_to_point(float x, float y, int max_speed) {
  printf("turning to point\n");
  Point target_point(x, y, 0);
  Pid pid(rotational_pid_controller);
  pid.max_time = 3000;
  while (!pid.settled()) {
    float error_theta = odometry.get_rot_error(target_point);
    float power = pid.update(error_theta, 0, true);

    // left_motors.move(-power);
    // right_motors.move(power);
    pros::delay(10);
  }
  printf("exited turn pid\n");
  left_motors.brake();
  right_motors.brake();
}

void Chassis::move_to_point(float x, float y, float theta, int max_speed) {
  Point target(x, y, theta);
  float prev_linear_power = 0;
  float prev_rotational_power = 0;
  bool close = false;
  // float lead = 0.5;  // TODO: make this a config option
  Pid linear_pid(linear_pid_controller);
  Pid rotational_pid(rotational_pid_controller);
  while (!linear_pid.settled()) {
    /*
    carrot_point = Point(
        (target_point.x - distance * sin(target_point.rotation) * lead),
        (target_point.y - distance * cos(target_point.rotation) * lead),
        0.0);
        */

    Point current_position = odometry.get_position();
    // update error
    float linear_error = odometry.get_linear_error(target);
    float rotational_error = odometry.get_rot_error(target);

    /*
    double linear_error = odometry.get_linear_error(target_point);
    double rotational_error = odometry.get_rot_error(target_point) * 180 /
                              M_PI;  // The pid loop is tuned for degrees
                                      */

    double linear_power = linear_pid.update(linear_error, 0);
    double rotational_power = rotational_pid.update(rotational_error, 0);

    if (current_position.get_linear_dist(Point(x, y, 0)) < 2) {
      close = true;
      max_speed = (std::fabs(prev_linear_power) < 30)
                      ? 30
                      : std::fabs(prev_linear_power);
    }

    linear_power = limit(linear_power, -max_speed, max_speed);
    if (close) rotational_power = 0;

    prev_linear_power = linear_power;
    prev_rotational_power = rotational_power;

    float left_power = linear_power - rotational_power;
    float right_power =
        linear_power +
        rotational_power;  // ratio the speeds to respect the max speed
    float ratio =
        std::max(std::fabs(left_power), std::fabs(right_power)) / max_speed;
    if (ratio > 1) {
      left_power /= ratio;
      right_power /= ratio;
    }

    left_motors.move(left_power);
    right_motors.move(right_power);
    pros::delay(20);
  }
  printf("move exited\n");
  left_motors.brake();
  right_motors.brake();
}

void Chassis::tank(int left, int right) {
  left_motors.move(left);
  right_motors.move(right);
}

void Chassis::chassis_task_function() {}
