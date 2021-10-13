#include <stdio.h>
#include<unistd.h>
#include <webots/light_sensor.h>
#include <webots/distance_sensor.h>
#include <webots/motor.h>
#include <webots/robot.h>
#include <webots/inertial_unit.h>
#define MAX_SPEED 10
#define SPEED 6
#define TIME_STEP 64

int main() {
WbDeviceTag ls0, ls1,ls2, left_motor, right_motor,inner;
int i;
wb_robot_init();
/* get a handler to the distance sensors. */
ls0 = wb_robot_get_device("ls0");
ls1 = wb_robot_get_device("ls1");//left
ls2 =  wb_robot_get_device("back");
wb_light_sensor_enable(ls0, TIME_STEP);
wb_light_sensor_enable(ls1, TIME_STEP);
wb_light_sensor_enable(ls2, TIME_STEP);

WbDeviceTag ds[2];
  char ds_names[2][10] = {"ds_left", "ds_right"};
  
  for (i = 0; i < 2; i++) {
  ds[i] = wb_robot_get_device(ds_names[i]);
  wb_distance_sensor_enable(ds[i], TIME_STEP);
}
  
 inner = wb_robot_get_device("inner");
 wb_inertial_unit_enable(inner,TIME_STEP);


int rotation_counter = 0;
int counter_left = 0;
int counter_right = 0;
int stop_flag = 0;
int close_flag = 0;
//int close_left = 0;
//int close_right = 0;
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
  const double ls2_value = wb_light_sensor_get_value(ls2);
  
  
  printf("%f %f %f \n", ls1_value,ls0_value,ls2_value);
  
   double left_speed = 10;
   double right_speed = 10;
   

    if(rotation_counter >0){
      //真後ろにあるので回転中
      rotation_counter--;
      left_speed = -5;
      right_speed = 5;
      
    }else if(close_flag == 1 ){
    //近づいて止まる
     break;   
       
    }else if(counter_left >0){
       counter_left--;
       left_speed = 0;
       right_speed = 10;
       printf("a\n");
       
    }else if(counter_right > 0){
       counter_right--;
       left_speed = 10;
       right_speed = 0;
       printf("b\n");
            
    }else{
       if((ls2_value > ls0_value)&&(ls2_value > ls1_value)){
        //ボールがロボットの真後ろにある時　回転する
          rotation_counter=20;
          
       }else if(ls1_value > ls0_value){
       //向かって左にボールがある
         counter_left = 1;
         
       }else if(ls1_value < ls0_value){
        //向かって右にボールがある
         counter_right = 1;
       }
       else if(ls0_value==1024&&ls1_value==1024){
         //真正面にあるとき
          close_flag = 1;
       
       }
   } 
      /* Set the motor speeds. */
   wb_motor_set_velocity(left_motor, left_speed);
   wb_motor_set_velocity(right_motor, right_speed);
   
}


while (wb_robot_step(TIME_STEP) != 1) {
  double ds_values[2];
      
      for (i = 0; i < 2; i++)
        ds_values[i] = wb_distance_sensor_get_value(ds[i]);
   
   printf("%f %f \n",ds_values[0],ds_values[1]);
   
   double left_speed = 10;
   double right_speed = 10;
   
   if(stop_flag == 1){
   break;
   
     }else {
     if(ds_values[0] < 1000 || ds_values[1] < 1000 ){
     stop_flag =1;
     }
     
   }
   
   wb_motor_set_velocity(left_motor, left_speed);
   wb_motor_set_velocity(right_motor, right_speed);
}
 wb_motor_set_velocity(left_motor, 0);
 wb_motor_set_velocity(right_motor, 0);

int rotation_counter_2 = 0; 
double *role_value;
role_value = wb_inertial_unit_get_roll_pitch_yaw(inner);

printf("現在の角度　%f\n",role_value[2]);

//黄色のゴールだと　3.14の角度の方向に
//青色のゴールだと０の方向に回転する
//今回は黄色のゴールに向かう

if(role_value[2]<0.45 && 0 <=role_value[2]){
  rotation_counter_2 = 40;
  
}else if(role_value[2]<0.9 && 0.45 <=role_value[2]){
    rotation_counter_2 = 30;
}
else if(role_value[2]<1.35 && 0.9 <=role_value[2]){
    rotation_counter_2 = 24;
    
}
else if(role_value[2]<1.8 && 1.35 <=role_value[2]){
    rotation_counter_2 = 17;
}
else if(role_value[2]<2.25 && 1.8 <=role_value[2]){
    rotation_counter_2 = 14;
}
else if(role_value[2]<2.7 && 2.25 <=role_value[2]){
    rotation_counter_2 = 9;
    
}else if(role_value[2]<3 && 2.7 <=role_value[2]){
    rotation_counter_2 = 3;
}
else if(role_value[2]>= -0.45 && 0 > role_value[2]){
  rotation_counter_2 = -40;
}
else if(role_value[2]>= -0.9 && -0.45 > role_value[2]){
  rotation_counter_2 = -30;
  
}else if(role_value[2]>= -1.35 && -0.9 > role_value[2]){
  rotation_counter_2 = -24;

}else if(role_value[2]>= -1.8 && -1.35 > role_value[2]){
  rotation_counter_2 = -17;
}
else if(role_value[2]>= -2.25 && -1.6 > role_value[2]){
  rotation_counter_2 = -14;

}
else if(role_value[2]>= -2.7 && -2.25 > role_value[2]){
  rotation_counter_2 = -9;

}else if(role_value[2]>= -3 && -2.7 > role_value[2]){
  rotation_counter_2 = -3;
}

while(wb_robot_step(TIME_STEP) != 1){
   double left_speed = 10;
   double right_speed = 10;
   
  if(rotation_counter_2 == 0 ){
  //回転する必要なし
  printf("a\n");
  break;
  
  }else if(rotation_counter_2 > 0){
  //左周りに回転してゴールに正対する
  rotation_counter_2--;
  left_speed = -2;
  right_speed = 2;
   printf("b\n");
  
  }else {
  //右周りに回転してゴールに正対する
   rotation_counter_2++;
   left_speed = 2;
   right_speed = -2;
   printf("c\n");
   
  }
  
   wb_motor_set_velocity(left_motor, left_speed);
   wb_motor_set_velocity(right_motor, right_speed);
}
 
 //ゴールまで運ぶ
 wb_motor_set_velocity(left_motor, 10);
 wb_motor_set_velocity(right_motor, 10);
 
wb_robot_cleanup();
return 0;
}