#include "subsystems/pid.hpp"

#include "api.h"

Pid::Pid(Pid::PidController controller) {
  this->ka = controller.ka;
  this->kp = controller.kp;
  this->ki = controller.ki;
  this->kd = controller.kd;
};

void Pid::reset() {
  prev_error = 0;
  total_error = 0;
  prev_output = 0;

  start_time = 0;
}

float Pid::update(double error) {
  // calculate output
  float delta_error = error - prev_error;
  float output = kp * error + ki * total_error + kd * delta_error;
  prev_output = output;
  prev_error = error;
  total_error += error;
  // printf("%f, %f, %f, %f\n", output, kp * error, ki * total_error,
  // kd * delta_error);
  return output;
}

bool Pid::settled() {
  if (start_time == 0) {  // if max_time has not been set
    start_time = pros::millis();
    return false;
  } else {  // check if the Pid has settled
    if (pros::millis() - start_time > max_time)
      return true;                              // max_time has been exceeded
    if (std::fabs(prev_error) < large_error) {  // large_error within range
      if (!large_time_counter)
        large_time_counter =
            pros::millis();  // large_time_counter has not been set
      else if (pros::millis() - large_time_counter > large_time)
        return true;  // large_time has been exceeded
    }
    if (std::fabs(prev_error) < small_error) {  // small_error within range
      if (!small_time_counter)
        small_time_counter =
            pros::millis();  // small_time_counter has not been set
      else if (pros::millis() - small_time_counter > small_time)
        printf("pid exited\n");
      return true;  // small_time has been exceeded
    }
    // if none of the exit conditions have been met
    return false;
  }
}
