#include "devices.h"
#include "main.h"
#include "subsystems/pid.hpp"
/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */

void autonomous() {
  printf("Started Auton\n");
  chassis.move_to_point(0, 10, 90, 75);
  // chassis.turn_to_point(10, 10, 75);
}
