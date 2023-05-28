#ifndef __RF24_USER_H
#define __RF24_USER_H

#include "RF24.h"



extern RF24 radio;

void RF24_Rx_Init(void);
void RF24_Rx_Read(void);
bool is_checksum_correct_joystick(uint8_t* buf);
bool is_checksum_correct_gcs(uint8_t* buf);
void Encode_Msg_PID_Gain(uint8_t* buf_tx, uint8_t id, float p, float i, float d);
void RF24_Tx_Sequence(uint8_t* buf_tx, uint8_t len);
#endif
