// omini controll

#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
#endif

#include <ros.h>
#include <std_msgs/UInt16.h>

ros::NodeHandle  nh;


void omini_cb( const std_msgs::UInt16& cmd_msg){
  int rosIN=cmd_msg.data; //value of input in 
  digitalWrite(13, HIGH-digitalRead(13));
  if (rosIN == 1){
    digitalWrite(9, HIGH);
  }
  else{
    digitalWrite(9, LOW);
  }
  //digitalWrite(13, LOW);
}

ros::Subscriber<std_msgs::UInt16> sub("omini", omini_cb);

void setup(){
  pinMode(13, OUTPUT);
  pinMode(9, OUTPUT);
  nh.initNode();
  nh.subscribe(sub);
 }

void loop(){
  nh.spinOnce();
  delay(10);
}
