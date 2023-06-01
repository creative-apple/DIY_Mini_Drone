#include <Arduino.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "JoyStick.h"

RF24 radio(7, 8); 

void RF24_Tx_Init(void)
{
  const byte address[6] = "00001";
  radio.begin();
  radio.openWritingPipe(address); // 데이터를 보낼 수신의 주소를 설정합니다.
  radio.setPALevel(RF24_PA_MAX); // 전원공급에 관한 파워레벨을 설정합니다.
  radio.stopListening();  //모듈을 송신기로 설정합니다.
  delay(1);
}

/*Send LV, LL, LR, RL, RR, RU, RD, SwA*/
void RF24_Tx_Send(void)
{ 
  static uint8_t Tx_Payload[10];
  static uint8_t checksum;
  Tx_Payload[0] = LV >> 8;
  Tx_Payload[1] = LV & 0xFF;
  Tx_Payload[2] = LL;
  Tx_Payload[3] = LR;
  Tx_Payload[4] = RL;
  Tx_Payload[5] = RR;
  Tx_Payload[6] = RU;
  Tx_Payload[7] = RD;
  Tx_Payload[8] = SwA;
  checksum = 0;
  for(int i = 0; i < sizeof(Tx_Payload)-1 ; i++)
  {
    checksum += Tx_Payload[i];
  }
  checksum = ~checksum + 1; //2의 보수 취하기
  uint8_t idx = sizeof(Tx_Payload)-1;
  Tx_Payload[idx] = checksum;

//  for(int i = 0; i<sizeof(Tx_Payload); i++)
//  {
//    Serial.print(Tx_Payload[i],HEX);  Serial.print("\t");
//  }
//  Serial.println();
  
  radio.write(&Tx_Payload, sizeof(Tx_Payload)); //해당 메시지를 수신자에게 보냅니다.
}
