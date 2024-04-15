#define pwm 7 
#define dir A0 

const float kp = 2.5 ;
const float kd = 1 ; 
const float ki = 0.01 ; 

float prev_error = 0 ;
float derivative = 0 ;
float output = 0 ; 
volatile long temp,counter = 0  ; 

void ai0 (){
  if(digitalRead(3) == LOW){
    counter++ ; 
  }
  else{
    counter-- ;
  }
}
void ai1 (){
  if(digitalRead(2) == LOW){
    counter-- ; 
  }
  else{
    counter++ ;
  }
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600) ;
  pinMode(pwm,OUTPUT) ;
  pinMode(dir,OUTPUT) ;

  pinMode(2, INPUT_PULLUP); // internal pullup input pin 2 
  pinMode(3, INPUT_PULLUP); // internalเป็น pullup input pin 3
  attachInterrupt(0, ai0, RISING);
  attachInterrupt(1, ai1, RISING); 
}

void loop() {
  float angle = (counter)*360/1200 ; 
  if( counter != temp){
  Serial.println (angle);
  temp = counter;
  }
  float serror = 0 ; 
  float dcounter = 500 ; 
  int currentPos = counter ; 
  float error = dcounter - currentPos ;
  serror = error + serror ; 
  derivative = error - prev_error ; 
  output = (kp * error) + (kd * derivative) + (ki * serror)  ;
  // put your main code here, to run repeatedly:
  prev_error = error ; 
  delay(10) ; 
}

 void adjustMotorSpeed(float speed) {
  // Motor control code (adjust this based on your motor driver or H-bridge setup)
  // Example: For a simple H-bridge, use analogWrite to control motor speed
  // For direction control, use digitalWrite to set motor direction pins

  // Example code (modify based on your motor setup)
  if (speed > 0) {
    digitalWrite(dir, HIGH); // Set motor direction
    analogWrite(pwm, speed); // Set motor speed using PWM
  } else if (speed < 0) {
    digitalWrite(dir, LOW); // Set motor direction (opposite direction)
    analogWrite(pwm, -speed); // Set motor speed using PWM (positive value)
  } else {
    analogWrite(pwm, 0); // Stop the motor if speed is 0
  }
  }
