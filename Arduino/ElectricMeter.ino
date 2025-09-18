import serial
import pandas as pd
from datetime import datetime

# Replace 'COM5' with your HC-05 port
ser = serial.Serial('COM5', 9600, timeout=1)
data_list = []

try:
    while True:
        line = ser.readline().decode().strip()
        if line:
            timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
            data_list.append([timestamp, line])
            print(timestamp, line)
except KeyboardInterrupt:
    df = pd.DataFrame(data_list, columns=["Time", "Data"])
    df.to_csv("ElectricMeterData.csv", index=False)
    print("Data saved to ElectricMeterData.csv")
