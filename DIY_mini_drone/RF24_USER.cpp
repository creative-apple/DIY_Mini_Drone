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
  delay(1);
}


void RF24_Rx_Read(void)
{   
  static uint8_t buf[32];
  radio.read(buf, sizeof(buf));
  
    if(is_checksum_correct_joystick(buf))
    {
      LV = buf[0]<<8 | buf[1];
      LH = buf[2]<<8 | buf[3];
      RV = buf[4]<<8 | buf[5];
      RH = buf[6]<<8 | buf[7];
      SwA = buf[8]<<8 | buf[9];
      Serial.println((String) LV + "\t" + LH + "\t" + RV + "\t" + RH + "\t" + SwA);
    }
}


bool is_checksum_correct_joystick(uint8_t* buf)
{
  uint8_t checksum = 0;
  for(int i=0;i<11;i++)
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
