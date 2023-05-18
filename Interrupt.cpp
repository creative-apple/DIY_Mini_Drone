#include <Arduino.h>

int Timer1_1ms_flag = 0;
int Timer1_2ms_flag = 0;
int Timer1_10ms_flag = 0;
int Timer1_100ms_flag = 0;
int Timer1_1000ms_flag = 0;

  
ISR(TIMER1_COMPA_vect)
{
  static int Timer1_1ms_count = 0;
  static int Timer1_2ms_count = 0;
  static int Timer1_10ms_count = 0;
  static int Timer1_100ms_count = 0;
  static int Timer1_1000ms_count = 0;

  Timer1_1ms_count += 1;
  Timer1_2ms_count += 1;
  Timer1_10ms_count += 1;
  Timer1_100ms_count += 1;
  Timer1_1000ms_count += 1;

  if(Timer1_1ms_count == 1)
  {
    Timer1_1ms_count = 0;
    Timer1_1ms_flag = 1;
  }

  if(Timer1_2ms_count == 2)
  {
    Timer1_2ms_count = 0;
    Timer1_2ms_flag = 1;
  }
  if(Timer1_10ms_count == 10)
  {
    Timer1_10ms_count = 0;
    Timer1_10ms_flag = 1;
  }
  if(Timer1_100ms_count == 100)
  {
    Timer1_100ms_count = 0;
    Timer1_100ms_flag = 1;
  }
  if(Timer1_1000ms_count == 1000)
  {
    Timer1_1000ms_count = 0;
    Timer1_1000ms_flag = 1;
  }
}
