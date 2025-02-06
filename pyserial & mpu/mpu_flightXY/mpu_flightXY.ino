#include <Wire.h>

// Variables for acceleration
long accelX, accelY, accelZ;
float gForceX, gForceY, gForceZ;

// Variables for temperature
long tempRaw;
float tempr;

// Variables for throttle control
float baseTemp = 0.0; // Base temperature for throttle control
int throttle = 0;     // Throttle percentage

void setup() {
  Serial.begin(115200);
  Wire.begin();
  setupMPU();
  recordBaseTemperature(); // Initialize the base temperature
}

void loop() {
  recordAccelRegisters();
  recordTempData();
  calculateThrottle();
  printData();
  delay(100);
}

void setupMPU() {
  Wire.beginTransmission(0b1101000); // MPU I2C address
  Wire.write(0x6B);                  // Power Management register
  Wire.write(0b00000000);            // Wake up the MPU
  Wire.endTransmission();

  Wire.beginTransmission(0b1101000);
  Wire.write(0x1C);                  // Accelerometer Configuration register
  Wire.write(0b00000000);            // Full scale +/- 2g
  Wire.endTransmission();
}

void recordBaseTemperature() {
  recordTempData();
  baseTemp = tempr; // Set the current temperature as the base
}

void recordAccelRegisters() {
  Wire.beginTransmission(0b1101000);
  Wire.write(0x3B);
  Wire.endTransmission();
  Wire.requestFrom(0b1101000, 6);
  while (Wire.available() < 6);

  accelX = Wire.read() << 8 | Wire.read();
  accelY = Wire.read() << 8 | Wire.read();
  accelZ = Wire.read() << 8 | Wire.read();

  processAccelData();
}

void processAccelData() {
  gForceX = accelX / 16384.0;
  gForceY = accelY / 16384.0;
  gForceZ = accelZ / 16384.0;
}

void recordTempData() {
  Wire.beginTransmission(0b1101000);
  Wire.write(0x41);
  Wire.endTransmission();
  Wire.requestFrom(0b1101000, 2);
  while (Wire.available() < 2);

  tempRaw = Wire.read() << 8 | Wire.read();
  processTempData();
}

void processTempData() {
  tempr = (tempRaw / 340.0) + 35.0;
}

void calculateThrottle() {
  float tempIncrease = tempr - baseTemp;
  throttle = map(tempIncrease * 100, 0, 400, 0, 100); // Map 0-4 degrees to 0-100%
  throttle = constrain(throttle, 0, 100);
}

void printData() {
 // Serial.print("Accel (g)");
 // Serial.print(" X=");
   Serial.print(gForceX);
  Serial.print(",");
  Serial.print(gForceY);
  Serial.print(","); 
  Serial.print(gForceZ);
  Serial.print(","); 
  Serial.println(tempr);
}
