#include <kipr/wombat.h>
#include <unistd.h>
#include <stdio.h>

#define LIGHT_SENSOR_0 0
#define LIGHT_SENSOR_1 1

struct sensor_data{
    int sensor_0_black;
    int sensor_0_white;

    int sensor_1_black;
    int sensor_1_white;
};

struct sensor_data calibrate_sensors(){
    struct sensor_data sensors;

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

    printf("Calibrated:\n\tSensor 0: %d, %d\n\tSensor 1: %d, %d\n", sensors.sensor_0_black, sensors.sensor_0_white, sensors.sensor_1_black, sensors.sensor_1_white);

    return sensors;
}

int main(){

    struct sensor_data sensors = calibrate_sensors();
    
    //fd(0);		//LINKS
    //sleep(1);
    //analog(1) 	LINKS
    
	while(1){
        freeze(0);
        freeze(1);
        
    	mav(0, 1450);
        mav(1, 1500);

        if(analog(1) >= sensors.sensor_1_white+200){
            freeze(0);
            freeze(1);
            mav(0, 100);

            while(!((analog(1) < sensors.sensor_1_white+10) || (analog(1) > sensors.sensor_1_white-10)));
        }
    }
    
    return 0;
}
