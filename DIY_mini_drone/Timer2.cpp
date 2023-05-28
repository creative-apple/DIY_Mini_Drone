
#include <Arduino.h>


void Timer2_Init(void)
{
  noInterrupts(); // 전역 인터럽트를 비활성화
  TCCR2A = 1<<WGM21; //CTC mode
  TCCR2B = (1<<CS22); //prescaler = 64
  OCR2A = 249;
  TIMSK2 = 1<<OCIE2A; //Interrupt enable
  interrupts(); // 전역 인터럽트 활성화
}
