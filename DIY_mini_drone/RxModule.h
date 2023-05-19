#ifndef __RXMODULE_H
#define __RXMODULE_H

#include "RF24.h"

extern RF24 radio;

void RF24_Rx_Init(void);
void RF24_Rx_Read(void);
bool is_checksum_correct(uint8_t* buf);

#endif
