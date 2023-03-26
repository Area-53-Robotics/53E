#include "api.h"
#include "subsystems/chassis/chassis.hpp"
#include "subsystems/pid.hpp"

// Conflicting ADI port definitions will cause a deadlock of some sort
//

inline Pid::PidController linear_pid_controller{
    0,    // ka
    10,   // kp
    0,    // ki
    30,   // kd
    1,    // small error
    100,  // small error timeout
    3,    // large error
    500,  // large error timeout
};

inline Pid::PidController rotational_pid_controller{
    1,    // ka
    2,    // kp
    0,    // ki
    10,   // kd
    1,    // small error
    100,  // small error timeout
    3,    // large error
    500,  // large error timeout
};

inline Chassis chassis(
    // Left motor ports
    {-12, -13, -14},
    // Right motor ports
    {18, 19, 20},
    // Gearset for drivetrain
    pros::E_MOTOR_GEAR_BLUE,
    // Left tracking wheel ports
    {'c', 'd'},
    // Center tracking wheel ports
    {'g', 'h'},
    // IMU port
    15,
    // Constants for pid
    linear_pid_controller, rotational_pid_controller);

inline pros::Controller controller(pros::E_CONTROLLER_MASTER);
// inline pros::ADILed led_strip(-1, 40);
