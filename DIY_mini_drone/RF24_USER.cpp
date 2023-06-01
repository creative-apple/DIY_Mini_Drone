#include <Arduino.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "RF24_USER.h"
#include "JoyStick.h"
#include "PID_Control.h"



RF24 radio(7, 8);

void RF24_Rx_Init(void)
{
  const byte address_1[6] = "00001";
  radio.begin();
  radio.openReadingPipe(0, address_1); //link with joystick
  radio.setPALevel(RF24_PA_MAX); //전원공급에 관한 파워레벨을 설정합니다.
  radio.startListening(); //모듈을 수신기로 설정합니다.

  attachInterrupt(digitalPinToInterrupt(2), RF24_Rx_Read, FALLING);
  delay(1);
}

void RF24_Rx_Read(void)
{   
  static uint8_t buf[32];
  radio.read(buf, sizeof(buf));
  
    if(is_checksum_correct_joystick(buf))
    { 
      LV = buf[0]<<8 | buf[1];

      LL = buf[2];
      LR = buf[3];
      
      RL = buf[4];
      RR = buf[5];
      RU = buf[6];
      RD = buf[7];
      
      SwA = buf[8];
      
//      Serial.println((String)LV + " " + LL + " " + LR + " " + RL + " " + RR + " " + RU + " " + RD + " " + SwA);
    }
}


bool is_checksum_correct_joystick(uint8_t* buf)
{
  uint8_t checksum = 0;
  for(int i=0;i<10;i++)
  {
    checksum += buf[i];
  }

  if(checksum == 0)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}
