
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
  RF24_Tx_Init();

}

void loop()
{ 
  if(Timer2_10ms_flag == 1)
  {
    Timer2_10ms_flag = 0;
    JoyStick_Read();
    RF24_Tx_Send(LV, LH, RV, RH); //해당 메시지를 수신자에게 보냅니다.
  }

}
