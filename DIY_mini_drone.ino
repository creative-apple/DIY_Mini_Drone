#include <Wire.h>
#include "MPU6050.h"
#include "UART.h"

Struct_MPU6050 mpu6050;

void setup() {
  /* Init Periperal */
  Wire.begin();                 // I2C Master mode init
  Serial.begin(115200);         // UART init

  Serial.println("hello world");
  /* Init Module */
  MPU6050_INIT();
  
}

void loop() {
//  MPU6050_Read_Data(&mpu6050);
//  MPU6050_Convert_Data(&mpu6050);


  delay(100);
}
