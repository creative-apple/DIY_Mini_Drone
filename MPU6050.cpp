#include <Arduino.h>
#include <Wire.h>
#include "MPU6050.h"


void MPU6050_INIT(void)
{ 
  /* Check MPU6050 connection */
  uint8_t who_am_i = 0;
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(0x75);  //WHO_AM_I register
  Wire.endTransmission(false);
  Wire.requestFrom(MPU6050_ADDR,1,true);  // request a total of 14 registers
  who_am_i = Wire.read();
  if(who_am_i == 0x68)
  {
    Serial.println("MPU6050 who_am_i = 0x68...OK");
  }
  else
  {
    Serial.println("ERROR!");
    Serial.println("MPU6050 who_am_i is not 0x68");
    while(1)
    {
      Serial.println("who am i error. Can not recognize mpu6050");
      delay(100);
    }
  }

  /* Factory Reset MPU6050 */
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(1<<7);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);

  /*wakes up the MPU6050*/
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
}

void MPU6050_Read_Data(Struct_MPU6050* mpu6050)
{ 
  /*Read 6-axis data from MPU6050*/
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU6050_ADDR,14,true);  // request a total of 14 registers

  mpu6050->acc_x_raw = Wire.read()<<8|Wire.read();   
  mpu6050->acc_y_raw = Wire.read()<<8|Wire.read();  
  mpu6050->acc_z_raw = Wire.read()<<8|Wire.read();  
  
  mpu6050->temperature_raw = Wire.read()<<8|Wire.read();  
  
  mpu6050->gyro_x_raw = Wire.read()<<8|Wire.read();  
  mpu6050->gyro_y_raw = Wire.read()<<8|Wire.read();  
  mpu6050->gyro_z_raw = Wire.read()<<8|Wire.read();  
}

void MPU6050_Convert_Data(Struct_MPU6050* mpu6050)
{ 
  static float LSB_Sensitivity_ACC = 16384.f;
  static float LSB_Sensitivity_GYRO = 131.f;
  
  mpu6050->acc_x = mpu6050->acc_x_raw / LSB_Sensitivity_ACC;
  mpu6050->acc_y = mpu6050->acc_y_raw / LSB_Sensitivity_ACC;
  mpu6050->acc_z = mpu6050->acc_z_raw / LSB_Sensitivity_ACC;
  
  mpu6050->gyro_x = mpu6050->gyro_x_raw / LSB_Sensitivity_GYRO;
  mpu6050->gyro_y = mpu6050->gyro_y_raw / LSB_Sensitivity_GYRO;
  mpu6050->gyro_z = mpu6050->gyro_z_raw / LSB_Sensitivity_GYRO; 
}
