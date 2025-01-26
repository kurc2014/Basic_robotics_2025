// Define pins for the ultrasonic sensor and buzzer
const int trigPin = 9;    // Trigger pin of the ultrasonic sensor
const int echoPin = 10;   // Echo pin of the ultrasonic sensor
const int buzzerPin = 8;  // Buzzer pin

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600); // Initialize serial communication for debugging
}

void loop() {
  // Measure distance using the ultrasonic sensor
  long duration;
  int distance;

  // Send a 10µs pulse to the trigger pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echo pin
  duration = pulseIn(echoPin, HIGH);

  // Calculate distance in cm
  distance = duration * 0.034 / 2;

  // Print the distance for debugging
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Control the buzzer based on distance
  if (distance <=5) {
    digitalWrite(buzzerPin, HIGH);
  } else {
    digitalWrite(buzzerPin, LOW);
  }
  delay(100); // Short delay before the next measurement
}
