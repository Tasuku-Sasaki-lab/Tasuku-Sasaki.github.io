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
ls0 = wb_robot_get_device("ls0");
ls1 = wb_robot_get_device("ls1");
wb_light_sensor_enable(ls0, TIME_STEP);
wb_light_sensor_enable(ls1, TIME_STEP);
int avoid_obstacle_counter_left = 0;
int avoid_obstacle_counter_right = 0;
/* get a handler to the motors and set target position to infinity (speed control). */
left_motor = wb_robot_get_device("wheel1");
right_motor = wb_robot_get_device("wheel2");
wb_motor_set_position(left_motor, INFINITY);
wb_motor_set_position(right_motor, INFINITY);

/*
wb_motor_set_velocity(left_motor, 0.0);
wb_motor_set_velocity(right_motor, 0.0);
*/

while (wb_robot_step(TIME_STEP) != 1) {
/* read sensor values */
const double ls0_value = wb_light_sensor_get_value(ls0);
const double ls1_value = wb_light_sensor_get_value(ls1);

printf("%f %f \n", ls0_value,ls1_value );

double left_speed = (1024 - ls0_value) / 100.0;
left_speed = (left_speed < MAX_SPEED) ? left_speed : MAX_SPEED;
double right_speed = (1024 - ls1_value) / 100.0;
right_speed = (right_speed < MAX_SPEED) ? right_speed : MAX_SPEED;


if (avoid_obstacle_counter_left > 0) {
avoid_obstacle_counter_left--;
left_speed = 3.0;
right_speed = -3.0;
}
else if (avoid_obstacle_counter_right > 0) {
avoid_obstacle_counter_right--;
left_speed = -3.0;
right_speed = 3.0;
}
else{
if(ls0_value - ls1_value >10){
avoid_obstacle_counter_right=5;
//printf("a");
}
else if(ls1_value - ls0_value>10){
avoid_obstacle_counter_left = 5;
//printf("b");
}
}

/* Set the motor speeds. */
wb_motor_set_velocity(left_motor, left_speed);
wb_motor_set_velocity(right_motor, right_speed);
}
wb_robot_cleanup();
return 0;
}