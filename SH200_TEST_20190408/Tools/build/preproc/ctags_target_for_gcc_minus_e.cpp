# 1 "D:\\Faynman\\Desktop\\test\\test\\test.ino"
# 1 "D:\\Faynman\\Desktop\\test\\test\\test.ino"
# 2 "D:\\Faynman\\Desktop\\test\\test\\test.ino" 2

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
