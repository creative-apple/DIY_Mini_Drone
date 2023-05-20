#include <Arduino.h>

short LV;
short LH;
short RV;
short RH;

void JoyStick_Read(void)
{
  LV = 1023-analogRead(A0);
  LH = 1023-analogRead(A1);
  RV = 1023-analogRead(A2);
  RH = 1023-analogRead(A3);  
}
