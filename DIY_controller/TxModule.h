#ifndef __TXMODULE_H
#define __TXMODULE_H


extern RF24 radio;

void RF24_Tx_Init(void);
void RF24_Tx_Send(short LV, short LH, short RV, short RH);

#endif
