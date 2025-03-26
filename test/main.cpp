// #include <Arduino.h>

// // Define flame sensor pins
// #define FLAME_SENSOR_1 24
// #define FLAME_SENSOR_2 22
// #define FLAME_SENSOR_3 26
// #define RELAY_PIN 30

// void setup() {
//     Serial.begin(115200);
//     pinMode(FLAME_SENSOR_1, INPUT);
//     pinMode(FLAME_SENSOR_2, INPUT);
//     pinMode(FLAME_SENSOR_3, INPUT);
//     pinMode(RELAY_PIN, OUTPUT);
//     digitalWrite(RELAY_PIN, LOW); // Initialize relay as OFF
// }

// void loop() {
//     int sensor1 = digitalRead(FLAME_SENSOR_1);
//     int sensor2 = digitalRead(FLAME_SENSOR_2);
//     int sensor3 = digitalRead(FLAME_SENSOR_3);
    
//     if(sensor1 == LOW) {
//         Serial.println("Flame detected by sensor 1");
//     }
//     else if(sensor2 == LOW) {
//         Serial.println("Flame detected by sensor 2");
//     }
//     else if(sensor3 == LOW) {
//         Serial.println("Flame detected by sensor 3");
//     }else{
//         Serial.println("No flame detected");
//     }

//     if(sensor1 == LOW || sensor2 == LOW || sensor3 == LOW) {
//         digitalWrite(RELAY_PIN, LOW); // Turn on relay
//         Serial.println("Fire detected! Activating suppression system...");
//     } else {
//         digitalWrite(RELAY_PIN, HIGH); // Turn off relay
//         Serial.println("No fire detected. Suppression system deactivated.");
//     }
// }


#include <Arduino.h>

int motorA1 = 42;  // IN1
int motorA2 = 40;  // IN2
int enableA = 2;  // ENA (Enable pin)
int motorB1 = 38;  // IN3
int motorB2 = 36;  // IN4
int enableB = 3;  // ENB (Enable pin)

int speed = 150;

void setup() {
    Serial.begin(115200);
    pinMode(motorA1, OUTPUT);
    pinMode(motorA2, OUTPUT);
    pinMode(enableA, OUTPUT);
    pinMode(motorB1, OUTPUT);
    pinMode(motorB2, OUTPUT);
    pinMode(enableB, OUTPUT);
}

void loop() {
    digitalWrite(motorA1, LOW);
    digitalWrite(motorA2, HIGH);
    digitalWrite(motorB1, LOW);
    digitalWrite(motorB2, LOW);
    analogWrite(enableA, speed);
    analogWrite(enableB, speed);
}
