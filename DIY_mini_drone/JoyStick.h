#ifndef __JOYSTICK_H
#define __JOYSTICK_H

extern uint16_t LV;

extern uint8_t LL;
extern uint8_t LR;

extern uint8_t RU;
extern uint8_t RD;
extern uint8_t RL;
extern uint8_t RR;

extern uint8_t SwA;

//Prev declare
extern uint16_t LV_Prev;

extern uint8_t LL_Prev; //yaw
extern uint8_t LR_Prev;

extern uint8_t RL_Prev; //roll
extern uint8_t RR_Prev;
extern uint8_t RU_Prev; //pitch
extern uint8_t RD_Prev;

extern uint8_t SwA_Prev;


void Reflect_JoyStick(float* roll_target, float* pitch_target, float* yaw_target);

#endif
