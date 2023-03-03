#include <kipr/wombat.h>
#include <unistd.h>

#define SIDE_SENSOR 2
#define LEFT_SENSOR 1
#define RIGHT_SENSOR 0

struct sensor_data {
  int sensor_side_black;
  int sensor_side_white;

  int sensor_left_black;
  int sensor_left_white;

  int sensor_right_black;
  int sensor_right_white;
};

struct sensor_data calibrate_sensors() {
  struct sensor_data sensors;

  printf("%s\n", "Put both sensors on the line.");
  while (1)
    if (a_button_clicked())
      break;

  sensors.sensor_side_black = analog(SIDE_SENSOR);
  sensors.sensor_left_black = analog(LEFT_SENSOR);
  sensors.sensor_right_black = analog(RIGHT_SENSOR);

  printf("%s\n", "Put both sensors out of the line.");
  while (1)
    if (a_button_clicked())
      break;

  sensors.sensor_side_white = analog(SIDE_SENSOR);
  sensors.sensor_left_white = analog(LEFT_SENSOR);
  sensors.sensor_right_white = analog(RIGHT_SENSOR);

  printf("Calibrated:\n\tSensor_Side: %d, %d\n\tSensor_Left: %d, "
         "%d\n\tSensor_Right: %d, %d\n",
         sensors.sensor_side_black, sensors.sensor_side_white,
         sensors.sensor_left_black, sensors.sensor_left_white,
         sensors.sensor_right_black, sensors.sensor_right_white);

  /*
  printf("%s\n", "Put both sensors on the line.");
  while(1)
      if(a_button_clicked())
          break;

  sensors.sensor_0_black = analog(LIGHT_SENSOR_0);
  sensors.sensor_1_black = analog(LIGHT_SENSOR_1);

  printf("%s\n", "Put both sensors outside the line.");
  while(1)
      if(a_button_clicked())
          break;

  sensors.sensor_0_white = analog(LIGHT_SENSOR_0);
  sensors.sensor_1_white = analog(LIGHT_SENSOR_1);

  printf("Calibrated:\n\tSensor 0: %d, %d\n\tSensor 1: %d, %d\n",
  sensors.sensor_0_black, sensors.sensor_0_white, sensors.sensor_1_black,
  sensors.sensor_1_white);
      */

  return sensors;
}

void freezeB() {
  freeze(0);
  freeze(1);
}

int main() {

  struct sensor_data sensors = calibrate_sensors();

  sleep(5);

  fd(0); // LEFT
  fd(1); // RIGHT

  // FD SLOWS THE ROBOT?

  while (1) {

    if (analog(LEFT_SENSOR) < sensors.sensor_left_white + 200) {
      freezeB();

      mav(0, 1500);
      mav(1, 1300);

      while (!((analog(LEFT_SENSOR) >= sensors.sensor_left_white + 200) &&
               (analog(RIGHT_SENSOR) >= sensors.sensor_right_white + 200)))
        ;
      fd(0);
      fd(1);

      // printf("%s", "LEFT OUTSIDE");
      // break;
    }

    if (analog(RIGHT_SENSOR) < sensors.sensor_left_white + 200) {
      freezeB();

      mav(0, 1300);
      mav(1, 1500);

      while (!((analog(LEFT_SENSOR) >= sensors.sensor_left_white + 200) &&
               (analog(RIGHT_SENSOR) >= sensors.sensor_right_white + 200)))
        ;

      fd(0);
      fd(1);

      // printf("%s", "RIGHT OUTSIDE");
      //  break;
    }
  }

  // printf("LEFT:  %d, ON LINE: %s\n", analog(LEFT_SENSOR), analog(LEFT_SENSOR)
  // >= sensors.sensor_left_white+200 ? "YES" : "NO"); printf("RIGHT: %d, ON
  // LINE: %s\n", analog(RIGHT_SENSOR), analog(RIGHT_SENSOR) >=
  // sensors.sensor_left_white+200 ? "YES" : "NO"); printf("SIDE:  %d, OUTSIDE
  // LINE: %s\n", analog(SIDE_SENSOR), analog(SIDE_SENSOR) <=
  // sensors.sensor_side_white+200 ? "YES" : "NO");

  // sleep(2);

  // if(analog(LEFT_SENSOR) >= sensors.sensor_left_white+200){
  //	mav(1, 500);
  //	while(!((analog(LEFT_SENSOR) >= sensors.sensor_left_white+200) &&
  //(analog(RIGHT_SENSOR) >= sensors.sensor_right_white+200)));
  // }

  // if(analog(RIGHT_SENSOR) >= sensors.sensor_right_white+200){
  //	mav(0, 500);
  //     while(!((analog(LEFT_SENSOR) >= sensors.sensor_left_white+200) &&
  //     (analog(RIGHT_SENSOR) >= sensors.sensor_right_white+200)));
  // }

  // fd(0);
  // fd(1);

  /*
  while((analog(LEFT_SENSOR) >= sensors.sensor_left_white+200) &&
  (analog(RIGHT_SENSOR) >= sensors.sensor_right_white+200)){
      if(analog(SIDE_SENSOR) >= sensors.sensor_side_white+200){
          break;
      }
  }
*/

  return 0;
}
