#pragma once
#include "../../libwallaby/include/kipr/wallaby.h"
// #include <kipr/wallaby.h>
#include "../share.h"
#include <stdio.h>
#include <unistd.h>

/**
 * Line follower for Botball 2023
 * @author Ankush Ahuja, Danko Vukoja
 * @version 2023-03-17
 **/

/**
 * @brief Stops both motors
 */
void freezeBoth() {
  freeze(LEFT_MOTOR);
  freeze(RIGHT_MOTOR);
}

/**
 * @brief All gas no brakes, full power drive
 */
void agnb() {
  fd(LEFT_MOTOR);  // LEFT
  fd(RIGHT_MOTOR); // RIGHT
}

/**
 * @brief All gas no brakes, full power drive but backwards
 */
void agnbb() {
  bk(LEFT_MOTOR);  // LEFT
  bk(RIGHT_MOTOR); // RIGHT
}

/**
 * @brief Turn right
 *
 * @param speed how fast it should turn right
 * @param duration how long it should turn right (in ms)
 */
void turnRight(int speed, int duration) {
  freezeBoth();

  mav(LEFT_MOTOR, speed);
  mav(RIGHT_MOTOR, -speed);

  msleep(duration);

  freezeBoth();
}

/**
 * @brief Turn left
 *
 * @param speed how fast it should turn left
 * @param duration how long it should turn left (in ms)
 */
void turnLeft(int speed, int duration) {
  freezeBoth();

  mav(LEFT_MOTOR, -speed);
  mav(RIGHT_MOTOR, speed);

  msleep(duration);

  freezeBoth();
}
/**
 * @brief implementation of a finished line follower, has to be used in a loop
 *
 * @param lf_state state of the line folloewr as pointer
 * @param sensors sensordata, contains values for black and white
 */
void linefollower(struct linefollower_state *lf_state,
                  struct sensor_data sensors) {

  if (analog(LEFT_SENSOR) < sensors.left_white + 200) {
    freezeBoth();

    mav(LEFT_MOTOR, 1500);

    while (!((analog(LEFT_SENSOR) >= sensors.left_white + 200) &&
             (analog(RIGHT_SENSOR) >= sensors.right_white + 200)))
      ;

    agnb();
  }

  if (analog(RIGHT_SENSOR) < sensors.left_white + 200) {
    freezeBoth();

    mav(RIGHT_SENSOR, 1500);

    while (!((analog(LEFT_SENSOR) >= sensors.left_white + 200) &&
             (analog(RIGHT_SENSOR) >= sensors.right_white + 200)))
      ;

    agnb();
  }

  if (analog(SIDE_SENSOR) >= (sensors.side_white + 200)) {
    if (!lf_state->onIntersection) {
      lf_state->intersection++;
      printf("Intersections found: %d", lf_state->intersection);
    }
    lf_state->onIntersection++;
  } else {
    lf_state->onIntersection = 0;
  }
}
