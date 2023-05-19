#include <Arduino.h>
#include "nRF24L01.h"
#include "RF24.h"

RF24 radio(7, 8); 

void RF24_Tx_Init(void)
{
  const byte address[6] = "00001";
  radio.begin();
  radio.openWritingPipe(address); // 데이터를 보낼 수신의 주소를 설정합니다.
  radio.setPALevel(RF24_PA_MIN); // 전원공급에 관한 파워레벨을 설정합니다.
  radio.stopListening();  //모듈을 송신기로 설정합니다.
}


void RF24_Tx_Send(short LV, short LH, short RV, short RH)
{ 
  static uint8_t Tx_Payload[9];
  static uint8_t checksum;
  Tx_Payload[0] = LV >> 8;
  Tx_Payload[1] = LV & 0xFF;
  Tx_Payload[2] = LH >> 8;
  Tx_Payload[3] = LH & 0xFF;
  Tx_Payload[4] = RV >> 8;
  Tx_Payload[5] = RV & 0xFF;
  Tx_Payload[6] = RH >> 8;
  Tx_Payload[7] = RH & 0xFF;
  
  checksum = 0;
  for(int i = 0; i<8 ; i++)
  {
    checksum += Tx_Payload[i];
  }
  checksum = ~checksum + 1; //2의 보수 취하기
  
  Tx_Payload[8] = checksum;

  for(int i = 0;i<9;i++)
  {
    Serial.print(Tx_Payload[i],HEX);  Serial.print("\t");
  }
  Serial.println();
  radio.write(&Tx_Payload, sizeof(Tx_Payload)); //해당 메시지를 수신자에게 보냅니다.
}
