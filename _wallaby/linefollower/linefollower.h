#pragma once
#include "../share.h"

/**
 * Stops both motors.
 **/
void freezeBoth();

/**
 * @brief All gas no brakes, full poewr drive
 */
void agnb();

/**
 * @brief Turn right
 *
 * @param speed how fast it should turn right
 * @param duration how long it should turn right (in ms)
 */
void turnRight(int speed, int duration);

/**
 * @brief Turn left
 *
 * @param speed how fast it should turn left
 * @param duration how long it should turn left (in ms)
 */
void turnLeft(int speed, int duration);

/**
 * @brief implementation of a finished line follower, has to be used in a loop
 *
 * @param lf_state state of the line folloewr as pointer
 * @param sensors sensordata, contains values for black and white
 */
void linefollower(struct linefollower_state *lf_state,
                  struct sensor_data sensors);
