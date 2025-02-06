import pyvjoy
import serial
import time

# Set up serial connection to Arduino
SERIAL_PORT = 'COM3'  # Replace with your Arduino's COM port
BAUD_RATE = 115200

# vJoy device setup
VJOY_DEVICE_ID = 1

try:
    arduino = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
    print(f"Connected to Arduino on {SERIAL_PORT}")
except Exception as e:
    print(f"Failed to connect to Arduino: {e}")
    exit()

try:
    vjoy = pyvjoy.VJoyDevice(VJOY_DEVICE_ID)
    print(f"Connected to vJoy device {VJOY_DEVICE_ID}")
except Exception as e:
    print(f"Failed to connect to vJoy device: {e}")
    exit()

def map_value(value, in_min, in_max, out_min, out_max):
    """Maps a value from one range to another."""
    return int((value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min)

def process_data(line):
    """Parses data received from Arduino and maps to joystick axes."""
    try:
        data = line.decode('utf-8').strip().split(',')
        if len(data) != 3:
            print(f"Invalid data: {line}")
            return

        # Parse and map accelerometer data
        roll = float(data[0])  # gForceX (Roll)
        pitch = float(data[1])  # gForceY (Pitch)
       # yaw = float(data[2])  # gForceZ (Yaw)
        #throttle_temp = float(data[3])  # Temperature-based throttle

        # Map to vJoy axes (0x1 to 0x8000 range for vJoy)
        roll_vjoy = map_value(roll, -2, 2, 0x1, 0x8000)  # Assuming gForce range (-2 to 2 g)
        pitch_vjoy = map_value(pitch, -2, 2, 0x1, 0x8000)  # Assuming gForce range (-2 to 2 g)
      #  yaw_vjoy = map_value(yaw, -2, 2, 0x1, 0x8000)  # Assuming gForce range (-2 to 2 g)
       # throttle_vjoy = map_value(throttle_temp, 0, 100, 0x1, 0x8000)  # Assuming temperature mapped to 0-100 throttle

        # Send to vJoy
        vjoy.data.wAxisX = roll_vjoy
        vjoy.data.wAxisY = pitch_vjoy
       # vjoy.data.wAxisZ = yaw_vjoy
      #  vjoy.data.wAxisZRot = throttle_vjoy
        vjoy.update()

        print(f"Sent to vJoy: Roll={roll_vjoy}, Pitch={pitch_vjoy}")

    except Exception as e:
        print(f"Error processing data: {e}")

# Main loop
print("Starting data transmission...")
try:
    while True:
        if arduino.in_waiting > 0:
            line = arduino.readline()
            process_data(line)
except KeyboardInterrupt:
    print("Exiting...")
except Exception as e:
    print(f"Error: {e}")
finally:
    arduino.close()
    print("Disconnected.")
