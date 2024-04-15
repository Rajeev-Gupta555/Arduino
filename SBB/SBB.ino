#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

#define PWMPIN 7
#define DIRPIN 8
Adafruit_BNO055 bno = Adafruit_BNO055(55);

class Bike
{
public:
  double bike_angular_velocity;
  double sample_rate;
  double tilt_angle_bike;
  double moi_flywheel;
  double k_bike;
  double moi_bike;
  double kp;
  double w_flywheel;
  double kd;
  Bike(double sample_rate)
  {
    bike_angular_velocity = 0.0;
    sample_rate = sample_rate;
    tilt_angle_bike = 0.0;
    moi_flywheel = 0.0075;
    k_bike = 10.6232;
    moi_bike = 1062;
    kp = 7;
    w_flywheel = 0;
    kd = 0.0001;
  }

  double balancing()
  {
    double dt = 1.0 / sample_rate;
    double w_bike = bike_angular_velocity;

    if (abs(tilt_angle_bike) > 0.001)
    {
      double torque = kp * tilt_angle_bike + kd * w_bike;
      double alpha = torque / moi_flywheel;
      w_flywheel += alpha * dt;
    }
    return w_flywheel;
  }
};

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
    if (abm < 50 && abm > 5)
    {
      abm = 50;
    }
    if (abm <= 5)
    {
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

int sample_rate = 100;
double angle = 0.0, prev_angle = 0.0, angular_vel = 0.0;
double pi = 3.14159265359;
double motor_ang_vel = 0.0;
double motor_pwm = 0, mf = 0.0;
double MOI_Reaction_Wheel = 0.0;
Motor reaction_wheel(PWMPIN, DIRPIN);
Bike sbb(sample_rate);

void setup(void)
{
  Serial.begin(9600);

  pinMode(PWMPIN, OUTPUT);
  pinMode(DIRPIN, OUTPUT);


    Serial.println("Orientation Sensor Test");
    Serial.println("");

  /* Initialise the sensor */
  if (!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while (1)
      ;
  }

  delay(1000);

  bno.setExtCrystalUse(true);
}

void loop(void)
{
  /* Get a new sensor event */
  sensors_event_t event;
  bno.getEvent(&event);

  angle = event.orientation.y;
  angle = angle*pi/180;
  angular_vel = (angle - prev_angle) / sample_rate;
  sbb.tilt_angle_bike = angle;
  sbb.bike_angular_velocity = angular_vel;
  motor_ang_vel = sbb.balancing();
  motor_pwm = omega_to_pwm(motor_ang_vel);
  

    Serial.print("angle: ");
    Serial.print(angle);
    Serial.print(", angular_vel: ");
    Serial.print(angular_vel);
    Serial.print(" ,  motor_ang_vel: ");
    Serial.print(motor_ang_vel);
    Serial.print(",  motor_pwm: ");
    Serial.print(motor_pwm);
    Serial.println("");

  reaction_wheel.moveit(motor_pwm);
  delay(sample_rate);
}

int omega_to_pwm(double motor_ang_vel)
{
  if (motor_ang_vel > 1)
    motor_ang_vel = 1;
  if (motor_ang_vel < 1)
    motor_ang_vel = -1;
  motor_ang_vel += 1;
  motor_ang_vel = motor_ang_vel * 255 / 2;
  return motor_ang_vel;
}
