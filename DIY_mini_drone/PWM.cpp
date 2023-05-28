#include <Arduino.h>


void PWM_Init(void)
{ 
  /*Timer0 Setting*/
  noInterrupts(); // 전역 인터럽트를 비활성화
  
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  TCCR0A = (1<<COM0A1)|(0<<COM0A0)|(1<<COM0B1)|(0<<COM0B0)|(1<<WGM01)|(1<<WGM00); //Activate OC0A, Activate OC0B, FAST PWM mode
  TCCR0B = (1<<CS01)|(1<<CS00); //prescaler = 64
  OCR0A = 50;
  OCR0B = 50;
//  TIMSK0 = 1<<TOIE0; //It is already reflected
//  TIFR0 = (1<<OCF0B)|(1<<OCF0A); //It is already reflected
  /*Timer1 Setting*/
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  TCCR1A = (1<<COM1A1)|(0<<COM1A0)|(1<<COM1B1)|(0<<COM1B0)|(0<<WGM11)|(1<<WGM10); //Activate OC0A, Activate OC0B, FAST PWM mode
  TCCR1B = (1<<WGM12)|(1<<CS01)|(1<<CS00); //prescaler = 64
  OCR1A = 50;
  OCR1B = 50;
  
  interrupts(); // 전역 인터럽트 활성화
}
