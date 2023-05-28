#include <Arduino.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "RF24_USER.h"
#include "JoyStick.h"
#include "PID_Control.h"
#include "EEPROM_USER.h"

typedef union _Parser
{
  uint8_t data[4];
  float float_data;
}Parser;


RF24 radio(7, 8);

void RF24_Rx_Init(void)
{
  const byte address_1[6] = "00001";
  radio.begin();
  radio.openReadingPipe(0, address_1); //link with joystick
  
//  const byte address_2[6] = "00GCS";
//  radio.openWritingPipe(address_2); // 데이터를 보낼 수신의 주소를 설정합니다.  RX_ADDR_P0 사용 for auto ack
//  radio.openReadingPipe(1, address_2); //link with GCS
  radio.setPALevel(RF24_PA_MAX); //전원공급에 관한 파워레벨을 설정합니다.
  radio.startListening(); //모듈을 수신기로 설정합니다.
  delay(1);
}


void RF24_Rx_Read(void)
{   
  static uint8_t buf[32];
  radio.read(buf, sizeof(buf));
//  for(int i = 0; i<32;i++)
//  {
//    Serial.print(buf[i],HEX); Serial.print(" ");
//  }
//  Serial.println();
  
  Serial.println("i got somthing");
    if(is_checksum_correct_joystick(buf))
    {
      LV = buf[0]<<8 | buf[1];
      LH = buf[2]<<8 | buf[3];
      RV = buf[4]<<8 | buf[5];
      RH = buf[6]<<8 | buf[7];
      Serial.println((String) LV + "\t" + LH + "\t" + RV + "\t" + RH);
    }

//  if(LV < 512)
//  {
//    if(buf[0] == 0x47 && buf[1] == 0x53) // message from GCS
//    { 
//      Serial.println("message from gcs");
//      if(is_checksum_correct_gcs(buf))
//      { 
//        Serial.println("checksum pass");
//        Parser parser;
//        float p,i,d;
//        p = *(float*)&buf[3];
//        i = *(float*)&buf[7];
//        d = *(float*)&buf[11];
//        Serial.println((String) p + "\t" + i + "\t" + d + "\t");
//        
//        uint8_t buf_tx[20];
//        switch(buf[2])
//        {
//          case 0:
//            EP_PID_Write(buf[2], p, i, d);
//            EP_PID_Read(buf[2], &roll.in.kp, &roll.in.ki, &roll.in.kd);
//            Encode_Msg_PID_Gain(&buf_tx[0], buf[2], roll.in.kp, roll.in.ki, roll.in.kd);
//            Serial.println((String) roll.in.kp + "\t" + roll.in.ki + "\t" + roll.in.kd + "\t");
//            RF24_Tx_Sequence(buf_tx, 20);
//            break;
//          case 1:
//            EP_PID_Write(buf[2], p, i, d);
//            EP_PID_Read(buf[2], &roll.out.kp, &roll.out.ki, &roll.out.kd);
//            Encode_Msg_PID_Gain(&buf_tx[0], buf[2], roll.out.kp, roll.out.ki, roll.out.kd);
//            RF24_Tx_Sequence(buf_tx, 20);
//            break;
//          case 2:
//            EP_PID_Write(buf[2], p, i, d);
//            EP_PID_Read(buf[2], &pitch.in.kp, &pitch.in.ki, &pitch.in.kd);
//            Encode_Msg_PID_Gain(&buf_tx[0], buf[2], pitch.in.kp, pitch.in.ki, pitch.in.kd);
//            RF24_Tx_Sequence(buf_tx, 20);
//            break;
//          case 3:
//            EP_PID_Write(buf[2], p, i, d);
//            EP_PID_Read(buf[2], &pitch.out.kp, &pitch.out.ki, &pitch.out.kd);
//            Encode_Msg_PID_Gain(&buf_tx[0], buf[2], pitch.out.kp, pitch.out.ki, pitch.out.kd);
//            RF24_Tx_Sequence(buf_tx, 20);
//            break;
//          case 4:
//            EP_PID_Write(buf[2], p, i, d);
//            EP_PID_Read(buf[2], &yaw_heading.kp, &yaw_heading.ki, &yaw_heading.kd);
//            Encode_Msg_PID_Gain(&buf_tx[0], buf[2], yaw_heading.kp, yaw_heading.ki, yaw_heading.kd);
//            RF24_Tx_Sequence(buf_tx, 20);
//            break;
//          case 5:
//            EP_PID_Write(buf[2], p, i, d);
//            EP_PID_Read(buf[2], &yaw_rate.kp, &yaw_rate.ki, &yaw_rate.kd);
//            Encode_Msg_PID_Gain(&buf_tx[0], buf[2], yaw_rate.kp, yaw_rate.ki, yaw_rate.kd);
//            RF24_Tx_Sequence(buf_tx, 20);
//            break;
//
//          case 0x20:
//            Encode_Msg_PID_Gain(&buf_tx[0], buf[2],p,i,d);
//            RF24_Tx_Sequence(buf_tx, 20);
//            break;
//          case 0x10:
//            switch(buf[3])
//              {
//                case 0:
//                  Encode_Msg_PID_Gain(&buf_tx[0], 0, roll.in.kp, roll.in.ki, roll.in.kd);
//                  break;
//                case 1:
//                  Encode_Msg_PID_Gain(&buf_tx[0], 1, roll.out.kp, roll.out.ki, roll.out.kd);
//                  break;
//                case 2:
//                  Encode_Msg_PID_Gain(&buf_tx[0], 2, pitch.in.kp, pitch.in.ki, pitch.in.kd);
//                  break;
//                case 3:
//                  Encode_Msg_PID_Gain(&buf_tx[0], 3, pitch.out.kp, pitch.out.ki, pitch.out.kd);
//                  break;
//                case 4:
//                  Encode_Msg_PID_Gain(&buf_tx[0], 4, yaw_heading.kp, yaw_heading.ki, yaw_heading.kd);
//                  break;
//                case 5:
//                  Encode_Msg_PID_Gain(&buf_tx[0], 5, yaw_rate.kp, yaw_rate.ki, yaw_rate.kd);
//                  break;
//                case 6:
////                  Encode_Msg_PID_Gain(&telemetry_tx_buf[0], 0, roll.in.kp, roll.in.ki, roll.in.kd);
////                  HAL_UART_Transmit(&huart1, &telemetry_tx_buf[0], 20, 10);
////                  Encode_Msg_PID_Gain(&telemetry_tx_buf[0], 1, roll.out.kp, roll.out.ki, roll.out.kd);
////                  HAL_UART_Transmit(&huart1, &telemetry_tx_buf[0], 20, 10);
////                  Encode_Msg_PID_Gain(&telemetry_tx_buf[0], 2, pitch.in.kp, pitch.in.ki, pitch.in.kd);
////                  HAL_UART_Transmit(&huart1, &telemetry_tx_buf[0], 20, 10);
////                  Encode_Msg_PID_Gain(&telemetry_tx_buf[0], 3, pitch.out.kp, pitch.out.ki, pitch.out.kd);
////                  HAL_UART_Transmit(&huart1, &telemetry_tx_buf[0], 20, 10);
////                  Encode_Msg_PID_Gain(&telemetry_tx_buf[0], 4, yaw_heading.kp, yaw_heading.ki, yaw_heading.kd);
////                  HAL_UART_Transmit(&huart1, &telemetry_tx_buf[0], 20, 10);
////                  Encode_Msg_PID_Gain(&telemetry_tx_buf[0], 5, yaw_rate.kp, yaw_rate.ki, yaw_rate.kd);
////                  HAL_UART_Transmit(&huart1, &telemetry_tx_buf[0], 20, 10);
//                  break;
//              }
//        }
//      }
//    }
//  }
}


