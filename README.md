# Smart Electric Meter

## Overview
This project implements a smart electric meter using Arduino Uno, ZMPT voltage sensor, ACS current sensor, and HC-05 Bluetooth module. Sensor data is logged via Python for monitoring and analysis.

## Features
- Measure voltage, current, power, and energy.
- Data logging using Python via Bluetooth.
- Real-time monitoring.
- Easy calibration and setup.

## Hardware
- Arduino Uno
- ZMPT Voltage Sensor
- ACS Current Sensor
- HC-05 Bluetooth Module
- Jumper Wires, Breadboard

## Software
- Arduino IDE
- Python 3.x
- Libraries: pyserial, pandas

## Wiring Diagram
![Wiring Diagram](Electric-Meter-circuit-Daigaram.jpg)

## Usage
1. Upload `ElectricMeter.ino` to Arduino.
2. Connect Arduino to Bluetooth module.
3. Run `BluetoothLogger.py` to log data to CSV.
4. Analyze data using Excel or Python.

## Future Improvements
- Add Wi-Fi module for cloud monitoring.
- Integrate ESP32 for standalone monitoring.
- Implement real-time dashboard.
