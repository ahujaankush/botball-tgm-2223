#pragma once

// DEFINE SENSORS
// ANALOG
#define SIDE_SENSOR 2
#define LEFT_SENSOR 1
#define RIGHT_SENSOR 0
// SENSOR FOR WAIT FOR LIGHT
#define LIGHT_PORT 3
// DISTANCE SENSOR
#define DISTANCE_SENSOR 4
// DIGITAL
#define RIGHT_BUMP 1
#define LEFT_BUMP 2

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
