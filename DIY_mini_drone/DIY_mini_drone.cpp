#include <Arduino.h>
#include <Wire.h>
#include "MPU6050.h"
#include "UART.h"
#include "Timer2.h"
#include "CalculateAngle.h"
#include "Interrupt.h"
#include "RF24_USER.h"
#include "JoyStick.h"
#include "PWM.h"
#include "PID_Control.h"
#include "DIY_mini_drone.h"



unsigned char motor_arming_flag = 0;
float roll_target;
float pitch_target;
float yaw_target;

short OCR1;
short OCR2;
short OCR3;
short OCR4;


void setup()
{
  /* Init Periperal */
  Wire.begin();                 // I2C Master mode init
  Serial.begin(115200);         // UART init
  Serial.println("hello world");
  Timer2_Init();
  
  /* Init Module */
  MPU6050_Init();
  RF24_Rx_Init();
  PWM_Init();
  PID_Gain_Init();
}

void loop()
{
  
  Check_Arming();
  Reflect_JoyStick(&roll_target, &pitch_target, &yaw_target);
  
  if(Timer2_2ms_flag == 1)
  {
    Timer2_2ms_flag = 0;
    MPU6050_Read_Data(&mpu6050);
    MPU6050_Convert_Data(&mpu6050);
    CalculateCompliFilter(&Angle, &mpu6050);
    
    Double_Roll_Pitch_PID_Calculation(&roll,  roll_target, Angle.ComFilt_roll, mpu6050.gyro_y);
    Double_Roll_Pitch_PID_Calculation(&pitch, pitch_target, Angle.ComFilt_pitch, mpu6050.gyro_x);
    Single_Yaw_Heading_PID_Calculation(&yaw_heading, yaw_target, Angle.ComFilt_yaw, mpu6050.gyro_z);

    OCR1 = LV / 4.5f - pitch.in.pid_result + roll.in.pid_result -yaw_heading.pid_result;
    OCR2 = LV / 4.5f + pitch.in.pid_result + roll.in.pid_result +yaw_heading.pid_result;
    OCR3 = LV / 4.5f + pitch.in.pid_result - roll.in.pid_result -yaw_heading.pid_result;
    OCR4 = LV / 4.5f - pitch.in.pid_result - roll.in.pid_result +yaw_heading.pid_result;
  }

  Reflect_Motor();
  
}





void Check_Arming(void)
{
/********************* Motor Arming State ************************/
  if(SwA == 1 && SwA_Prev == 0)
  {
    if(LV < 20)
    {
      motor_arming_flag = 1;
      
      //Set target !
      yaw_target = Angle.ComFilt_yaw;
      roll_target = 0.f;
      pitch_target = 0.f;
    }
    else
    {
      motor_arming_flag = 0;
    }
  }
  SwA_Prev = SwA;
}


void Reflect_Motor(void)
{
  if(motor_arming_flag == 1)
  {
    if(LV>20)
    {
      OCR0B = OCR1 > MOTOR_MAX ? MOTOR_MAX : OCR1 < MOTOR_MIN ? MOTOR_MIN : OCR1; //D5
      OCR0A = OCR2 > MOTOR_MAX ? MOTOR_MAX : OCR2 < MOTOR_MIN ? MOTOR_MIN : OCR2; //D6
      OCR1A = OCR3 > MOTOR_MAX ? MOTOR_MAX : OCR3 < MOTOR_MIN ? MOTOR_MIN : OCR3; //D9
      OCR1B = OCR4 > MOTOR_MAX ? MOTOR_MAX : OCR4 < MOTOR_MIN ? MOTOR_MIN : OCR4; //D10
    }
    else
    {
      OCR0B = MOTOR_MIN;
      OCR0A = MOTOR_MIN;
      OCR1A = MOTOR_MIN;
      OCR1B = MOTOR_MIN;
    }
  }
  else
  {
    OCR0B = 0;
    OCR0A = 0;
    OCR1A = 0;
    OCR1B = 0;
  }
}
