#include <stdio.h>
#include <webots/light_sensor.h>
#include <webots/motor.h>
#include <webots/robot.h>
#define MAX_SPEED 20
#define SPEED 6
#define TIME_STEP 64
int main() {
WbDeviceTag ls0, ls1, left_motor, right_motor;
wb_robot_init();
/* get a handler to the distance sensors. */
ls0 = wb_robot_get_device("ls0");//right
ls1 = wb_robot_get_device("ls1");//left
ls2 =  wb_robot_get_device("back");
wb_light_sensor_enable(ls0, TIME_STEP);
wb_light_sensor_enable(ls1, TIME_STEP);
wb_light_sensor_enable(ls2, TIME_STEP);
/* get a handler to the motors and set target position to infinity (speed control). */
/*
left_motor = wb_robot_get_device("wheel1");
right_motor = wb_robot_get_device("wheel2");
wb_motor_set_position(left_motor, INFINITY);
wb_motor_set_position(right_motor, INFINITY);

/*
wb_motor_set_velocity(left_motor, 0.0);
wb_motor_set_velocity(right_motor, 0.0);
*/

while (wb_robot_step(TIME_STEP) != 1) {
/* read sensor values */ double ls0_value = wb_light_sensor_get_value(ls0);
double ls1_value = wb_light_sensor_get_value(ls1);
double ls2_value = wb_light_sensor_get_value(ls2)



/*
double left_speed = (1024 - ls0_value) / 100.0;
left_speed = (left_speed < MAX_SPEED) ? left_speed : MAX_SPEED;
double right_speed = (1024 - ls1_value) / 100.0;
right_speed = (right_speed < MAX_SPEED) ? right_speed : MAX_SPEED;



wb_motor_set_velocity(left_motor, left_speed);
wb_motor_set_velocity(right_motor, right_speed);
*/
}
wb_robot_cleanup();
return 0;
}