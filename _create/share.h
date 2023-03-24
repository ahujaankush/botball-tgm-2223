#pragma once

// NO NEED TO DEFINE SENSOR PORTS (INFRA)
// SENSOR FOR WAIT FOR LIGHT
#define LIGHT_PORT 3
// NO NEED TO DEFINE MOTORS

struct sensor_data {
  int rf_black;
  int rf_gray;
  int rf_white;

  int lf_black;
  int lf_gray;
  int lf_white;

  int rb_black;
  int rb_gray;
  int rb_white;

  int lb_black;
  int lb_gray;
  int lb_white;
};

struct linefollower_state {
  int intersection;
  int onIntersection;
};
