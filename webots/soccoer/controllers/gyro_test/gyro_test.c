/*
 * File:          gyro_test.c
 * Date:
 * Description:
 * Author:
 * Modifications:
 */

/*
 * You may need to add include files like <webots/distance_sensor.h> or
 * <webots/motor.h>, etc.
 */
#include<stdio.h>
#include <webots/robot.h>
#include <webots/gyro.h>
#include <webots/motor.h>
/*
 * You may want to add macros here.
 */
#define TIME_STEP 64

/*
 * This is the main program.
 * The arguments of the main function can be specified by the
 * "controllerArgs" field of the Robot node
 */
int main(int argc, char **argv) {
  int i;
  /* necessary to initialize webots stuff */
  wb_robot_init();

  /*
   * You should declare here WbDeviceTag variables for storing
   * robot devices like this:
   *  WbDeviceTag my_sensor = wb_robot_get_device("my_sensor");
   *  WbDeviceTag my_actuator = wb_robot_get_device("my_actuator");
   */
   
     WbDeviceTag gyo = wb_robot_get_device("gyro");
   

  WbDeviceTag left_motor = wb_robot_get_device("wheel1");
  WbDeviceTag right_motor = wb_robot_get_device("wheel2");
  
  wb_motor_set_position(left_motor, INFINITY);
  wb_motor_set_position(right_motor, INFINITY);
  /* main loop
   * Perform simulation steps of TIME_STEP milliseconds
   * and leave the loop when the simulation is over
   */
   wb_gyro_enable(gyo,TIME_STEP);
   
   int count =0;
  while (wb_robot_step(TIME_STEP) != -1) {
  count++;
  if (count==10) break;
    /*
     * Read the sensors :
     * Enter here functions to read sensor data, like:
     *  double val = wb_distance_sensor_get_value(my_sensor);
     */
  
     
   double left_speed = 10;
   double right_speed = -10;
      
  
          /*
     * Enter here functions to send actuator commands, like:
     * wb_motor_set_position(my_actuator, 10.0);
     */
     
      
     
     wb_motor_set_velocity(left_motor, left_speed);
   wb_motor_set_velocity(right_motor, right_speed);
   
  };
  wb_motor_set_velocity(left_motor, 0);
   wb_motor_set_velocity(right_motor,0);
   
  wb_gyro_disable(gyo);


 printf("%d ",wb_gyro_get_sampling_period(gyo));
    /* Process sensor data here */
    double  *gyro_values;
    gyro_values = wb_gyro_get_values(gyo);
      
      for(i = 0;i< 3;i++){
      printf("%f ",gyro_values[i]);
      }
      printf("\n");
  /* Enter your cleanup code here */

  /* This is necessary to cleanup webots resources */
  wb_robot_cleanup();

  return 0;
}
