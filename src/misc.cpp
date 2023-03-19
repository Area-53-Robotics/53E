#include "devices.h"
#include "main.h"
#include "pros/llemu.hpp"

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

void area_53() {
  std::cout << R"(




       db         88888888ba   88888888888         db            8888888888    ad888888b,  
      d88b        88      "8b  88                 d88b           88           d8"     "88  
     d8'`8b       88      ,8P  88                d8'`8b          88  ____             a8P  
    d8'  `8b      88aaaaaa8P'  88aaaaa          d8'  `8b         88a8PPPP8b,       aad8"   
   d8YaaaaY8b     88""""88'    88"""""         d8YaaaaY8b        PP"     `8b       ""Y8,   
  d8""""""""8b    88    `8b    88             d8""""""""8b                d8          "8b  
 d8'        `8b   88     `8b   88            d8'        `8b      Y8a     a8P  Y8,     a88  
d8'          `8b  88      `8b  88888888888  d8'          `8b      "Y88888P"    "Y888888P'  
)" << '\n';

  std::cout << R"(
         ,,,,                                                              ,,,,
      ╔███████████▄▄,                                               ,▄▄██████████▄
     ,██▌    `^╙▀▀█████▄▄,                                    ,▄▄█████▀▀▀^     ╟██U
     `███        ,,,`╙▀█████▄                              ▄█████▀▀^,,,       ,▓██Ö
      ╙███▄    ▓██▀▀▀▓▒▄,`╙███,         ,,▄▄▄▄╓,          ▓██▀,,▄Æ█▀▀▀███   ,▄███▀
       `╚███▌  `▀▌      `╙▀▀████▄,  ╓▄█████████████▄  ,▄█████▀▀^      ╟█  ,▄███▀`
         `╚███▌, ╙▓▄  ╟█████▄▄╠███████▀^        ^▀███████▒▄▄█████▌  ╓▓▀ ,▄███▀`
           `╚▓███, ╙▀▄ ╚████████████╨       Ü      ╙████████████▀ ╓▒▀ ,████▀`
             `╙▀███▄ `▀▄ ▀█████████        ╔▒        ▓████████▀ ╔╩^ ╓████▀`
                ╙▀████▄ ╙w,╙██████`    ═M%▒▓▓▒▒M═    '██████▀,*╨ ╓▄███▀╨
                  `╚▀████▄`╙╗,▀███         ╙▒         ▓██▀^╔╜ ╓▄████▀^
                     `╙▀████▄^╩╦╠▓ ▓███▄    ▒   ▄▄███ ▓░▄╩^▄█████▀^
                        `╙▀████▄╙▀U██████▄    ▄██████,▀^▄█████▀`
                      ▄████████████╙███████  ▓██████╩▓███████████▄,
                   ╓▄███▀▓█▀▀▓█████▌`▀█████  █████▀ ╢██████╙▀█▓▀████▄
                ,▄███▀^▄▓▀╓█████████▌  `^^   `^^   ╫█████████▄╙▓▄`▀███▌,
              ▄███▀^,▄▀^▄█████████████           ,█████████████▄^▀▌,╙▀███▄
           ,▄███▀ ╓▓▀  ╫███████▀▀▄▄▒▀▓█▄        ▄██▀▀▄▄▀▀████████  ╙▓▄ ▀████,
         ╓███▀^ ,▓▀    ╙▀▀▀^,▄Æ▀▀▄▄██████▄,  ,▄██████▄▄╙▀W▄▄^▀▀▀▀    ╙▓U ^▀███▄
       ╓███▀   ╔██▄   ,╓▄Æ╩╨,▄▄█████▀╨╙▀████████▀╙╙▀▀█████▄,╙▀W▄▄,, ,╓██U   ▀███▄
      ╢██▀     `▀▀▀▀▀▀^ ,▄█████▀▀╙`      ^╙▀▀╨^      `^▀▀█████▄╓ ^▀▀▀▀▀▀^     ▀███
     )██▌          ,▄▄█████▀▀^`                          `^╙▀██████▄╓          ╟██▌
     `▀███▄▄▄▄▄███████▀▀╙`                                    `╙▀▀███████▄▄▄▄▄████`
       ╙▀▀█████▀▀▀▀╙`                                              `^╙▀▀▀█████▀▀╨
     
)" << '\n';
}
void initialize() {
  pros::lcd::initialize();
  pros::lcd::set_text(1, "MANKIND IS DEAD");
  pros::lcd::set_text(2, "BLOOD IS FUEL");
  pros::lcd::set_text(3, "HELL IS FULL");
  pros::lcd::set_background_color(255, 0, 0);
  area_53();

  chassis.init();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}
