#pragma once

// DEFINE SENSORS
#define SIDE_SENSOR 2
#define LEFT_SENSOR 1
#define RIGHT_SENSOR 0
// SENSOR FOR WAIT FOR LIGHT
#define LIGHT_PORT 3
// DEFINE MOTORS
#define LEFT_MOTOR 0
#define RIGHT_MOTOR 1

struct sensor_data {
  int side_black;
  int side_white;

  int left_black;
  int left_white;

  int right_black;
  int right_white;
};

struct linefollower_state {
  int intersection;
  int onIntersection;
};
