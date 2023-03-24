#include "libwallaby/include/kipr/wallaby.h"
// #include <kipr/wallaby.h>
#include <stdio.h>
#include <unistd.h>
#include "share.h"
/**
 * Line follower for Botball 2023
 * @author Ankush Ahuja, Danko Vukoja
 * @version 2023-03-17
 **/

/**
 * Retuns sensor data
 * @return picked up sensor data <bold>Calibrated</bold>
 **/
struct sensor_data calibrate_sensors() {
  struct sensor_data sensors;

  printf("%s\n", "Put both sensors on the line.");
  // WAIT TILL BUTTON IS CLICKED
  while (1)
    if (a_button_clicked())
      break;

  // save data
  sensors.sensor_side_black = analog(SIDE_SENSOR);
  sensors.sensor_left_black = analog(LEFT_SENSOR);
  sensors.sensor_right_black = analog(RIGHT_SENSOR);

  // WAIT TILL BUTTON IS CLICKED
  printf("%s\n", "Put both sensors out of the line.");
  while (1)
    if (a_button_clicked())
      break;

  // save data
  sensors.sensor_side_white = analog(SIDE_SENSOR);
  sensors.sensor_left_white = analog(LEFT_SENSOR);
  sensors.sensor_right_white = analog(RIGHT_SENSOR);

  // print data
  printf("Calibrated:\n\tSensor_Side: %d, %d\n\tSensor_Left: %d, "
         "%d\n\tSensor_Right: %d, %d\n",
         sensors.sensor_side_black, sensors.sensor_side_white,
         sensors.sensor_left_black, sensors.sensor_left_white,
         sensors.sensor_right_black, sensors.sensor_right_white);

  return sensors;
}

/**
 * Freezes both motors
 **/
void freezeBoth() {
  freeze(LEFT_MOTOR);
  freeze(RIGHT_MOTOR);
}

/**
 * ALL GAS NO BRAKES
 * Drives forward with full speed
 **/
void agnb() {
  fd(LEFT_MOTOR);  // LEFT
  fd(RIGHT_MOTOR); // RIGHT
}

/**
 * Turns right
 */
void turnRight(int speed) {
  freezeBoth();

  mav(LEFT_MOTOR, 1500);
  mav(RIGHT_MOTOR, -1500);

  msleep(800);

  freezeBoth();
}

void turnLeft() {
  freezeBoth();

  mav(LEFT_MOTOR, -1500);
  mav(RIGHT_MOTOR, 1500);

  msleep(800);

  freezeBoth();
}

void linefollower(struct linefollower_state *lf_state,
                  struct sensor_data sensors) {

  /*
  struct sensor_data sensors;
  sensors.sensor_side_white = 162;
  sensors.sensor_right_white = 1176;
  sensors.sensor_left_white = 1247;
  */

  // sleep(5);


  // while (1) {

    if (analog(LEFT_SENSOR) < sensors.sensor_left_white + 200) {
      freezeBoth();

      mav(LEFT_MOTOR, 1500);

      while (!((analog(LEFT_SENSOR) >= sensors.sensor_left_white + 200) &&
               (analog(RIGHT_SENSOR) >= sensors.sensor_right_white + 200)))
        ;

      agnb();
    }

    if (analog(RIGHT_SENSOR) < sensors.sensor_left_white + 200) {
      freezeBoth();

      mav(RIGHT_SENSOR, 1500);

      while (!((analog(LEFT_SENSOR) >= sensors.sensor_left_white + 200) &&
               (analog(RIGHT_SENSOR) >= sensors.sensor_right_white + 200)))
        ;

      agnb();
    }

    if (analog(SIDE_SENSOR) >= (sensors.sensor_side_white + 200)) {
      if (!lf_state->onIntersection) {
        lf_state->intersection++;
        printf("Intersections found: %d", lf_state->intersection);
      }
      lf_state->onIntersection++;
    } else {
      lf_state->onIntersection = 0;
    }

    /*
    if(intersection == 2){

        msleep(580);

            turnRight();
    }
    */

  // }

}
