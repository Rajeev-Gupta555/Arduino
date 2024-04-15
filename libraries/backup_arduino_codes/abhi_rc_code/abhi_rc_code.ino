#include <IBusBM.h>
#include <math.h>

IBusBM ibus;

int rcCH1 = 0;
int rcCH2 = 0;
int rcCH3 = 0;
int rcCH4 = 0;
int rcCH5 = 0;
int rcCH6 = 0;

int angle;
int speedf;
int angular_velocity, up_pwm, out_pwm;
float vx, vy, w;
float m1 = 0, m2 = 0, m3 = 0, ax, ay;
#define dirPort1 12
#define speedPort1 11
#define dirPort2 4
#define speedPort2 10
#define dirPort3 7
#define speedPort3 8

#define plateup_dir 3
#define plateup_pwm 5
#define plateout_dir 6
#define plateout_pwm 13
int readChannel(byte channelInput, int minLimit, int maxLimit, int defaultValue)
{
    uint16_t ch = ibus.readChannel(channelInput);
    if (ch < 900)
        return defaultValue;
    return map(ch, 1000, 2000, minLimit, maxLimit);
}
class Motor
{
public:
    int speedPort, dirPort, abm = 0;
    Motor(int speedPortx, int dirPortx)
    {
        speedPort = speedPortx;
        dirPort = dirPortx;
    }

    void moveit(float m)
    {
        abm = abs(m);
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

Motor motor1(11, 12), motor2(10, 4), motor3(8, 7), motorUP(plateup_pwm, plateup_dir), motorOUT(plateout_pwm, plateout_dir);
void omini_cb(int speedf, float ax, float ay, int angular_velocity)
{
    vx = speedf * ax / 1000;
    vy = speedf * ay / 1000;
    w = angular_velocity;

    m1 = -w + vx;
    m2 = -w - vx / 2 + vy * sqrt(3) / 2;
    m3 = -w - vx / 2 - vy * sqrt(3) / 2;

    motor1.moveit(m1);
    motor2.moveit(m2);
    motor3.moveit(m3);
}
int plate_rest_range = 80;
void plate_move(int up_pwm, int out_pwm)
{
    if (abs(up_pwm) < plate_rest_range)
    {
        motorUP.moveit(0);
    }
    if (abs(up_pwm) > plate_rest_range)
    {
        motorUP.moveit(up_pwm);
    }
    if (abs(out_pwm) < plate_rest_range)
    {
        motorOUT.moveit(0);
    }
    if (abs(out_pwm) > plate_rest_range)
    {
        motorOUT.moveit(out_pwm);
    }
      Serial.println(up_pwm);
      Serial.println(out_pwm);
}
void setup()
{
    ibus.begin(Serial1);
    Serial.begin(9600);
    pinMode(dirPort1, OUTPUT);
    pinMode(speedPort1, OUTPUT);
    pinMode(dirPort2, OUTPUT);
    pinMode(speedPort2, OUTPUT);
    pinMode(dirPort3, OUTPUT);
    pinMode(speedPort3, OUTPUT);

    pinMode(plateup_pwm, OUTPUT);
    pinMode(plateup_dir, OUTPUT);
    pinMode(plateout_pwm, OUTPUT);
    pinMode(plateout_dir, OUTPUT);

    analogWrite(speedPort1, 0);
    analogWrite(speedPort2, 0);
    analogWrite(speedPort3, 0);

    analogWrite(plateup_pwm, 0);
    analogWrite(plateout_pwm, 0);
}

void loop()
{
    rcCH1 = readChannel(0, -1000, 1000, 0);
    rcCH2 = readChannel(1, -1000, 1000, 0);
    rcCH3 = readChannel(2, 0, 255, 0);
    rcCH4 = readChannel(3, -100, 100, 0); // angular velocity
    rcCH5 = readChannel(4, -255, 255, 0);
    rcCH6 = readChannel(5, -255, 255, 0);

    speedf = rcCH3;
    ax = rcCH1;
    ay = rcCH2;
    angular_velocity = rcCH4;
    up_pwm = rcCH5;
    out_pwm = rcCH6;
    omini_cb(speedf, ax, ay, angular_velocity);
    plate_move(up_pwm, out_pwm);
    
//    Serial.println(ax);
//    Serial.println(ay);
//    Serial.println(speedf);
//    Serial.println(angular_velocity);
    Serial.println("\n\n");
    delay(250);
}
