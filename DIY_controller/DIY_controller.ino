
#include "JoyStick.h"


#include "nRF24L01.h"
#include "RF24.h"
#include "TxModule.h"
#include "Timer2.h"
#include "Interrupt.h"


void setup()
{
  Serial.begin(115200);
  Timer2_Init();
  JoyStick_Init();
  RF24_Tx_Init();
  
  pinMode(2, OUTPUT);
}

void loop()
{ 
  if(Timer2_10ms_flag == 1)
  { 
    digitalWrite(2, HIGH);
    Timer2_10ms_flag = 0;
    JoyStick_Read();
    RF24_Tx_Send(LV, LH, RV, RH, SwA); //해당 메시지를 수신자에게 보냅니다.
    
    digitalWrite(2,LOW);
  }

}
