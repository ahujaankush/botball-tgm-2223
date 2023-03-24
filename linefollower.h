#pragma once
#include "share.h"

/**
 * Sets sensor_data struct with values picked up from sensor
 **/
struct sensor_data calibrate_sensors();

/**
 * Stops both motors.
 **/
void freezeBoth();

/**
 * All gas no break;
 **/
void agnb();

/**
 * turn right.
 **/
void turnRight(int speed);

/**
 * right left.
 **/
void turnLeft();

/**
 * linefollower implementation
 *
 **/
void linefollower(struct linefollower_state *lf_state,
                  struct sensor_data sensors);
