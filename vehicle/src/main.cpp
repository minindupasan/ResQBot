#include <Arduino.h>
#include "MotorController.h"
#include "GyroController.h"
#include "FireSuppression.h"

// Motor pin definitions
int motorA1 = 42;  // IN1
int motorA2 = 40;  // IN2
int enableA = 2;  // ENA (Enable pin)
int motorB1 = 38;  // IN3
int motorB2 = 36;  // IN4
int enableB = 3;  // ENB (Enable pin)

// Define IR obstacle sensor pin
int irObstacle = 50;  // Obstacle IR sensor

// Create objects
GyroController gyro;
MotorController motor(motorA1, motorA2, enableA, motorB1, motorB2, enableB, irObstacle, gyro);
FireSuppressionSystem fireSystem;

void setup() {
    Serial.begin(115200);
    while (!Serial)
        delay(10);

    gyro.initialize();
    fireSystem.initialize();
}

void loop() {
    float currentYaw = gyro.getYaw();
    motor.controlCar();
    fireSystem.checkFire();

    Serial.print("Yaw: ");
    Serial.println(currentYaw);

    delay(50);
}