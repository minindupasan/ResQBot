#include "arduino_secrets.h"
#include "environmentMonitor.h"
#include "fireDetection.h"
#include "communication.h"
#include "thingProperties.h"
#include <Arduino.h>

void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(115200);
  initDHT(); // Initialize DHT sensor
  pinMode(IR_FLAME_PIN_1, INPUT);
  pinMode(IR_FLAME_PIN_2, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  initBluetooth(); // Initialize Bluetooth communication

  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  ArduinoCloud.update();

  // Read values from sensors
  float temp = readTemperature();
  float hum = readHumidity();
  int mq = readMQSensor();
  int flame = detectFlame();

  temperature = temp;
  humidity = hum;
  mqValue = mq;
  flameDetected = (flame != 0);
  fireAlert = flameDetected;

  if (flameDetected) {
    alertFire();
  } else {
    stopBuzzer();
  }

  fireControl();
}








