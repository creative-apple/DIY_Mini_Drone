#include "nRF24L01.h"
#include "RF24.h"
#include "RF_USER.h"

uint8_t rx_cplt_flag = 0;
uint8_t buf[20];

void setup()
{
  Serial.begin(115200);
  RF24_GCS_TO_FC_Init();
  attachInterrupt(digitalPinToInterrupt(2), RF24_Rx_Read, FALLING);

  radio.startListening(); //모듈을 수신기로 설정합니다.
}

void loop()
{
  
  
  if(rx_cplt_flag == 1)
  {
    rx_cplt_flag = 0;
    for(int i=0;i<20;i++)
    {
      Serial.print(buf[i],HEX); Serial.print(" ");
    }
    Serial.println();
    radio.write(&buf, sizeof(buf)); //해당 메시지를 수신자에게 보냅니다.
    delay(1);
    RF24_Rx_Sequence(); //mode change
  }
//  char buff[] = "GS123456789123456789";
//  radio.write(&buff, sizeof(buff));
//  Serial.print("USE RF TO SEND:"); Serial.println(buff);
//  delay(1000);
}


void serialEvent()
{
  static uint8_t cnt = 0;
  uint8_t temp = Serial.read();
  
  switch(cnt)
  {
    case 0:
      if(temp == 0x47)
      {
        buf[cnt] = temp;
        cnt++;
      }
      else
      {
        cnt = 0;
      }
      break;
    case 1:
      if(temp == 0x53)
      {
        buf[cnt] = temp;
        cnt++;
      }
      else
      {
        cnt = 0;
      }
      break;
    case 19:
      buf[cnt] = temp;
      cnt = 0;
      rx_cplt_flag = 1;
      break;
    default:
      buf[cnt] = temp;
      cnt++;
      break;
  }
}
