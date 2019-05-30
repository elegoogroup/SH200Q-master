# 1 "D:\\Faynman\\Desktop\\SH200_TEST_20190408_v2\\test\\test.ino"
# 1 "D:\\Faynman\\Desktop\\SH200_TEST_20190408_v2\\test\\test.ino"
# 2 "D:\\Faynman\\Desktop\\SH200_TEST_20190408_v2\\test\\test.ino" 2
# 3 "D:\\Faynman\\Desktop\\SH200_TEST_20190408_v2\\test\\test.ino" 2

KalmanFilter kalmanfilter;

int16_t ax, ay, az, gx, gy, gz;
float dt = 0.005, Q_angle = 0.001, Q_gyro = 0.005, R_angle = 0.5, C_0 = 1, K1 = 0.05;
unsigned long previous_time;
void setup()
{
  Serial.begin(256000);
  while (!Serial)
  {
  }

  sh200q_init();
}

void loop()
{
  previous_time = millis();

  sh200q_getADC();
  kalmanfilter.Angletest(acc[0], acc[1], acc[2], gyro[0], gyro[1], gyro[2], dt, Q_angle, Q_gyro, R_angle, C_0, K1);

  static unsigned long t;
  if (millis() - t > 100)
  {
    t = millis();
    Serial.println(kalmanfilter.angle);
  }

  Serial.println(millis() - previous_time);
}
