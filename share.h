#pragma once
// DEFINE SENSORS
#define SIDE_SENSOR 2
#define LEFT_SENSOR 1
#define RIGHT_SENSOR 0

// DEFINE MOTORS
#define LEFT_MOTOR 0
#define RIGHT_MOTOR 1

struct sensor_data {
  int sensor_side_black;
  int sensor_side_white;

  int sensor_left_black;
  int sensor_left_white;

  int sensor_right_black;
  int sensor_right_white;
};

struct linefollower_state {
  int intersection;
  int onIntersection;
};
