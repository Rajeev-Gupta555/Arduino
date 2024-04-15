#include <AccelStepper.h>

// Define a stepper and the pins it will use
AccelStepper stepper; // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5
void setup()
{  
  Serial.begin(9600);
  // Change these to suit your stepper if you want
  stepper.setMaxSpeed(2000);
  stepper.setAcceleration(1000);
}
int desired_posn = 4;

void loop()
{
//  if (Serial.available() > 0) {
//    desired_posn = Serial.read();
//    Serial.println(desired_posn);
    stepper.moveTo(2000);
    while(stepper.distanceToGo() == 0){
    stepper.run();
    }
    delay(1000);
    Serial.flush();
//  }
//  else Serial.println("Data not available");
}
