#include <Arduino.h>

short LV;
short LH;
short RV;
short RH;
short SwA;

void JoyStick_Init(void)
{
  pinMode(A4, INPUT_PULLUP);
}

void JoyStick_Read(void)
{
  LV = 1023-analogRead(A0);
  LH = 1023-analogRead(A1);
  RV = 1023-analogRead(A2);
  RH = 1023-analogRead(A3);  
  SwA = digitalRead(A4);
}
