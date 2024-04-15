int LeftSensor = A0;
int RightSensor = A1;
int L_sensor_val = 0; // To store value from sensors.
int R_sensor_val = 0;
int threshold = 500;
void setup() {
  Serial.begin(9600);
  pinMode(LeftSensor, INPUT);
  pinMode(RightSensor, INPUT);
}
void loop() {
L_sensor_val = analogRead(LeftSensor); 
R_sensor_val = analogRead(RightSensor); 
Serial.print(L_sensor_val);
Serial.print(" and ");
Serial.println(R_sensor_val);
delay(500);
}
