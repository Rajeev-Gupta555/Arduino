const int analogPin = A0; // Analog input pin

void setup() {
  Serial.begin(9600); // Initialize serial communication
}

void loop() {
  int sensorValue = analogRead(analogPin); // Read the analog input
  float voltage = sensorValue * (5.0 / 1023.0); // Convert to voltage (assuming 5V reference)
  
  Serial.print("Analog Input Value: ");
  Serial.print(sensorValue);
  Serial.print("\tVoltage: ");
  Serial.print(voltage, 8); // Print voltage with 2 decimal places
  Serial.println(" V");

  delay(100); // Optional delay to make the output readable
}
