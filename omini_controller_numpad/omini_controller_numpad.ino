// omini controll

#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
#endif

#include <ros.h>
#include <std_msgs/Int16MultiArray.h>
#define dirPort1 12
#define speedPort1 11
#define dirPort2 4
#define speedPort2 10
#define dirPort3 7
#define speedPort3 9
ros::NodeHandle  nh;
int default_speed, to_move;
float angle, time_to_run1;
void omini_cb( const std_msgs::Int16MultiArray cmd_msg){
  digitalWrite(13, HIGH-digitalRead(13));
  default_speed = 100;
  to_move = cmd_msg.data[0]; // angle in degrees
  if(to_move==5){
      angle=cmd_msg.data[1]*3.14159/180;
      time_to_run1 = 2*angle/1.3227so;;    //at speed of 100
    if (angle<0){
    digitalWrite(dirPort1, LOW);
    digitalWrite(dirPort2, LOW);
    digitalWrite(dirPort3, LOW);
    }
    if (angle>0){
      digitalWrite(dirPort1, HIGH);
      digitalWrite(dirPort2, HIGH);
      digitalWrite(dirPort3, HIGH);
      
    }
    analogWrite(speedPort1, 100);
    analogWrite(speedPort2, 100);
    analogWrite(speedPort3, 100);
    delay(time_to_run1);
    analogWrite(speedPort1, 0);
    analogWrite(speedPort2, 0);
    analogWrite(speedPort3, 0);
  
  }
  if (cmd_msg.data[1] != 0){
    default_speed = cmd_msg.data[1];
  }
  if (to_move == 8){
    analogWrite(speedPort1, 0);
    digitalWrite(dirPort2, LOW);
    analogWrite(speedPort2, default_speed);
    digitalWrite(dirPort3, HIGH);
    analogWrite(speedPort3, default_speed);
  }
  if (to_move == 2){
    analogWrite(speedPort1, 0);
    digitalWrite(dirPort2, HIGH);
    analogWrite(speedPort2, default_speed);
    digitalWrite(dirPort3, LOW);
    analogWrite(speedPort3, default_speed);
  }

  if(to_move==6){
    digitalWrite(dirPort1, HIGH);
    digitalWrite(dirPort2, LOW);
    digitalWrite(dirPort3, LOW);
    analogWrite(speedPort1, 2*default_speed);
    analogWrite(speedPort2, default_speed);
    analogWrite(speedPort3, default_speed);
  }
  if(to_move==4){
    digitalWrite(dirPort1, LOW);
    digitalWrite(dirPort2, HIGH);
    digitalWrite(dirPort3, HIGH);
    analogWrite(speedPort1, 2.3*default_speed);
    analogWrite(speedPort2, default_speed);
    analogWrite(speedPort3, default_speed);
  }
  
  
}

ros::Subscriber<std_msgs::Int16MultiArray> sub("rasp_to_omini_chatter", omini_cb);

void setup(){
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(dirPort1, OUTPUT);
  pinMode(speedPort1, OUTPUT);
  pinMode(dirPort2, OUTPUT);
  pinMode(speedPort2, OUTPUT);
  pinMode(dirPort3, OUTPUT);
  pinMode(speedPort3, OUTPUT);
  analogWrite(speedPort1, 0);
  analogWrite(speedPort2, 0);
  analogWrite(speedPort3, 0);
  nh.initNode();
  nh.subscribe(sub);
 }

void loop(){
  nh.spinOnce();
  delay(1);
}