//void RF24_Tx_Sequence(uint8_t* buf_tx, uint8_t len)
//{
//  radio.stopListening();  //모듈을 송신기로 설정합니다.
//  delay(1);
//    for(int i = 0; i<20;i++)
//  {
//    Serial.print(buf_tx[i],HEX); Serial.print(" ");
//  }
//  radio.write(&buf_tx, len); //보내기
//  radio.startListening(); //모듈을 수신기로 설정합니다.
//  delay(1);
//  Serial.println("Message transmitted");
//}



void Encode_Msg_PID_Gain(uint8_t* buf_tx, uint8_t id, float p, float i, float d)
{
  buf_tx[0] = 0x46;
  buf_tx[1] = 0x43;
  buf_tx[2] = id;
  *(float*)&buf_tx[3] = p;
  *(float*)&buf_tx[7] = i;
  *(float*)&buf_tx[11] = d;
  buf_tx[15] = 0x00;
  buf_tx[16] = 0x00;
  buf_tx[17] = 0x00;
  buf_tx[18] = 0x00;
  buf_tx[19] = 0xff;
  for(int i = 0; i<19; i++)
  {
    buf_tx[19] = buf_tx[19] - buf_tx[i];
  }
}




bool is_checksum_correct_joystick(uint8_t* buf)
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

bool is_checksum_correct_gcs(uint8_t* buf)
{
  uint8_t checksum = 0xFF;
  for(int i=0;i<19;i++)
  {
    checksum = checksum - buf[i];
  }

  if(checksum == buf[19])
  {
    return 1;
  }
  else
  {
    return 0;
  }
}
