#include <Arduino.h>
#line 1 "D:\\Faynman\\Desktop\\test\\test\\test.ino"
#line 1 "D:\\Faynman\\Desktop\\test\\test\\test.ino"
#include "sh200q.h"

#line 3 "D:\\Faynman\\Desktop\\test\\test\\test.ino"
void setup();
#line 13 "D:\\Faynman\\Desktop\\test\\test\\test.ino"
void loop();
#line 3 "D:\\Faynman\\Desktop\\test\\test\\test.ino"
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

