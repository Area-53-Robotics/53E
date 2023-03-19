#include "api.h"
#include "subsystems/chassis/chassis.hpp"

// Conflicting ADI port definitions will cause a deadlock of some sort

inline Chassis chassis(
    // Left motor ports
    {-12, -13, -14},
    // Right motor ports
    {18, 19, 20},
    // Left tracking wheel ports
    {'c', 'd'},
    // Center tracking wheel ports
    {'g', 'h'},
    // IMU port
    15);

inline pros::Controller controller(pros::E_CONTROLLER_MASTER);
