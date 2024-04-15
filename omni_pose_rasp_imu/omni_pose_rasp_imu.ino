#include <ros.h>
#include <geometry_msgs/Point.h>
#define msg_type geometry_msgs::Point
//#include <MPU9250.h> 
//MPU9250 mpu;         

ros::NodeHandle nh;
msg_type posn, last_posn;

ros::Publisher pub("omni_to_rasp_chatter", &posn);

int encPin[4] = {35, 3, 33, 2}; // for mega
volatile long long counterx = 0, countery = 0;
const double pi = 3.14159265358979;
char sx[5], sy[5], st[5], log_msg[100];
void enc_read()
{
  posn.x = counterx * 0.058 * pi / 600.0;
  posn.y = countery * 0.058 * pi / 600.0;
}

void ai0()
{
  if (digitalRead(encPin[0]) == HIGH)
    countery++;
  else
    countery--;
}
void ai1()
{
  if (digitalRead(encPin[2]) == LOW)
    counterx++;
  else
    counterx--;
}
void setup()
{
//  Wire.begin();
  nh.initNode();
  delay(2000);
  nh.advertise(pub);
  for (int i = 0; i < 4; i++)
    pinMode(encPin[i], INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(encPin[1]), ai0, RISING);
  attachInterrupt(digitalPinToInterrupt(encPin[3]), ai1, RISING);
  posn.x = 0;
  posn.y = 0;
  posn.z = 0;
//  while (!mpu.setup(0x68))
//  {
//    nh.loginfo("MPU connection failed. Please check your connection with `connection_check` example.");
//    delay(5000);
//  }
  nh.loginfo("Accel Gyro calibration will start in 5sec.");
  nh.loginfo("Please leave the device still on the flat plane.");
//  delay(5000);
//  mpu.calibrateAccelGyro();
  nh.loginfo("Mag calibration will start in 5sec.");
  nh.loginfo("Please Wave device in a figure eight until done.");
  delay(5000);
//  mpu.calibrateMag();
  nh.loginfo("Calibration Done, wait for few seconds...");
//  mpu.verbose(false);
}

void loop()
{
//  mpu.update();
  enc_read();
//  posn.z = mpu.getYaw();
  pub.publish(&posn);
  nh.spinOnce();
  delay(20);
}
