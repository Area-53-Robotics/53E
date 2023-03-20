#include "subsystems/chassis/odometry.hpp"

#include "pros/imu.hpp"

Odometry::Odometry(std::array<int, 2> left_encoder_ports,
                   std::array<int, 2> center_encoder_ports, int imu_port)
    : left_encoder(left_encoder_ports[0], left_encoder_ports[1]),
      center_encoder(center_encoder_ports[0], center_encoder_ports[1]),
      imu(imu_port){

      };

Odometry::~Odometry() {
  printf("odom task killed\n");
  if (odom_task != nullptr) {
    odom_task->remove();
  }
};

void Odometry::init() {
  printf("Initializing Odom\n");
  printf("Calibrating Imu\n");
  imu.reset(true);
  printf("Imu Calibrated\n");
  odom_task = new pros::Task([this] { this->odom_task_function(); });
};

Point Odometry::get_position() { return current_position; }

double Odometry::get_linear_error(Point target) {
  return current_position.get_linear_dist(target);
}

double Odometry::get_rot_error(Point target) {
  double x = target.x;
  double y = target.y;

  x -= current_position.x;
  y -= current_position.y;

  double delta_theta = atan2(y, x) - current_position.rotation;

  while (fabs(delta_theta) > M_PI) {
    delta_theta -= 2 * M_PI * delta_theta / fabs(delta_theta);
  }

  return delta_theta;
}

void Odometry::odom_task_function() {
  // Pilons the goat
  //  http://thepilons.ca/wp-content/uploads/2018/10/Tracking.pdf
  printf("Starting odom task\n");
  int time_elapsed = 0;
  // Constants
  const double WHEEL_RADIUS = 2.75 / 2;

  // starting angle
  const double THETA_START = M_PI;

  const double LEFT_TRACKING_RADIUS =
      3.25;  // TODO: move these values to some kind of config option
  const double S_TRACKING_RADIUS = 2.0;

  double left_position;
  double s_position;

  double left_prev_position;
  double s_prev_position;

  double delta_l;
  double delta_s;

  double total_delta_l;
  double total_delta_s;

  double current_absolute_orientation;

  double delta_theta;
  double previous_theta;

  double delta_x_local;
  double delta_y_local;

  double avg_theta_for_arc;

  double delta_x_global;
  double delta_y_global;

  while (true) {
    // Encoders output in degrees
    left_position = left_encoder.get_value();
    s_position = center_encoder.get_value();

    // Distance moved in inches
    delta_l =
        ((left_position - left_prev_position) * (M_PI / 180) * WHEEL_RADIUS);
    delta_s = (s_position - s_prev_position) * (M_PI / 180 * WHEEL_RADIUS);

    // Log previous values in degrees
    left_prev_position = left_position;
    s_prev_position = s_position;

    // Total movement on both encoders in inches
    total_delta_l += delta_l;
    total_delta_s += delta_s;

    // Radians
    current_absolute_orientation = (360 - imu.get_heading() * M_PI / 180);

    delta_theta = current_absolute_orientation - previous_theta;

    previous_theta = current_absolute_orientation;

    // If we didn't rotate, we moved in a straight line
    // This check is needed so we don't divide by zero
    if (delta_theta == 0) {
      delta_x_local = delta_l;
      delta_y_local = delta_l;
    } else {
      delta_x_local =
          2 * sin(delta_theta) * ((delta_s / delta_theta) + S_TRACKING_RADIUS);
      delta_y_local = 2 * sin(delta_theta) *
                      ((delta_l / delta_theta) + LEFT_TRACKING_RADIUS);
    }

    // calculate average angle of the robot during it's arc in radians
    avg_theta_for_arc = current_absolute_orientation - (delta_theta / 2);

    delta_x_global = (delta_y_local * cos(avg_theta_for_arc)) -
                     (delta_x_local * sin(avg_theta_for_arc));

    delta_y_global = (delta_y_local * sin(avg_theta_for_arc)) -
                     (delta_x_local * cos(avg_theta_for_arc));

    // wraps angles back around if they ever go under 0 or over 2 pi
    while (current_absolute_orientation >= 0) {
      current_absolute_orientation -= 2 * M_PI;
    }

    while (current_absolute_orientation < 0) {
      current_absolute_orientation += 2 * M_PI;
    }

    // update global coordinates
    current_position.x += delta_x_global;
    current_position.y += delta_y_global;
    current_position.rotation = current_absolute_orientation;

    // The brain terminal can't handle printing faster than 50 ms
    if (time_elapsed % 50 == 0) {
      // printf("dl: %f, ds: %f, abs or: %f, x: %f, y: %f\n", total_delta_l,
      // total_delta_s, imu.get_heading(), current_position.x,
      // current_position.y);
      // printf("%f, %f\n", total_delta_l, total_delta_s);
      printf("%f, %f\n", current_position.x, current_position.y);
    }

    // delay to give other tasks time to do things
    time_elapsed += 10;
    pros::delay(10);  // ADI encoders refresh at max 10ms. This is an arbitrary
                      // limit set by vex because they were scared of our power.
  }
}
