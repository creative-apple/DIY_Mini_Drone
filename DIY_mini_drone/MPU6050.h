#ifndef __MPU6050_H
#define __MPU6050_H


#define MPU6050_ADDR                  0x68

typedef struct _MPU6050{
  short acc_x_raw;
  short acc_y_raw;
  short acc_z_raw;
  short temperature_raw;
  short gyro_x_raw;
  short gyro_y_raw;
  short gyro_z_raw;

  float acc_x;
  float acc_y;
  float acc_z;
  float temperature;
  float gyro_x;
  float gyro_y;
  float gyro_z;
}Struct_MPU6050;

extern Struct_MPU6050 mpu6050;

void MPU6050_INIT(void);
void MPU6050_Read_Data(Struct_MPU6050* mpu6050);
void MPU6050_Convert_Data(Struct_MPU6050* mpu6050);
#endif
