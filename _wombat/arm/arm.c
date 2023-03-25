#pragma once
#include "../../libwallaby/include/kipr/wallaby.h"
// #include <kipr/wallaby.h>

void closeArm(){
  set_servo_position(0, 1240);
}

void openArm(){
  set_servo_position(0, 900);
}

