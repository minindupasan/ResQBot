#include <Wire.h>
#include <SoftwareSerial.h>
#include "mq_humidity_monitor.h"
#include "flame_detection.h"
#include "gsm.h"
#include <Arduino.h>

// Initialize variables
int mqValue = 0;               // Variable to store MQ sensor value
bool flameDetected = false;    // Boolean to store flame detection status
float humidity = 0.0;          // Variable to store humidity value

void setup() {
  // Start serial communication
  Serial.begin(115200);

  // Initialize GSM module (done in gsm_sim800.cpp)
  delay(1000);
  
  // Print initialization message
  Serial.println("System initialized.");
}

void loop() {
  // Read MQ sensor value (fire detection)
  mqValue = readMQSensor();

  // Read flame sensor value
  flameDetected = detectFlame();

  // Read humidity value
  humidity = readHumidity();

  // Fire detection logic
  if (mqValue > FIRE_THRESHOLD || flameDetected) {
    Serial.println("Fire detected!");

    // Send SMS alert to phone
    sendSMS("Fire detected in the room!");

  } else {
    Serial.println("No fire detected.");
  }

  // Check humidity (optional logic)
  if (humidity > HUMIDITY_THRESHOLD) {
    Serial.println("High humidity detected.");
  }

  delay(2000); // Delay for 2 seconds before next loop iteration
}