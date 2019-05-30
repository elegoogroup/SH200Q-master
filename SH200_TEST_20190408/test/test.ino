#include "sh200q.h"

void setup()
{
  Serial.begin(115200);
  while (!Serial)
  {
  }

  sh200q_init();
}

void loop()
{
  sh200q_getADC();
  delay(100);
}
