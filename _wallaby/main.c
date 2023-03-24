#include "../libwallaby/include/kipr/wallaby.h"
// #include <kipr/wallaby.h>
#include "linefollower/linefollower.h"
#include "share.h"
#include <stdio.h>
#include <unistd.h>

/**
 * @brief calibrates the sensors
 *
 * @return picked up values in struct
 */
struct sensor_data calibrate_sensors() {
  struct sensor_data sensors;

  printf("%s\n", "Put both sensors on the line.");
  // WAIT TILL BUTTON IS CLICKED
  while (1)
    if (a_button_clicked())
      break;

  // save data
  sensors.side_black = analog(SIDE_SENSOR);
  sensors.left_black = analog(LEFT_SENSOR);
  sensors.right_black = analog(RIGHT_SENSOR);

  // WAIT TILL BUTTON IS CLICKED
  printf("%s\n", "Put both sensors out of the line.");
  while (1)
    if (a_button_clicked())
      break;

  // save data
  sensors.side_white = analog(SIDE_SENSOR);
  sensors.left_white = analog(LEFT_SENSOR);
  sensors.right_white = analog(RIGHT_SENSOR);

  // print data
  printf("Calibrated:\n\tSensor_Side: %d, %d\n\tSensor_Left: %d, "
         "%d\n\tSensor_Right: %d, %d\n",
         sensors.side_black, sensors.side_white,
         sensors.left_black, sensors.left_white,
         sensors.right_black, sensors.right_white);

  return sensors;
}

/**
 * @brief Implementation of linefollower
 *
 * @param lf_state pointer to linefollower_state
 * @param sensors picked up sensor values by calibrate_sensors()
 */
void linefollowerImp(struct linefollower_state *lf_state,
                     struct sensor_data sensors) {
  while (1) {
    linefollower(lf_state, sensors);

    if (digital(3)) {
      return;
    }
  }
  return;
}

/**
 * @brief Hardcoded route of the robot 🐹
 */
void route(struct linefollower_state *lf_state, struct sensor_data sensors) {
  // TURN RIGHT FOR CORRECT POSITION
  // ADJUST POS THAT CUBE IS RIGHT IN FRONT OF ROBOT
  // DRIVE FULLSPEED TILL CUBE
  // PICK CUBE UP
  // TURN LEFT
  // DRIVE TILL BLACK LINE
  // TURN LEFT
  // OPEN ARMS
  // DRIVE FORWARD
  // -----------
  // PLACE CUBE
}

int main() {
  // INFO: boilerplate code
  struct linefollower_state lf_state;
  lf_state.intersection = 0;
  lf_state.onIntersection = 0;
  struct sensor_data sensors = calibrate_sensors();
  msleep(5000);
  wait_for_light(LIGHT_PORT);
  shut_down_in(119);
  // INFO: END OF BOILERPLATE, ACTUAL PROGRAM
  agnb();
  route(&lf_state, sensors);
  return 0;
}
