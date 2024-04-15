#include <ros.h>
#include <geometry_msgs/Point.h>
#define msg_type geometry_msgs::Point
//#include <std_msgs/Float32MultiArray.h>
//#define msg_type std_msgs::Float32MultiArray

//#include <MPU9250.h>                //for gyro
//MPU9250 mpu;                        //for gyro
//#include <Wire.h>

ros::NodeHandle nh;
msg_type posn, last_posn;

ros::Publisher pub("omni_to_rasp_chatter", &posn);

//char sx[5], sy[5], log_msg[99];
  
int encPin[4] = {35, 3, 33, 2};           //for mega
//int encPin[4] = {13, 3, 12, 2};           //for uno
volatile long long counterx = 0, countery = 0;
const double pi = 3.1415926535897932384626433832795;
//pi = 3.1415926535897932384626433832795
void enc_read()
{
  posn.x = counterx * 5.8 * pi / 600.0;
  posn.y = countery * 5.8 * pi / 600.0;
 }

void ai0()
{
  if (digitalRead(encPin[0]) == HIGH)
    counterx++;
  else
    counterx--;
}
void ai1()
{
  if (digitalRead(encPin[2]) == LOW)
    countery++; 
  else
    countery--;
}
void setup()
{
//  Wire.begin();
  nh.initNode();
  nh.advertise(pub);
  for (int i = 0; i < 4; i++)
    pinMode(encPin[i], INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(encPin[1]), ai0, RISING);
  attachInterrupt(digitalPinToInterrupt(encPin[3]), ai1, RISING);
  posn.x=0; posn.y=0; posn.z=0;
  last_posn.x=0; last_posn.y=0; last_posn.z=0;
  
}

void loop()
{
//  if(nh.connected()){
    enc_read();
//    if (mpu.update()) {
//          static uint32_t prev_ms = millis();
//          if (millis() > prev_ms + 25) {
//              prev_ms = millis();
//          }
//      }
//    posn.z = mpu.getYaw();
    pub.publish( &posn );
    nh.spinOnce();
    delay(10);
  //if (posn.x!=last_posn.x && posn.y!=last_posn.y){ 
  //    last_posn = posn;
  //    dtostrf(posn.x, 2, 2, sx);
  //    dtostrf(posn.y, 2, 2, sy);
  //    sprintf(log_msg, "current posn: x=%s, y=%s", sx, sy);
  //    nh.loginfo(log_msg);
  //  }
//  }
//  else{
//  // posn.x=0; posn.y=0; posn.z=0;
//  // pub.publish( &posn );
//  nh.loginfo("rosserial disconnected ...");
//  }
}
