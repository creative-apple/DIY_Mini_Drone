#include <Wire.h>
#include "MPU6050.h"
#include "UART.h"
#include "Timer.h"

extern int Timer_1ms_flag;
extern int Timer_2ms_flag;
extern int Timer_10ms_flag;
extern int Timer_100ms_flag;
extern int Timer_1000ms_flag;

Struct_MPU6050 mpu6050;
char toggle0=1;

void setup() {
  /* Init Periperal */
//  Wire.begin();                 // I2C Master mode init
  Serial.begin(115200);         // UART init

  Serial.println("hello world");
  /* Init Module */
//  MPU6050_INIT();

  pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);
  
  Timer1_Init();
 
}

void loop() {
//  MPU6050_Read_Data(&mpu6050);
//  MPU6050_Convert_Data(&mpu6050);


 if(Timer_2ms_flag == 1)
  {
    Timer_2ms_flag = 0;
    digitalWrite(12,digitalRead(12)^1);
  }


}
