#include <AFMotor.h>

AF_DCMotor motor1(1, MOTOR12_64KHZ);
AF_DCMotor motor2(2, MOTOR12_64KHZ);

void setup() {
}
void loop() {
motor1.setSpeed(150);
motor2.setSpeed(150);
// set the speed to 200/255
motor1.run(FORWARD);
motor2.run(FORWARD);
}
