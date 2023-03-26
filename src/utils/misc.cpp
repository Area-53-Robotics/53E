#include <cmath>
#include <iostream>

#include "utils.hpp"

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

// Math
int limit(double input, int min, int max) {
  if (input > max) {
    return max;
  } else if (input < min) {
    return min;
  } else {
    return input;
  }
}

float rad_to_deg(float input) { return input * 180 / M_PI; }

float deg_to_rad(float input) { return input * M_PI / 180; }

float angle_error(float angle1, float angle2, bool radians) {
  float max = radians ? 2 * M_PI : 360;
  float half = radians ? M_PI : 180;
  angle1 = fmod(angle1, max);
  angle2 = fmod(angle2, max);
  float error = angle1 - angle2;
  if (error > half)
    error -= max;
  else if (error < -half)
    error += max;
  return error;
}

float slew(float target, float current, float max_change) {
  float change = target - current;
  if (max_change == 0) return target;
  if (change > max_change)
    change = max_change;
  else if (change < -max_change)
    change = -max_change;
  return current + change;
}
