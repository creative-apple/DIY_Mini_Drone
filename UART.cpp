#include <Arduino.h>

void print_3_float(float a, float b, float c)
{
  Serial.print(a);
  Serial.print("\t");
  Serial.print(b);
  Serial.print("\t");
  Serial.print(c);
  Serial.print("\n");
}

void print_3_int(int a, int b, int c)
{
  Serial.print(a);
  Serial.print("\t");
  Serial.print(b);
  Serial.print("\t");
  Serial.print(c);
  Serial.print("\n");
}
