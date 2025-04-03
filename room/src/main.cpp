#include <Wire.h>
#include <SoftwareSerial.h>
#include "mqHumidityMonitor.h"
#include "fireDetection.h"
#include "communication.h"
#include "gsm.h"
#include <Arduino.h>

// Initialize variables
int mqValue = 0;               // Variable to store MQ sensor value
bool flameDetected = false;    // Boolean to store flame detection status
float humidity = 0.0;          // Variable to store humidity value

unsigned long lastCheckTime = 0;
const unsigned long checkInterval = 5000;  // Check every 5 seconds

void setup() {
  // Start serial communication
  Serial.begin(115200);
  initBluetooth();  // Initialize Wi-Fi connection
  delay(1000);
  
  Serial.println("✅ System initialized.");
}

void loop() {
    fireControl();
}