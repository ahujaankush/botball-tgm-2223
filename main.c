#include <kipr/wombat.h>
#include <unistd.h>

#define SIDE_SENSOR 2
#define LEFT_SENSOR 1
#define RIGHT_SENSOR 0

struct sensor_data{
    int sensor_side_black;
    int sensor_side_white;

    int sensor_left_black;
    int sensor_left_white;

	int sensor_right_black;
    int sensor_right_white;
};

struct sensor_data calibrate_sensors(){
    struct sensor_data sensors;

    printf("%s\n", "Put both sensors on the line.");
    while(1)
        if(a_button_clicked())
            break;
    
    sensors.sensor_side_black = analog(SIDE_SENSOR);
    sensors.sensor_left_black = analog(LEFT_SENSOR);
    sensors.sensor_right_black = analog(RIGHT_SENSOR);
    
    printf("%s\n", "Put both sensors out of the line.");
    while(1)
        if(a_button_clicked())
            break;
    
    sensors.sensor_side_white = analog(SIDE_SENSOR);
    sensors.sensor_left_white = analog(LEFT_SENSOR);
    sensors.sensor_right_white = analog(RIGHT_SENSOR);
    
    printf("Calibrated:\n\tSensor_Side: %d, %d\n\tSensor_Left: %d, %d\n\tSensor_Right: %d, %d\n", sensors.sensor_side_black, sensors.sensor_side_white, sensors.sensor_left_black, sensors.sensor_left_white, sensors.sensor_right_black, sensors.sensor_right_white);
    
    return sensors;
}

void freezeB(){
    freeze(0);
    freeze(1);
}

// ALL GAS NO BRAKES
void AGNB(){
    fd(0); // LEFT
    fd(1); // RIGHT
}

void turnRight(){
    freezeB();
    
	mav(0, 1500);
    mav(1, -1500);
    
    msleep(800);
    
    freezeB();
}

void turnLeft(){
    freezeB();
    
	mav(0, -1500);
    mav(1, 1500);
    
    msleep(800);
    
    freezeB();
}

int main(){
	
    struct sensor_data sensors = calibrate_sensors();
    msleep(5000);
    
    /*
    struct sensor_data sensors;
    sensors.sensor_side_white = 162;
    sensors.sensor_right_white = 1176;
	sensors.sensor_left_white = 1247;
    */
    
    int intersection = 0;
    int onIntersection = 0;
    
    //sleep(5);
    
	AGNB();
    
    while(1){
        
        if(analog(LEFT_SENSOR) < sensors.sensor_left_white+200){
            freezeB();
            
            mav(0,1500);
            
            while(!((analog(LEFT_SENSOR) >= sensors.sensor_left_white+200) && (analog(RIGHT_SENSOR) >= sensors.sensor_right_white+200)));
            
			AGNB();
        }
            
        if(analog(RIGHT_SENSOR) < sensors.sensor_left_white+200){
            freezeB();
            
            mav(1, 1500);

            while(!((analog(LEFT_SENSOR) >= sensors.sensor_left_white+200) && (analog(RIGHT_SENSOR) >= sensors.sensor_right_white+200)));
            
			AGNB();
        }
        
        if(analog(SIDE_SENSOR) >= (sensors.sensor_side_white+200)){
            if(!onIntersection){
                intersection++;
            	printf("Intersections found: %d", intersection);
			}
            onIntersection++;
        }else{
        	onIntersection = 0;
        }
        
        if(intersection == 2){
            
            msleep(580);
            
        	turnRight();
        }
    }
    
    return 0;
}

