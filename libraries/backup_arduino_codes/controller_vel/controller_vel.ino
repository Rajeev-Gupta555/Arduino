#include <ros.h>
#include <geometry_msgs/Twist.h>
#define msg_type geometry_msgs::Twist
#define dirPort1 12
#define speedPort1 11
#define dirPort2 4
#define speedPort2 10
#define dirPort3 7
#define speedPort3 8

ros::NodeHandle nh;

char svx[5], svy[5], sw[5];
char log_msg1[99];

float angle, velocity, w = 0;
//float d = 0.2;
float vx, vy;
float m1 = 0, m2 = 0, m3 = 0;
class Motor
{
public:
    int speedPort, dirPort, abm=0;
    Motor(int speedPortx, int dirPortx)
    {
        speedPort = speedPortx;
        dirPort = dirPortx;
    }

    void moveit(float m)
    {
        abm = abs(m);
        if (abm < 50 && abm > 5){
          abm = 50;
        }
        if (abm <=5){
          abm = 0;
        }
        analogWrite(speedPort, abm);
        if (m < 0)
        {
            digitalWrite(dirPort, HIGH);
        }
        if (m > 0)
        {
            digitalWrite(dirPort, LOW);
        }
    }
};

Motor motor1(11, 12), motor2(10, 4), motor3(8, 7);

void omini_cb(const msg_type &cmd_msg)
{
    digitalWrite(13, HIGH - digitalRead(13));
//    vx = cmd_msg.data[0];
//    vy = cmd_msg.data[1];
//    w = cmd_msg.data[2];
//    vx = cmd_msg.linear.x;
//    vy = cmd_msg.linear.y;
//    w = cmd_msg.angular.z;

//    m1 = -w - vy;
//    m2 = -w + vy + vx;
//    m3 = -w + vy - vx;
    m1 = cmd_msg.linear.x;
    m2 = cmd_msg.linear.y;
    m3 = cmd_msg.linear.z;
    motor1.moveit(m1);
    motor2.moveit(m2);
    motor3.moveit(m3);
    
    dtostrf(vx, 2, 2, svx);
    dtostrf(vy, 2, 2, svy);
    dtostrf(w , 2, 2, sw);
    sprintf(log_msg1, "velocity input: %s, %s, %s", svx, svy, sw);
    nh.loginfo(log_msg1);

}
//Defining subscriber 
ros::Subscriber<msg_type> sub("rasp_to_omni_chatter", omini_cb);


void setup()
{
    if(1){
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
        nh.loginfo("session started");
    }
    else{
      nh.loginfo("ERROR: session not started");
      }
}

void loop()
{
    if(1){
        nh.spinOnce();
    }
    else{
        analogWrite(speedPort1, 0);
        analogWrite(speedPort2, 0);
        analogWrite(speedPort3, 0);
    }
}
