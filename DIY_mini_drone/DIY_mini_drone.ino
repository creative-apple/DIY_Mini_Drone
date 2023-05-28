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

unsigned char motor_arming_flag = 0;
unsigned short iBus_SwA_Prev = 0;

void setup()
{
  /* Init Periperal */
  Wire.begin();                 // I2C Master mode init
  Serial.begin(115200);         // UART init
  Serial.println("hello world");

//  Timer2_Init();
  
  /* Init Module */
//  MPU6050_INIT();
  RF24_Rx_Init();

  attachInterrupt(digitalPinToInterrupt(2), RF24_Rx_Read, FALLING);
//  PWM_Init();

}

void loop()
{
//  if(Timer2_2ms_flag == 1)
//  {
//    Timer2_2ms_flag = 0;
//    MPU6050_Read_Data(&mpu6050);
//    MPU6050_Convert_Data(&mpu6050);
//    CalculateCompliFilter(&Angle, &mpu6050);
////    Serial.println((String) LV +" "+ LH+" " + RV+" " + RH);
////    Double_Roll_Pitch_PID_Calculation(&pitch, (RV * 1000.f/1023.f -500 ) * 0.04f, Angle.ComFilt_pitch, mpu6050.gyro_x);
////    Double_Roll_Pitch_PID_Calculation(&roll,  (RL * 1000.f/1023.f -500 ) * 0.04f, Angle.ComFilt_roll, mpu6050.gyro_y);
//  }

//  if(motor_arming_flag == 1)
//  {
//    OCR0A = LV/4;
//    OCR0B = LH/4;
//    OCR1A = RV/4;
//    OCR1B = RH/4;
//  }

  
}
