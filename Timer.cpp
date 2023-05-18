
#include <Arduino.h>


void Timer1_Init(void)
{
  noInterrupts(); // 전역 인터럽트를 비활성화
  TCCR1A = 0;
  TCCR1B = (1<<WGM12)|(1<<CS11)|(1<<CS10); //prescaler = 64
  OCR1A = 249;
  TIMSK1 = 1<<OCIE1A; //Interrupt enable
  interrupts(); // 전역 인터럽트 활성화
}
