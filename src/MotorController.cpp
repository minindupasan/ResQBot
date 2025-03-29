#include "MotorController.h"
#include <Arduino.h>

MotorController::MotorController(int motorA1, int motorA2, int enableA, int motorB1, int motorB2, int enableB, int irLeft, int irRight,int irObstacle) {
    this->motorA1 = motorA1;
    this->motorA2 = motorA2;
    this->enableA = enableA;
    this->motorB1 = motorB1;
    this->motorB2 = motorB2;
    this->enableB = enableB;
    this->irLeft = irLeft;
    this->irRight = irRight;
    this->irObstacle = irObstacle;

    pinMode(motorA1, OUTPUT);
    pinMode(motorA2, OUTPUT);
    pinMode(enableA, OUTPUT);
    pinMode(motorB1, OUTPUT);
    pinMode(motorB2, OUTPUT);
    pinMode(enableB, OUTPUT);
    pinMode(irLeft, INPUT);
    pinMode(irRight, INPUT);
    pinMode(irObstacle, INPUT);
}

void MotorController::moveForward(int speed) {
    analogWrite(enableA, speed);
    analogWrite(enableB, speed);
    digitalWrite(motorA1, LOW);
    digitalWrite(motorA2, HIGH);
    digitalWrite(motorB1, LOW);
    digitalWrite(motorB2, HIGH);
}

void MotorController::moveBackward(int speed) {
    digitalWrite(motorA1, HIGH);
    digitalWrite(motorA2, LOW);
    digitalWrite(motorB1, HIGH);
    digitalWrite(motorB2, LOW);
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

void MotorController::adjustSpeed() {
    int left = digitalRead(irLeft)==LOW ? LOW : HIGH;
    int right = digitalRead(irRight)==LOW ? LOW : HIGH;
    Serial.println("Left: "); 
    Serial.println(left);
    Serial.println("Right: ");
    Serial.println(right);

    if (left == LOW && right == HIGH) {
        Serial.println("Turning left");
        LEFT();
    } else if (right == LOW && left == HIGH) {
        Serial.println("Turning right");
        RIGHT();
    } else if (left == LOW && right == LOW) {  // Move forward when both sensors are clear
        Serial.println("Moving forward");
        moveForward(100);
    } else {
        Serial.println("Stopping");
        stop();
    }
}

void MotorController::LEFT() {
    analogWrite(enableB, 25); // Slow down right motor
    analogWrite(enableA, 100);
    while (digitalRead(irLeft) == LOW) {
        if (digitalRead(irRight) == LOW) {
            stop();
            while (digitalRead(irLeft) == LOW && digitalRead(irRight) == LOW);
        }
        moveForward(100);
    }
    moveForward(100);
}

void MotorController::RIGHT() {
    analogWrite(enableA, 25); // Slow down left motor
    analogWrite(enableB, 100);
    while (digitalRead(irRight) == LOW) {
        if (digitalRead(irLeft) == LOW) {
            stop();
            while (digitalRead(irLeft) == LOW && digitalRead(irRight) == LOW);
        }
        moveForward(100);
    }
    moveForward(100);
}