#include <Arduino.h>
#include "nRF24L01.h"
#include "RF24.h"


RF24 radio(7, 8); 

void RF24_GCS_TO_FC_Init(void)
{
  const byte address[6] = "00GCS";
  radio.begin();
  radio.openWritingPipe(address); // 데이터를 보낼 수신의 주소를 설정합니다.
  radio.openReadingPipe(1, address); //link with GCS
  radio.setPALevel(RF24_PA_MAX); // 전원공급에 관한 파워레벨을 설정합니다.
  radio.stopListening();  //모듈을 송신기로 설정합니다.
  delay(1);
}

uint8_t send_back_cplt_flag = 0;
void RF24_Rx_Sequence(void)
{
  radio.startListening(); //모듈을 수신기로 설정합니다.
  Serial.println("turn into receiver ");
  Serial.println(send_back_cplt_flag);
  unsigned long times = micros();
  while(send_back_cplt_flag == 0 && (micros()-times < 10000))
  {
    Serial.println("im suck");
  }
  Serial.println(send_back_cplt_flag);
  

  radio.stopListening();  //모듈을 송신기로 설정합니다.
}

void RF24_Rx_Read(void)
{ 
  Serial.println("RF24_Rx_Read working");
  static uint8_t buf[32];
  radio.read(buf, sizeof(buf));
  Serial.write(buf,20);
  
  if(buf[0] == 0x46 && buf[1] == 0x43)
  {
    send_back_cplt_flag = 1;
  }
  
}
