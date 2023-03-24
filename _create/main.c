#include "../libwallaby/include/kipr/create.h"
#include "../libwallaby/include/kipr/wallaby.h"
// #include <kipr/wallaby.h>
// #include <kipr/create.h>
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

  printf("%s\n", "Put sensors rf & lf on black line");
  // WAIT TILL BUTTON IS CLICKED
  while (1)
    if (a_button_clicked())
      break;

  // save data for *f_black
  sensors.rf_black = get_create_rfcliff();
  sensors.lf_black = get_create_lfcliff();

  printf("%s\n", "Put sensors rb & lb on black line");
  // WAIT TILL BUTTON IS CLICKED
  while (1)
    if (a_button_clicked())
      break;

  // save data for *b_black
  sensors.rb_black = get_create_rcliff();
  sensors.lb_black = get_create_lcliff();

  printf("%s\n", "Put sensors rf & lf on grey line");
  // WAIT TILL BUTTON IS CLICKED
  while (1)
    if (a_button_clicked())
      break;

  // save data for *f_gray
  sensors.rf_gray = get_create_rfcliff();
  sensors.lf_gray = get_create_lfcliff();

  printf("%s\n", "Put sensors rb & lb on grey line");
  // WAIT TILL BUTTON IS CLICKED
  while (1)
    if (a_button_clicked())
      break;

  // save data for *b_gray
  sensors.rb_gray = get_create_rcliff();
  sensors.lb_gray = get_create_lcliff();

  printf("%s\n", "Put sensors rf, lf, rb & lb on white spot");
  // WAIT TILL BUTTON IS CLICKED
  while (1)
    if (a_button_clicked())
      break;

  // save data for *_white
  sensors.rf_white = get_create_rfcliff();
  sensors.lf_white = get_create_lfcliff();
  sensors.rb_white = get_create_rcliff();
  sensors.lb_white = get_create_lcliff();

  // print data
  printf("Calibrated (Black, Gray, White):\n\tSensor_Front_Right: %d, %d, "
         "%d\n\tSensor_Front_Left: "
         "%d, %d, %d\n\tSensor_Behind_Right: %d, %d, %d\n\tSensor_Behind_Left: "
         "%d, %d, %d",
         sensors.rf_black, sensors.rf_gray, sensors.rf_white, sensors.lf_black,
         sensors.lf_gray, sensors.lf_white, sensors.rb_black, sensors.rb_gray,
         sensors.rb_white, sensors.lb_black, sensors.lb_gray, sensors.lb_white);

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
  // DRIVE FORWARD TILL BLACK LINE
  // REMOVE RINGS WITH ARM
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
