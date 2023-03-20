#pragma once
// This is very much inspired from here:
// https://github.com/LemLib/LemLib/blob/master/src/lemlib/pid.cpp

class Pid {
 public:
  typedef struct {
    float ka;
    float kp;
    float ki;
    float kd;
    float small_error;
    float small_error_timeout;
    float large_error;
    float large_error_timeout;
  } PidController;

  Pid(PidController pid_controller);

  float update(double error);
  bool settled();

  void reset();

 private:
  float ka;
  float kp;
  float ki;
  float kd;

  float prev_error = 0;
  float total_error = 0;
  float prev_output = 0;

  float large_error;
  float small_error;
  int large_time = 0;
  int small_time = 0;
  int max_time = -1;  // -1 means no max time set, run forever

  int large_time_counter = 0;
  int small_time_counter = 0;
  int start_time = 0;
};
