#ifndef __EEPROM_USER_H
#define __EEPROM_USER_H



void EP_PID_Write(uint8_t id, float p, float i, float d);
void EP_PID_Read(uint8_t id, float* p, float* i, float* d);


#endif
