int motor1pin1 = 2;
int motor1pin2 = 3;

int motor2pin1 = 4;
int motor2pin2 = 5;

int ENA = 10;
int ENB = 9;

//uses proximity sensing
const int trigPin = 6;    // Trigger pin of the ultrasonic sensor
const int echoPin = 7;   // Echo pin of the ultrasonic sensor

// Set initial motor speeds (adjust as needed for balance)
int speedA = 170; // Adjust from 0-255 for left motor
int speedB = 170; // Adjust from 0-255 for right motor

void setup() {
  Serial.begin(9600); // Initialize serial communication

  // put your setup code here, to run once:
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);

  //initailize the ultrasonic sensors
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  //initialize ena pins
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  
  // Set initial motor speeds for balance
  analogWrite(ENA, speedA);
  analogWrite(ENB, speedB);
}

void loop() {
  int distance = proximity();
  if (distance <= 20) {
    left();
  } else {
    forward();
  }
}

int proximity() {
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

  // Check for false readings
  if (distance <= 0 || distance > 400) {
    return 400; // Ignore bad readings
  }

  // Print the distance for debugging
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(100); // Short delay before the next measurement
  return distance;
}

void forward() {
  // Enable motors with predefined speed values
  analogWrite(ENA, speedA);
  analogWrite(ENB, speedB);
  
  //motor 1
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);
  
  //motor 2
  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);
}

void stop() {
  //motor 1
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, LOW);
  
  //motor 2
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, LOW);

  // Disable motors
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

void left() {   
  // Reduce speed while turning
  analogWrite(ENA, (int)(speedA / 1.2));
  analogWrite(ENB, (int)(speedB / 1.2));

  //motor 1
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, HIGH);
  
  //motor 2
  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);
}

void right() {
  // Reduce speed while turning
  analogWrite(ENA, (int)(speedA / 1.2));
  analogWrite(ENB, (int)(speedB / 1.2));

  //motor 1
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);
  
  //motor 2
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, HIGH);
}

