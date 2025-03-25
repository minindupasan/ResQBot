#include <Arduino.h>

// Define flame sensor pins
#define FLAME_SENSOR_1 24
#define FLAME_SENSOR_2 22
#define FLAME_SENSOR_3 26
#define RELAY_PIN 30

void setup() {
    Serial.begin(115200);
    pinMode(FLAME_SENSOR_1, INPUT);
    pinMode(FLAME_SENSOR_2, INPUT);
    pinMode(FLAME_SENSOR_3, INPUT);
    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, LOW); // Initialize relay as OFF
}

void loop() {
    int sensor1 = digitalRead(FLAME_SENSOR_1);
    int sensor2 = digitalRead(FLAME_SENSOR_2);
    int sensor3 = digitalRead(FLAME_SENSOR_3);
    
    if(sensor1 == LOW) {
        Serial.println("Flame detected by sensor 1");
    }
    else if(sensor2 == LOW) {
        Serial.println("Flame detected by sensor 2");
    }
    else if(sensor3 == LOW) {
        Serial.println("Flame detected by sensor 3");
    }else{
        Serial.println("No flame detected");
    }

    if(sensor1 == LOW || sensor2 == LOW || sensor3 == LOW) {
        digitalWrite(RELAY_PIN, LOW); // Turn on relay
        Serial.println("Fire detected! Activating suppression system...");
    } else {
        digitalWrite(RELAY_PIN, HIGH); // Turn off relay
        Serial.println("No fire detected. Suppression system deactivated.");
    }
}