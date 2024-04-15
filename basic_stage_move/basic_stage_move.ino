#include <AccelStepper.h>

#define dirPin 2
#define stepPin 3
#define motorInterfaceType 1

// Create a new instance of the AccelStepper class:
AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);

void setup()
{  
  // Change these to suit your stepper if you want
  stepper.setMaxSpeed(1000);
  stepper.setAcceleration(500);
  int steps = 400;
  int mm = 2;
  stepper.moveTo(steps*mm);
}

void loop()
{
    // If at the end of travel go to the other end
    stepper.run();
}
