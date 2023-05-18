#include <Wire.h>
#include "MPU6050.h"
#include "UART.h"
#include "Timer1.h"
#include "CalculateAngle.h"
#include "Interrupt.h"


void setup() {
  /* Init Periperal */
  Wire.begin();                 // I2C Master mode init
  Serial.begin(115200);         // UART init

  Serial.println("hello world");
  /* Init Module */
  MPU6050_INIT();

  pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);
  
  Timer1_Init();

}

void loop() {
  if(Timer1_2ms_flag == 1)
  {
    Timer1_2ms_flag = 0;
    MPU6050_Read_Data(&mpu6050);
    MPU6050_Convert_Data(&mpu6050);
    CalculateCompliFilter(&Angle, &mpu6050);
    print_3_float(Angle.ComFilt_roll, Angle.ComFilt_pitch, Angle.ComFilt_yaw);
  }
}
