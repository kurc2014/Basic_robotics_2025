import serial
import json
import time

# Initialize serial connection (Update COM port)
ser = serial.Serial('COM3', 9600, timeout=1)
time.sleep(2)  # Allow time for Arduino to initialize

def send_command(command):
    ser.reset_input_buffer()  # Flush old data to avoid lagging
    ser.write((command + '\n').encode())  # Send command
    time.sleep(0.1)  # Give Arduino time to process

    response = ser.readline().decode().strip()  # Read response
    return response if response else "No response received."

def read_serial_data():
    while True:
        print("\nAvailable commands: TEXT, INT, FLOAT, BINARY, JSON")
        command = input("Enter command: ").strip().upper()

        response = send_command(command)
        
        if response.startswith("Received: "):
            response = send_command(command)  # Re-request for valid data

        if response.startswith("Hello") or response.startswith("Invalid"):
            print(f"Text Data: {response}")

        elif response.isdigit():
            print(f"Integer Data: {int(response)}")

        elif response.replace('.', '', 1).isdigit():
            print(f"Float Data: {float(response)}")

        elif response.startswith("{") and response.endswith("}"):
            try:
                json_data = json.loads(response)
                print(f"JSON Data: {json_data}")
            except json.JSONDecodeError:
                print("Invalid JSON Data")

        else:  # Binary case
            print(f"Binary Data (raw): {response.encode()}")

# Run the function
read_serial_data()
