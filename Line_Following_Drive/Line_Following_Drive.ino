#include <AFMotor.h>

AF_DCMotor motor1(1, MOTOR12_64KHZ);
AF_DCMotor motor2(2, MOTOR12_64KHZ);
// declaring Sensor Pins.
int LeftSensor = A0;
int RightSensor = A1;
int L_sensor_val = 0; // To store value from sensors.
int R_sensor_val = 0;
int threshold = 500;
int motor_speed = 120;
void setup()
{
  Serial.begin(9600);
  pinMode(LeftSensor, INPUT);
  pinMode(RightSensor, INPUT);
}
void loop()
{
  motor1.setSpeed(motor_speed);
  motor2.setSpeed(motor_speed);
  L_sensor_val = analogRead(LeftSensor);
  R_sensor_val = analogRead(RightSensor); // Reading Right sensor data

  Serial.print(L_sensor_val);
  Serial.print(" and ");
  Serial.println(R_sensor_val);
  if (L_sensor_val > threshold && R_sensor_val > threshold)
  {
    motor1.run(FORWARD);
    motor2.run(FORWARD);
  }
  else if (L_sensor_val < threshold && R_sensor_val < threshold)
  {
    motor1.run(FORWARD);
    motor2.run(FORWARD);
  }
  else if (L_sensor_val > threshold)
  {
    motor1.run(BACKWARD);
    motor2.run(FORWARD);
  }
  else if (R_sensor_val > threshold)
  {
    motor1.run(FORWARD);
    motor2.run(BACKWARD);
  }
}
