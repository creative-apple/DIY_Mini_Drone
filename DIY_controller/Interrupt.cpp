#include <Arduino.h>

int Timer2_1ms_flag = 0;
int Timer2_2ms_flag = 0;
int Timer2_10ms_flag = 0;
int Timer2_100ms_flag = 0;
int Timer2_1000ms_flag = 0;

  
ISR(TIMER2_COMPA_vect)
{
  static int Timer2_1ms_count = 0;
  static int Timer2_2ms_count = 0;
  static int Timer2_10ms_count = 0;
  static int Timer2_100ms_count = 0;
  static int Timer2_1000ms_count = 0;

  Timer2_1ms_count += 1;
  Timer2_2ms_count += 1;
  Timer2_10ms_count += 1;
  Timer2_100ms_count += 1;
  Timer2_1000ms_count += 1;

  if(Timer2_1ms_count == 1)
  {
    Timer2_1ms_count = 0;
    Timer2_1ms_flag = 1;
  }

  if(Timer2_2ms_count == 2)
  {
    Timer2_2ms_count = 0;
    Timer2_2ms_flag = 1;
  }
  if(Timer2_10ms_count == 10)
  {
    Timer2_10ms_count = 0;
    Timer2_10ms_flag = 1;
  }
  if(Timer2_100ms_count == 100)
  {
    Timer2_100ms_count = 0;
    Timer2_100ms_flag = 1;
  }
  if(Timer2_1000ms_count == 1000)
  {
    Timer2_1000ms_count = 0;
    Timer2_1000ms_flag = 1;
  }
}
