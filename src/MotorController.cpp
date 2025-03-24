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
}

void MotorController::moveForward(int speed) {
    digitalWrite(motorA1, speed);
    digitalWrite(motorA2, 0);
    digitalWrite(motorB1, speed);
    digitalWrite(motorB2, 0);
}

void MotorController::moveBackward(int speed) {
    digitalWrite(motorA1, 0);
    digitalWrite(motorA2, speed);
    digitalWrite(motorB1, 0);
    digitalWrite(motorB2, speed);
}

void MotorController::stop() {
    digitalWrite(motorA1, 0);
    digitalWrite(motorA2, 0);
    digitalWrite(motorB1, 0);
    digitalWrite(motorB2, 0);
}

void MotorController::adjustSpeed(float yawError) {
    int constantSpeed = 100;  // Set a constant low speed for both motors

    // If yawError is positive, reverse the direction of motor A
    if (yawError > 5) {
        // Motor A should slow down or stop slightly, motor B should go forward
        digitalWrite(motorA1, LOW);          // Stop motor A forward
        digitalWrite(motorA2, LOW);  // Move motor A backward
        digitalWrite(motorB1, HIGH);  // Move motor B forward
        digitalWrite(motorB2, LOW);          // Stop motor B backward
        analogWrite(enableA, constantSpeed);
        analogWrite(enableB, constantSpeed);
    }
    // If yawError is negative, reverse the direction of motor B
    else if (yawError < -5) {
        // Motor B should slow down or stop slightly, motor A should go forward
        digitalWrite(motorA1, HIGH);  // Move motor A forward
        digitalWrite(motorA2, LOW);          // Stop motor A backward
        digitalWrite(motorB1, LOW);          // Stop motor B forward
        digitalWrite(motorB2, LOW);  // Move motor B backward
        analogWrite(enableA, constantSpeed);
        analogWrite(enableB, constantSpeed);
    }
    else {
        // If no yaw error, both motors move forward with constant speed
        digitalWrite(motorA1, HIGH);  // Move motor A forward
        digitalWrite(motorA2, LOW);              // Stop motor A backward
        digitalWrite(motorB1, HIGH);  // Move motor B forward
        digitalWrite(motorB2, LOW);              // Stop motor B backward
        analogWrite(enableA, constantSpeed);
        analogWrite(enableB, constantSpeed);
    }
}