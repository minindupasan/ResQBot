#include <Arduino.h>
#include "MotorController.h"
#include "GyroController.h"
#include "FireSuppression.h"
#include "Communication.h"

// Motor pin definitions
int motorA1 = 42;  // IN1
int motorA2 = 40;  // IN2
int enableA = 2;   // ENA (Enable pin)
int motorB1 = 38;  // IN3
int motorB2 = 36;  // IN4
int enableB = 3;   // ENB (Enable pin)

// Define Ultrasonic sensor pins
int trigPin = 9;   // Trigger pin for ultrasonic sensor
int echoPin = 10;  // Echo pin for ultrasonic sensor

GyroController gyro;
FireSuppressionSystem fireSystem;
MotorController motor(motorA1, motorA2, enableA, motorB1, motorB2, enableB, trigPin, echoPin, gyro, fireSystem);

void setup() {
    Serial.begin(115200);
    setupWiFi();   // Initialize Wi-Fi connection
    setupServer(); // Start the server

    while (!Serial)
        delay(10);

    gyro.initialize();
    fireSystem.initialize();
}

void loop() {
    handleClientRequests(); // Process incoming fire alerts

    float currentYaw = gyro.getYaw();
    motor.controlCar();
    Serial.print("Yaw: ");
    Serial.println(currentYaw);

    delay(50);
}