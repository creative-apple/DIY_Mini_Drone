
#include <Arduino.h>
#include <EEPROM.h>

#include "EEPROM_USER.h"

typedef union _Parser
{
  uint8_t data[4];
  float float_data;
}Parser;

void EP_PID_Write(uint8_t id, float p, float i, float d)
{ 

  uint8_t buf[16];
  Parser parser;
  
  buf[0] = 0x45;
  buf[1] = 0x50;
  buf[2] = id;
  
  parser.float_data = p;
  buf[3] = parser.data[0];
  buf[4] = parser.data[1];
  buf[5] = parser.data[2];
  buf[6] = parser.data[3];
  
  parser.float_data = i;
  buf[7] = parser.data[0];
  buf[8] = parser.data[1];
  buf[9] = parser.data[2];
  buf[10] = parser.data[3];

  parser.float_data = d;
  buf[11] = parser.data[0];
  buf[12] = parser.data[1];
  buf[13] = parser.data[2];
  buf[14] = parser.data[3];
  
  uint8_t checksum = 0;
  for(int i=0;i<15;i++)
  {
    checksum += buf[i];
  }
  checksum = ~checksum + 1; //2's complement
  buf[15] = checksum;


  /* Save data onto EEPROM */
  unsigned int start = id * 16;
  for(int i=0;i<16;i++)
  {
    EEPROM.write(start + i, buf[i]);
  }
}

void EP_PID_Read(uint8_t id, float* p, float* i, float* d)
{
  uint8_t buf[16];
  Parser parser;
  unsigned int start = id * 16;
  for(int i=0;i<16;i++)
  {
    buf[i] = EEPROM.read(start + i);
  }
  /* verify checksum */
  uint8_t checksum = 0;
  for(int i=0;i<16;i++)
  {
    checksum += buf[i];
  }

  if(checksum != 0)
  {
    while(1)
    {
      Serial.println("PID EEPROM READ ERROR!!");
    }
  }

  if(buf[0] == 0x45 && buf[1] == 0x50 && checksum == 0)
  {
    parser.data[0] = buf[3];
    parser.data[1] = buf[4];
    parser.data[2] = buf[5];
    parser.data[3] = buf[6];
    *p = parser.float_data;
    
    parser.data[0] = buf[7];
    parser.data[1] = buf[8];
    parser.data[2] = buf[9];
    parser.data[3] = buf[10];
    *i = parser.float_data;
    
    parser.data[0] = buf[11];
    parser.data[1] = buf[12];
    parser.data[2] = buf[13];
    parser.data[3] = buf[14]; 
    *d = parser.float_data;
  }
  delay(500);
}
