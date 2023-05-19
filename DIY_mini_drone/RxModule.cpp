#include <Arduino.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "RxModule.h"
#include "JoyStick.h"


RF24 radio(7, 8);

void RF24_Rx_Init(void)
{
  const byte address[6] = "00001";
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN); //전원공급에 관한 파워레벨을 설정합니다.
  radio.startListening(); //모듈을 수신기로 설정합니다.
}


void RF24_Rx_Read(void)
{   
  static uint8_t buf[32];
  if (radio.available())
  {
    radio.read(buf, sizeof(buf));

    if(is_checksum_correct(buf))
    { 
      LV = buf[0]<<8 | buf[1];
      LH = buf[2]<<8 | buf[3];
      RV = buf[4]<<8 | buf[5];
      RH = buf[6]<<8 | buf[7];
      Serial.println((String) LV + "\t" + LH + "\t" + RV + "\t" + RH);
    }
  }
}

bool is_checksum_correct(uint8_t* buf)
{
  uint8_t checksum = 0;
  for(int i=0;i<9;i++)
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
