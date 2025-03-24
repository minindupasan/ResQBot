#include "MotorController.h"
#include <Arduino.h>

MotorController::MotorController(int motorA1, int motorA2, int enableA, int motorB1, int motorB2, int enableB, int irLeft, int irRight) {
    this->motorA1 = motorA1;
    this->motorA2 = motorA2;
    this->enableA = enableA;
    this->motorB1 = motorB1;
    this->motorB2 = motorB2;
    this->enableB = enableB;
    this->irLeft = irLeft;
    this->irRight = irRight;

    // Initialize motor pins
    pinMode(motorA1, OUTPUT);
    pinMode(motorA2, OUTPUT);
    pinMode(enableA, OUTPUT);
    pinMode(motorB1, OUTPUT);
    pinMode(motorB2, OUTPUT);
    pinMode(enableB, OUTPUT);

    // Initialize IR sensor pins
    pinMode(irLeft, INPUT);
    pinMode(irRight, INPUT);
}

void MotorController::moveForward(int speed) {
    digitalWrite(motorA1, HIGH);
    digitalWrite(motorA2, LOW);
    digitalWrite(motorB1, HIGH);
    digitalWrite(motorB2, LOW);
    analogWrite(enableA, speed);
    analogWrite(enableB, speed);
}

void MotorController::moveBackward(int speed) {
    digitalWrite(motorA1, LOW);
    digitalWrite(motorA2, HIGH);
    digitalWrite(motorB1, LOW);
    digitalWrite(motorB2, HIGH);
    analogWrite(enableA, speed);
    analogWrite(enableB, speed);
}

void MotorController::stop() {
    digitalWrite(motorA1, LOW);
    digitalWrite(motorA2, LOW);
    digitalWrite(motorB1, LOW);
    digitalWrite(motorB2, LOW);
    analogWrite(enableA, 0);
    analogWrite(enableB, 0);
}

void MotorController::adjustSpeed(float yawError) {
    int constantSpeed = 100;  // Set a constant low speed for both motors

    // Check if an obstacle is detected
    if (digitalRead(irLeft) == LOW || digitalRead(irRight) == LOW) {
        stop();  // Stop motors immediately if an obstacle is detected
        Serial.println("Obstacle detected! Stopping motors.");
        return;  // Exit the function to prevent further movement adjustments
    }

    // Normal movement logic
    if (yawError > 5) {
        digitalWrite(motorA1, LOW);
        digitalWrite(motorA2, LOW);
        digitalWrite(motorB1, HIGH);
        digitalWrite(motorB2, LOW);
    } 
    else if (yawError < -5) {
        digitalWrite(motorA1, HIGH);
        digitalWrite(motorA2, LOW);
        digitalWrite(motorB1, LOW);
        digitalWrite(motorB2, LOW);
    } 
    else {
        digitalWrite(motorA1, HIGH);
        digitalWrite(motorA2, LOW);
        digitalWrite(motorB1, HIGH);
        digitalWrite(motorB2, LOW);
    }

    // Apply constant speed
    analogWrite(enableA, constantSpeed);
    analogWrite(enableB, constantSpeed);
}