#include <Arduino.h>

int Timer_1ms_flag = 0;
int Timer_2ms_flag = 0;
int Timer_10ms_flag = 0;
int Timer_100ms_flag = 0;
int Timer_1000ms_flag = 0;

  
ISR(TIMER1_COMPA_vect)
{
  static int Timer_1ms_count = 0;
  static int Timer_2ms_count = 0;
  static int Timer_10ms_count = 0;
  static int Timer_100ms_count = 0;
  static int Timer_1000ms_count = 0;

  Timer_1ms_count += 1;
  Timer_2ms_count += 1;
  Timer_10ms_count += 1;
  Timer_100ms_count += 1;
  Timer_1000ms_count += 1;

  if(Timer_1ms_count == 1)
  {
    Timer_1ms_count = 0;
    Timer_1ms_flag = 1;
  }

  if(Timer_2ms_count == 2)
  {
    Timer_2ms_count = 0;
    Timer_2ms_flag = 1;
  }
  if(Timer_10ms_count == 10)
  {
    Timer_10ms_count = 0;
    Timer_10ms_flag = 1;
  }
  if(Timer_100ms_count == 100)
  {
    Timer_100ms_count = 0;
    Timer_100ms_flag = 1;
  }
  if(Timer_1000ms_count == 1000)
  {
    Timer_1000ms_count = 0;
    Timer_1000ms_flag = 1;
  }
}
