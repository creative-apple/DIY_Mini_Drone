#include <Arduino.h>

uint16_t LV;

uint8_t LL; //yaw
uint8_t LR;

uint8_t RL; //roll
uint8_t RR;
uint8_t RU; //pitch
uint8_t RD;

uint8_t SwA;


//Prev declare
uint16_t LV_Prev;

uint8_t LL_Prev; //yaw
uint8_t LR_Prev;

uint8_t RL_Prev; //roll
uint8_t RR_Prev;
uint8_t RU_Prev; //pitch
uint8_t RD_Prev;

uint8_t SwA_Prev;

//Reflect joystick
void Reflect_JoyStick(float* roll_target, float* pitch_target, float* yaw_target)
{
  if(LL == 1 && LL_Prev == 0)
  {
    *yaw_target -= 2.5f;
  }
  if(LR == 1 && LR_Prev == 0)
  {
    *yaw_target += 2.5f;
  }
  if(RL == 1 && RL_Prev == 0)
  {
    *roll_target -= 1;
  }
  if(RR == 1 && RR_Prev == 0)
  {
    *roll_target += 1;
  }
  if(RU == 1 && RU_Prev == 0)
  {
    *pitch_target += 1;
  }
  if(RD == 1 && RD_Prev == 0)
  {
    *pitch_target -= 1;
  }
  LL_Prev = LL;
  LR_Prev = LR;
  RL_Prev = RL;
  RR_Prev = RR;
  RU_Prev = RU;
  RD_Prev = RD;

  
  
}
