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
  
  initWiFi();  // Initialize Wi-Fi connection
  delay(1000);
  
  Serial.println("✅ System initialized.");
}

void loop() {
  // Use millis() to avoid blocking delays
  if (millis() - lastCheckTime >= checkInterval) {
    lastCheckTime = millis();
    
    int fireRoom = detectFlame();
    if (fireRoom != 0) {
        fireControl();
        sendFireAlert(fireRoom);  // Send the detected room number to ESP-01
        delay(5000);  // Avoid spamming requests
    }
    mqValue = readMQSensor();  // Read MQ sensor value
    humidity = readHumidity(); // Read humidity
    
    Serial.print("🌡️ Humidity: ");
    Serial.print(humidity);
    Serial.println("%");
    
    Serial.print("🔥 MQ Sensor Value: ");
    Serial.println(mqValue);
  }
}