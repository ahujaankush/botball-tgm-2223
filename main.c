#include "libwallaby/include/kipr/wallaby.h"
// #include <kipr/wallaby.h>
#include "linefollower.h"
#include "share.h"
#include <stdio.h>
#include <unistd.h>

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

int linefollowerImp(struct linefollower_state *lf_state,
                    struct sensor_data sensors) {
  while (1) {
    linefollower(lf_state, sensors);

    if (digital(3)) {
      return 0;
    }
  }
  return 0;
}

int main() {
  struct linefollower_state lf_state;
  lf_state.intersection = 0;
  lf_state.onIntersection = 0;
  struct sensor_data sensors = calibrate_sensors();
  msleep(5000);
  agnb();
  linefollowerImp(&lf_state, sensors);
  return 0;
}
