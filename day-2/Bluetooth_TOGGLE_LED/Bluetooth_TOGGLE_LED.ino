#include <SoftwareSerial.h>

#define BT_RX_PIN 2 // Connect to TX of HC-05
#define BT_TX_PIN 3 // Connect to RX of HC-05

SoftwareSerial bluetooth(BT_RX_PIN, BT_TX_PIN);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT); // Set the built-in LED pin as output
  digitalWrite(LED_BUILTIN, LOW); // Turn off the LED initially

  Serial.begin(9600); // For serial monitor
  bluetooth.begin(9600); // HC-05 default baud rate
  
  Serial.println("Waiting for Bluetooth commands...");
}

void loop() {
  // Check for incoming Bluetooth data
  if (bluetooth.available()) {
    String btCommand = bluetooth.readStringUntil('\n'); // Read command until newline
    btCommand.trim(); // Remove any extra whitespace
    handleCommand(btCommand); // Process the command
  }

  // Check for data from the Serial Monitor
  if (Serial.available()) {
    String serialCommand = Serial.readStringUntil('\n'); // Read command until newline
    serialCommand.trim(); // Remove any extra whitespace
    handleCommand(serialCommand); // Process the command
  }
}

// Function to handle received commands
void handleCommand(String command) {
  if (command.equalsIgnoreCase("ON")) {
    digitalWrite(LED_BUILTIN, HIGH); // Turn LED on
    Serial.println("LED turned ON");
    bluetooth.println("LED turned ON");
  } else if (command.equalsIgnoreCase("OFF")) {
    digitalWrite(LED_BUILTIN, LOW); // Turn LED off
    Serial.println("LED turned OFF");
    bluetooth.println("LED turned OFF");
  } else {
    Serial.println("Invalid command: " + command);
    bluetooth.println("Invalid command: " + command);
  }
}
