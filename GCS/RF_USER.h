#ifndef __RF_USER_H
#define __RF_USER_H


extern RF24 radio;
extern uint8_t send_back_cplt_flag;


void RF24_GCS_TO_FC_Init(void);
void RF24_Rx_Sequence(void);
void RF24_Rx_Read(void);

#endif
