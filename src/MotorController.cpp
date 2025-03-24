#include "MotorController.h"
#include <Arduino.h>

MotorController::MotorController(int motorA1, int motorA2, int enableA, int motorB1, int motorB2, int enableB) {
    this->motorA1 = motorA1;
    this->motorA2 = motorA2;
    this->enableA = enableA;
    this->motorB1 = motorB1;
    this->motorB2 = motorB2;
    this->enableB = enableB;

    // Initialize motor pins
    pinMode(motorA1, OUTPUT);
    pinMode(motorA2, OUTPUT);
    pinMode(enableA, OUTPUT);
    pinMode(motorB1, OUTPUT);
    pinMode(motorB2, OUTPUT);
    pinMode(enableB, OUTPUT);

    // Enable motors
    digitalWrite(enableA, HIGH);
    digitalWrite(enableB, HIGH);
}

void MotorController::moveForward(int speed) {
    analogWrite(motorA1, speed);
    analogWrite(motorA2, 0);
    analogWrite(motorB1, speed);
    analogWrite(motorB2, 0);
}

void MotorController::moveBackward(int speed) {
    analogWrite(motorA1, 0);
    analogWrite(motorA2, speed);
    analogWrite(motorB1, 0);
    analogWrite(motorB2, speed);
}

void MotorController::stop() {
    analogWrite(motorA1, 0);
    analogWrite(motorA2, 0);
    analogWrite(motorB1, 0);
    analogWrite(motorB2, 0);
}

void MotorController::adjustSpeed(float yawError) {
    int adjustment = yawError * 10;  // Scale the yaw error to adjust motor speeds

    motorASpeed = 255 - adjustment;  // Reduce speed of motor A if yaw error is positive
    motorBSpeed = 255 + adjustment;  // Increase speed of motor B if yaw error is negative

    // Ensure motor speeds are within valid range
    motorASpeed = constrain(motorASpeed, 0, 255);
    motorBSpeed = constrain(motorBSpeed, 0, 255);

    // Apply adjusted speeds
    moveForward(motorASpeed);  // Move forward with adjusted speeds
    analogWrite(motorB1, motorBSpeed);
    analogWrite(motorB2, 0);
}