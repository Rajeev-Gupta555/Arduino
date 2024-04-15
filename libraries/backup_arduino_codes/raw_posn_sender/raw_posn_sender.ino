#include "MPU9250.h"

MPU9250 mpu;
double data[3]={0.0, 0.0, 0.0};

int encPin[4] = {35, 3, 33, 2}; // for mega
volatile long long counterx = 0, countery = 0;
const double pi = 3.14159265358979;
char sx[5], sy[5], st[5], log_msg[100];
void enc_read()
{
  data[0] = counterx * 0.058 * pi / 600.0;
  data[1] = countery * 0.058 * pi / 600.0;
}

void ai0()
{
  if (digitalRead(encPin[0]) == HIGH)
    countery++;
  else
    countery--;
}
void ai1()
{
  if (digitalRead(encPin[2]) == LOW)
    counterx++;
  else
    counterx--;
}
void setup() {
    Serial.begin(115200);
    Wire.begin();
    delay(2000);
    for (int i = 0; i < 4; i++)
        pinMode(encPin[i], INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(encPin[1]), ai0, RISING);
    attachInterrupt(digitalPinToInterrupt(encPin[3]), ai1, RISING);
    while (!mpu.setup(0x68))
    { // change to your own address
        Serial.println("MPU connection failed. Please check your connection with `connection_check` example.");
        delay(5000);
    }

    // calibrate anytime you want to
    Serial.println("Accel Gyro calibration will start in 5sec.");
    Serial.println("Please leave the device still on the flat plane.");
    mpu.verbose(true);
    delay(5000);
    mpu.calibrateAccelGyro();

    Serial.println("Mag calibration will start in 5sec.");
    Serial.println("Please Wave device in a figure eight until done.");
    delay(5000);
    mpu.calibrateMag();

    print_calibration();
    mpu.verbose(false);
}

void loop() {
    enc_read();
    if (mpu.update()) {
        static uint32_t prev_ms = millis();
        if (millis() > prev_ms + 25) {
            data[2] = 180-mpu.getYaw();
            print_data();
            prev_ms = millis();
        }
    }
}

void print_data() {
    Serial.print("$");
    Serial.print(data[0], 2);
    Serial.print(" ");
    Serial.print(data[1], 2);
    Serial.print(" ");
    Serial.println(data[2], 2);
}

void print_calibration() {
    Serial.println("< calibration parameters >");
    Serial.println("accel bias [g]: ");
    Serial.print(mpu.getAccBiasX() * 1000.f / (float)MPU9250::CALIB_ACCEL_SENSITIVITY);
    Serial.print(", ");
    Serial.print(mpu.getAccBiasY() * 1000.f / (float)MPU9250::CALIB_ACCEL_SENSITIVITY);
    Serial.print(", ");
    Serial.print(mpu.getAccBiasZ() * 1000.f / (float)MPU9250::CALIB_ACCEL_SENSITIVITY);
    Serial.println();
    Serial.println("gyro bias [deg/s]: ");
    Serial.print(mpu.getGyroBiasX() / (float)MPU9250::CALIB_GYRO_SENSITIVITY);
    Serial.print(", ");
    Serial.print(mpu.getGyroBiasY() / (float)MPU9250::CALIB_GYRO_SENSITIVITY);
    Serial.print(", ");
    Serial.print(mpu.getGyroBiasZ() / (float)MPU9250::CALIB_GYRO_SENSITIVITY);
    Serial.println();
    Serial.println("mag bias [mG]: ");
    Serial.print(mpu.getMagBiasX());
    Serial.print(", ");
    Serial.print(mpu.getMagBiasY());
    Serial.print(", ");
    Serial.print(mpu.getMagBiasZ());
    Serial.println();
    Serial.println("mag scale []: ");
    Serial.print(mpu.getMagScaleX());
    Serial.print(", ");
    Serial.print(mpu.getMagScaleY());
    Serial.print(", ");
    Serial.print(mpu.getMagScaleZ());
    Serial.println();
}
