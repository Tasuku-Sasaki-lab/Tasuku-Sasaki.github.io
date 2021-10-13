#include <webots/robot.h>
#include<stdio.h>
// Added a new include file
#include <webots/motor.h>
#include <webots/distance_sensor.h>
#define TIME_STEP 64

int main(int argc, char **argv) {
  wb_robot_init();
  int i;
  int avoid_obstacle_counter_left = 0;
  int avoid_obstacle_counter_right = 0;

  WbDeviceTag ds[2];
  char ds_names[2][10] = {"ds_left", "ds_right"};
  
  for (i = 0; i < 2; i++) {
  ds[i] = wb_robot_get_device(ds_names[i]);
  wb_distance_sensor_enable(ds[i], TIME_STEP);
  }
  
  WbDeviceTag left_motor = wb_robot_get_device("wheel1");
  WbDeviceTag right_motor = wb_robot_get_device("wheel2");
  
  wb_motor_set_position(left_motor, INFINITY);
  wb_motor_set_position(right_motor, INFINITY);
  
    wb_motor_set_velocity(left_motor, 0.0);
wb_motor_set_velocity(right_motor, 0.0);
  
  while (wb_robot_step(TIME_STEP) != -1) {
 double ds_values[2];
      
      for (i = 0; i < 2; i++)
        ds_values[i] = wb_distance_sensor_get_value(ds[i]);
     printf("%f %f \n",ds_values[0],ds_values[1]);
  }
  wb_robot_cleanup();
  return 0; // EXIT_SUCCESS
  }