#include <Wire.h>
#include "MPU6050.h"
#include "UART.h"
#include "Timer2.h"
#include "CalculateAngle.h"
#include "Interrupt.h"
#include "RxModule.h"
#include "JoyStick.h"
#include "PWM.h"

void setup() {
  /* Init Periperal */
  Wire.begin();                 // I2C Master mode init
  Serial.begin(115200);         // UART init
  Serial.println("hello world");

  Timer2_Init();
  
  /* Init Module */
  MPU6050_INIT();
  RF24_Rx_Init();

  attachInterrupt(digitalPinToInterrupt(2), RF24_Rx_Read, FALLING);
  PWM_Init();
}

void loop() {
  if(Timer2_2ms_flag == 1)
  {
    Timer2_2ms_flag = 0;
//    MPU6050_Read_Data(&mpu6050);
//    MPU6050_Convert_Data(&mpu6050);
//    CalculateCompliFilter(&Angle, &mpu6050);
//    print_3_float(Angle.ComFilt_roll, Angle.ComFilt_pitch, Angle.ComFilt_yaw);

    OCR0A = LV/4;
    OCR0B = LH/4;
    OCR1A = RV/4;
    OCR1B = RH/4;

    
  }
//  Serial.print(TIMSK0,HEX); Serial.print("\t"); Serial.println(TIFR0,HEX);
//  Serial.print(TIMSK0,BIN); Serial.print("\t"); Serial.println(TIFR0,BIN);
//  delay(100);

  
}
