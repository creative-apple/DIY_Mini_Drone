
#include "JoyStick.h"


#include "nRF24L01.h"
#include "RF24.h"
#include "TxModule.h"







void setup()
{
  Serial.begin(115200);

  RF24_Tx_Init();
}

void loop()
{ 
  JoyStick_Read();
  RF24_Tx_Send(LV, LH, RV, RH); //해당 메시지를 수신자에게 보냅니다.
  
  delay(50);

}
