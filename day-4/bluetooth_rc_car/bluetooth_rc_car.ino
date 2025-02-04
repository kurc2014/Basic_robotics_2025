#include <SoftwareSerial.h>

int motor1pin1 = 2;
int motor2pin1 = 4;

int ENA = 10;
int ENB = 9;

#define BT_RX_PIN 6 // Connect to TX of HC-05
#define BT_TX_PIN 7 // Connect to RX of HC-05

int speedA = 170; // Adjust from 0-255 for left motor
int speedB = 170; // Adjust from 0-255 for right motor

SoftwareSerial bluetooth(BT_RX_PIN, BT_TX_PIN);

void setup() {
  Serial.begin(9600); // For Serial Monitor
  bluetooth.begin(9600); // HC-05 default baud rate
  
  Serial.println("Waiting for Bluetooth connection...");

  // Initialize motor pins
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor2pin1, OUTPUT);

  // Initialize enable pins
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Set initial speed (balanced)
  analogWrite(ENA, speedA);
  analogWrite(ENB, speedB);
}

void loop() {
  if (bluetooth.available()) {
    char btData = bluetooth.read();
    Serial.print("Received: ");
    Serial.println(btData);

    if (btData == '1') {
      forward();
    } 
    else if (btData == '2') {
      left();
    }
    else if (btData == '3') {
      right();
    }
    else if (btData == '4') {
      stop();
    }
  }
}

void forward() {
  analogWrite(ENA, speedA);
  analogWrite(ENB, speedB);
  
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor2pin1, HIGH);
}

void stop() {
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor2pin1, LOW);

  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

void left() {   
  analogWrite(ENA, speedA / 2); // Slow left motor
  analogWrite(ENB, speedB);     // Right motor stays full speed
}

void right() {
  analogWrite(ENA, speedA);     // Left motor stays full speed
  analogWrite(ENB, speedB / 2); // Slow right motor
}
