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
void freezeBoth() { create_drive_direct(0, 0); }

/**
 * @brief All gas no brakes, full poewr drive
 */
void agnb() { create_drive_direct(500, 500); }

/**
 * @brief Turn right
 *
 * @param speed how fast it should turn right
 * @param duration how long it should turn right (in ms)
 */
void turnRight(int speed, int duration) {
  freezeBoth();

  create_drive_direct(speed, -speed);
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

  create_drive_direct(-speed, speed);
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

}
