Embedded firmware for the PulseSync IoT device.

---
# PulseSync IoT – Firmware

Embedded C/C++ firmware for the PulseSync IoT heart-rate monitoring device.

## Hardware Platform
- **Microcontroller:** Arduino Uno  
- **Wi-Fi Module:** ESP-01S  
  - Communication via SoftwareSerial on D10 (TX) / D11 (RX)

## I/O Configuration
- **Heart Rate Sensor:** Grove Ear-Clip Sensor  
  - Input Pin: D6 (configured with `INPUT_PULLUP`)
- **Status LED:**  
  - Output Pin: D13  
  - Flashes on each detected heartbeat

## Functionality
- Performs real-time heart-rate detection using PPG-based pulse sensing  
- Calculates instantaneous BPM based on beat-to-beat timing  
- Publishes BPM data to **Adafruit IO**  
  - Feed name: `HeartRate`
- Maintains non-blocking sensor polling and LED synchronization during Wi-Fi transmissions

## Notes
- The ESP-01S uses a **project-specific command interface** for Wi-Fi and Adafruit IO communication  
- Credentials (Wi-Fi SSID, passwords, API keys) are intentionally omitted and must be supplied by the user

