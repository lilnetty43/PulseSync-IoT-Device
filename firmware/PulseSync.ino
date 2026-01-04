/***************************************************************************
 Antoinette Kellam - CPEG298 - Spring 2025

    ESP-01S + Grove Ear-Clip Heart Sensor on D6 → Adafruit IO 
  • SoftwareSerial on D10/D11 for ESP-01
  • Poll D6 for beats, flash D13 at each beat
  • Publish instantaneous BPM immediately (and keep polling during send)


 NOTE:
 The ESP-01S in this project uses a custom command interface / firmware
 wrapper (e.g., wifi_ssid=, setup_io, send_data) rather than stock ESP AT
 commands. These commands are specific to the ESP-01S setup used in this
 project and are not part of the default Espressif AT firmware.
***************************************************************************/
#include <Arduino.h>
#include <SoftwareSerial.h>  // Allows us to use two GPIO pins for a second UART

// ——— Pin definitions ———
#define RESET_PIN         9   // ESP-01S CH_PD/RESET
#define UART_RX_PIN      11   // ESP-01 TX → D11
#define UART_TX_PIN      10   // ESP-01 RX ← D10
#define HEART_SENSOR_PIN  6   // Grove sensor → D6
#define LED_PIN          13   // Indicator LED net “13” in your schematic

// ——— SoftwareSerial for ESP-01 ———
SoftwareSerial espSerial(UART_RX_PIN, UART_TX_PIN);

// ——— Adafruit IO credentials ———
const String IO_USERNAME = "YOUR_ADAFRUIT_IO_USERNAME";
const String IO_KEY      = "YOUR_ADAFRUIT_IO_KEY";
const String WIFI_SSID   = "YOUR_WIFI_SSID";
const String WIFI_PASS   = "YOUR_WIFI_PASSWORD";

// ——— Heart-beat detection globals ———
unsigned long lastBeatTime = 0;      // timestamp of last beat
unsigned int  heartRate    = 0;      // computed BPM
bool          newReady     = false;  // flag: a new BPM is ready

// ——— LED flash timing (non-blocking) ———
unsigned long ledOnTime       = 0;
const unsigned long ledFlashDuration = 50; // ms

// ——— For edge-detecting the sensor pin ———
bool lastSensorState = LOW;

// ——— Helper: send AT-style cmd & collect response ———
String espSend(const String &cmd, int timeout=2000, bool dbg=true) {
  String resp;
  Serial.print("> "); Serial.println(cmd);
  espSerial.println(cmd);
  unsigned long start = millis();
  while (millis() - start < timeout) {
    while (espSerial.available()) {
      resp += char(espSerial.read());
    }
    // keep heart polling alive while waiting:
    // (so LED still flashes on beats during long publishes)
    bool now = digitalRead(HEART_SENSOR_PIN);
    if (now && !lastSensorState) {
      unsigned long t = millis();
      unsigned long delta = t - lastBeatTime;
      lastBeatTime = t;
      if (delta < 2000) {
        heartRate = 60000UL / delta;
        newReady  = true;  // allow immediate send back in loop
      }
      // schedule LED flash
      digitalWrite(LED_PIN, HIGH);
      ledOnTime = millis();
    }
    lastSensorState = now;
  }
  resp.trim();
  if (dbg) {
    Serial.print("Resp: "); Serial.println(resp);
  }
  return resp;
}

// ——— Poll the heart sensor & LED off-timer ———
void pollHeartSensor() {
  bool now = digitalRead(HEART_SENSOR_PIN);

  // on rising edge → record a beat
  if (now && !lastSensorState) {
    unsigned long t = millis();
    unsigned long delta = t - lastBeatTime;
    lastBeatTime = t;

    if (delta < 2000) {
      heartRate = 60000UL / delta;  // instantaneous BPM
      newReady  = true;
    }

    // schedule LED flash
    digitalWrite(LED_PIN, HIGH);
    ledOnTime = millis();
  }
  lastSensorState = now;

  // turn LED off once its flash-duration is up
  if (ledOnTime && (millis() - ledOnTime >= ledFlashDuration)) {
    digitalWrite(LED_PIN, LOW);
    ledOnTime = 0;
  }
}

void setup() {
  // — Serial setups —
  Serial.begin(115200); // for the monitor
  espSerial.begin(9600); // for the commands

  // — Reset ESP-01S —
  pinMode(RESET_PIN, OUTPUT);
  digitalWrite(RESET_PIN, LOW);
  delay(1000);
  digitalWrite(RESET_PIN, HIGH);
  delay(2000); // 2 sec loop reading

  // — Sensor & LED pins —
  pinMode(HEART_SENSOR_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);

  // — Drain any stray ESP bytes —
  unsigned long t0 = millis();
  while (millis() - t0 < 2000) {
    while (espSerial.available()) espSerial.read();
    pollHeartSensor();
  }

  // — Adafruit IO handshake —
  Serial.println("\n\n--- Heart Rate → Adafruit IO ---");
  espSend("get_macaddr");
  espSend("get_version");
  espSend("wifi_ssid=" + WIFI_SSID);
  delay(500);
  espSend("wifi_pass=" + WIFI_PASS);
  delay(500);
  espSend("io_user=" + IO_USERNAME);
  espSend("io_key="  + IO_KEY, 2000, false);

  String r = espSend("setup_io", 30000);
  if (r.indexOf("connected") < 0) {
    Serial.println("Adafruit IO Connection Failed");
    while (1);
  }
  espSend("setup_pubfeed=1,HeartRate");
  Serial.println("------ Setup Complete ------");
}

void loop() {
  // always poll sensor first (handles LED off-timer too)
  pollHeartSensor(); //edge detects rising pulse from D6

  if (newReady) {
    // send immediately on each beat
    Serial.print("Sending BPM: "); Serial.println(heartRate);
    espSerial.print("send_data=1,");
    espSerial.println(heartRate);

    // wait up to 2s for ESP reply, but keep polling sensor:
    String resp;
    unsigned long t1 = millis();
    while (millis() - t1 < 2000) {
      while (espSerial.available()) {
        resp += char(espSerial.read());
      }
      pollHeartSensor();
    }
    Serial.print("Resp: "); Serial.println(resp);

    newReady = false;
    // no extra delay – each heartbeat triggers its own send & flash
  }
}

