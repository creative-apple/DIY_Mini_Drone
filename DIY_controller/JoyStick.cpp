#include <Arduino.h>

uint16_t LV;

uint8_t LL; //yaw
uint8_t LR;

uint8_t RL; //roll
uint8_t RR;
uint8_t RU; //pitch
uint8_t RD;

uint8_t SwA;



void JoyStick_Init(void)
{ 
  //LV doesn't need init
  pinMode(A1, INPUT_PULLUP); //LL
  pinMode(A2, INPUT_PULLUP); //LR

  pinMode(2, INPUT_PULLUP); //RL
  pinMode(3, INPUT_PULLUP); //RR
  pinMode(4, INPUT_PULLUP); //RU
  pinMode(5, INPUT_PULLUP); //RD
  
  pinMode(A4, INPUT_PULLUP); //SwA
}



void JoyStick_Read(void)
{
  LV = analogRead(A0);
  
  LL = digitalRead(A1);
  LR = digitalRead(A2);

  RL = digitalRead(2);
  RR = digitalRead(3);
  RU = digitalRead(4);
  RD = digitalRead(5);
  
  SwA = digitalRead(A4);
}
