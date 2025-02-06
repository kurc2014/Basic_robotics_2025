void setup() {
    Serial.begin(9600);  // Start serial communication
    //Serial.println("Arduino Ready. Send commands: TEXT, INT, FLOAT, BINARY, JSON");
}

void loop() {
    if (Serial.available() > 0) {
        String command = Serial.readStringUntil('\n');  // Read input until newline
        command.trim();  // Remove any extra whitespace
        
        if (command == "TEXT") {
            Serial.println("Hello, PySerial!");
        } 
        else if (command == "INT") {
            Serial.println(42);
        } 
        else if (command == "FLOAT") {
            Serial.println(3.14);
        } 
        else if (command == "BINARY") {
            byte binaryData[] = {0x12, 0x34, 0x56, 0x78};
            Serial.write(binaryData, 4);
            Serial.println();  // Add newline to separate responses
        } 
        else if (command == "JSON") {
            Serial.println("{\"temperature\": 25.5, \"humidity\": 60}");
        } 
        else {
            Serial.println("Invalid Command. Use: TEXT, INT, FLOAT, BINARY, JSON");
        }
    }
}
