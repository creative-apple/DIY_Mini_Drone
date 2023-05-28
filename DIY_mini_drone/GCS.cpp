#include <Arduino.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "GCS.h"



//RF24 radio_gcs(A0, A1);
//
//void RF24_GCS_Rx_Init(void)
//{
//  const byte address[6] = "22222";
//  radio_gcs.begin();
//  radio_gcs.openReadingPipe(0, address);
//  radio_gcs.setPALevel(RF24_PA_MAX); // 전원공급에 관한 파워레벨을 설정합니다.
//  radio_gcs.startListening(); //모듈을 수신기로 설정합니다.
//  delay(10);
//}
//
//
//
//void RF24_GCS_Rx_Read(void)
//{ 
//  static uint8_t buf[32];
//  radio_gcs.read(buf, sizeof(buf));
//  if(is_checksum_correct_1(buf) && buf[0] == 0x47 && buf[1] == 0x53)
//  { 
//    Parser parser;
//    float p,i,d;
//    parser.data[0] = buf[3];
//    parser.data[1] = buf[4];
//    parser.data[2] = buf[5];
//    parser.data[3] = buf[6];
//    p = parser.float_data;
//    
//    parser.data[0] = buf[7];
//    parser.data[1] = buf[8];
//    parser.data[2] = buf[9];
//    parser.data[3] = buf[10];
//    i = parser.float_data;
//    
//    parser.data[0] = buf[11];
//    parser.data[1] = buf[12];
//    parser.data[2] = buf[13];
//    parser.data[3] = buf[14]; 
//    d = parser.float_data;
//    
//    Serial.println((String) p + "\t" + i + "\t" + d + "\t");
//  }
//}
