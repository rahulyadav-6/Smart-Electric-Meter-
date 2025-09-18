#include <SoftwareSerial.h>
#include <math.h>

const int voltageSensorPin = A0;
const int currentSensorPin = A1;
const int ledPin = 13;               // LED for constant ON indication
SoftwareSerial hc05Serial(2, 3);     // RX, TX for HC-05 Bluetooth

const float voltageCalibration = 3.0;   // Calibration factor for voltage sensor
const float currentCalibration = 0.1923; // Calibration factor for current sensor

unsigned long previousMillis = 0;
float energy_kWh = 0.0;

void setup() {
  pinMode(voltageSensorPin, INPUT);
  pinMode(currentSensorPin, INPUT);
  pinMode(ledPin, OUTPUT);

  digitalWrite(ledPin, HIGH);        // LED ON to indicate system is ON

  Serial.begin(9600);
  hc05Serial.begin(9600);

  previousMillis = millis();         // Initialize previousMillis here

  Serial.println("Electric Meter Starting...");
}

void loop() {
  unsigned long currentMillis = millis();
  unsigned long elapsedMillis = currentMillis - previousMillis;
  previousMillis = currentMillis;

  float rawVoltageRMS = readRMS(voltageSensorPin);
  float rawCurrentRMS = readRMS(currentSensorPin);

  float voltage = rawVoltageRMS * voltageCalibration;
  float current = rawCurrentRMS * currentCalibration;
  float power = voltage * current;        // Power in watts

  // Calculate energy in kWh
  float durationHours = elapsedMillis / 3600000.0;  // ms to hours
  energy_kWh += (power / 1000.0) * durationHours;  // watts to kW * hours = kWh

  // Time formatting
  unsigned long seconds = currentMillis / 1000;
  int hours = seconds / 3600;
  int minutes = (seconds % 3600) / 60;
  int secs = seconds % 60;

  // Print to Serial Monitor
  Serial.print("Time: ");
  printTime(hours, minutes, secs);
  Serial.print("Voltage (V): "); Serial.print(voltage, 2);
  Serial.print("\tCurrent (A): "); Serial.print(current, 2);
  Serial.print("\tPower (W): "); Serial.print(power, 2);
  Serial.print("\tEnergy (kWh): "); Serial.println(energy_kWh, 4);

  // Send data to HC-05 Bluetooth terminal
  hc05Serial.print("T: ");
  printTimeHC05(hours, minutes, secs);
  hc05Serial.print("(V): "); hc05Serial.print(voltage, 2);
  hc05Serial.print("(A): "); hc05Serial.print(current, 2);
  hc05Serial.print("(W): "); hc05Serial.print(power, 2);
  hc05Serial.print("(kWh): "); hc05Serial.println(energy_kWh, 4);

  delay(1000);  // Update every second
}

float readRMS(int pin) {
  int samples = 1000;
  long sum = 0;
  for (int i = 0; i < samples; i++) {
    int val = analogRead(pin);
    int offsetVal = val - 512;      // Remove DC offset BEFORE squaring
    sum += (long)offsetVal * offsetVal;
  }
  float mean = sum / (float)samples;
  return sqrt(mean);
}

void printTime(int h, int m, int s) {
  if (h < 10) Serial.print('0');
  Serial.print(h); Serial.print(":");
  if (m < 10) Serial.print('0');
  Serial.print(m); Serial.print(":");
  if (s < 10) Serial.print('0');
  Serial.print(s); Serial.print("\t");
}

void printTimeHC05(int h, int m, int s) {
  // Helper function to print time over HC-05 serial
  if (h < 10) hc05Serial.print('0');
  hc05Serial.print(h); hc05Serial.print(":");
  if (m < 10) hc05Serial.print('0');
  hc05Serial.print(m); hc05Serial.print(":");
  if (s < 10) hc05Serial.print('0');
  hc05Serial.print(s); hc05Serial.print("");
}
