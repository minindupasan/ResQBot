#include "MotorController.h"
#include "GyroController.h"
#include <Arduino.h>


MotorController::MotorController(int motorA1, int motorA2, int enableA, int motorB1, int motorB2, int enableB, int trigPin, int echoPin, GyroController &gyro) {
    this->motorA1 = motorA1;
    this->motorA2 = motorA2;
    this->enableA = enableA;
    this->motorB1 = motorB1;
    this->motorB2 = motorB2;
    this->enableB = enableB;
    this->trigPin = trigPin;
    this->echoPin = echoPin;
    this->gyro = &gyro;

    pinMode(motorA1, OUTPUT);
    pinMode(motorA2, OUTPUT);
    pinMode(enableA, OUTPUT);
    pinMode(motorB1, OUTPUT);
    pinMode(motorB2, OUTPUT);
    pinMode(enableB, OUTPUT);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

float MotorController::getObstacleDistance() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    long duration = pulseIn(echoPin, HIGH);
    float distance = duration * 0.034 / 2; // Convert to cm
    return distance;
}

void MotorController::moveForward(int baseSpeed) {
    if (getObstacleDistance() < OBSTACLE_THRESHOLD) {
        stopMoving();
        Serial.println("Obstacle detected! Stopping motors.");
        return;
    }

    float yawError = gyro->getYaw();
    float correction = yawError * 2.0; // Proportional control (tune this factor as needed)
    
    int leftSpeed = constrain(baseSpeed + correction, 0, 255);
    int rightSpeed = constrain(baseSpeed - correction, 0, 255);
    
    analogWrite(enableA, leftSpeed);
    analogWrite(enableB, rightSpeed);
    digitalWrite(motorA1, LOW);
    digitalWrite(motorA2, HIGH);
    digitalWrite(motorB1, LOW);
    digitalWrite(motorB2, HIGH);
}

void MotorController::moveBackward(int speed) {
    analogWrite(enableA, speed);
    analogWrite(enableB, speed);
    digitalWrite(motorA1, HIGH);
    digitalWrite(motorA2, LOW);
    digitalWrite(motorB1, HIGH);
    digitalWrite(motorB2, LOW);
}

void MotorController::stopMoving() {
    brake();
    digitalWrite(motorA1, LOW);
    digitalWrite(motorA2, LOW);
    digitalWrite(motorB1, LOW);
    digitalWrite(motorB2, LOW);
    analogWrite(enableA, 0);
    analogWrite(enableB, 0);
    delay(2000);
}

void MotorController::turnLeft(int speed) {
    float targetYaw = gyro->getYaw() - TARGET_ANGLE;
    stopMoving();

    analogWrite(enableA, speed);
    analogWrite(enableB, 0);
    digitalWrite(motorA1, LOW);
    digitalWrite(motorA2, HIGH);
    digitalWrite(motorB1, HIGH);
    digitalWrite(motorB2, LOW);

    while (gyro->getYaw() > targetYaw) {
        Serial.println(gyro->getYaw());
        delay(10);
    }

    brakeTurnLeft();
    stopMoving();
    gyro->resetSystem();
}

void MotorController::turnRight(int speed) {
    float targetYaw = gyro->getYaw() + TARGET_ANGLE;
    stopMoving();

    analogWrite(enableA, 0);
    analogWrite(enableB, speed);
    digitalWrite(motorA1, HIGH);
    digitalWrite(motorA2, LOW);
    digitalWrite(motorB1, LOW);
    digitalWrite(motorB2, HIGH);

    while (gyro->getYaw() < targetYaw) {
        Serial.println(gyro->getYaw());
        delay(10);
    }

    brakeTurnRight();
    gyro->resetSystem();
}

void MotorController::controlCar() {
    int turningSpeed = 60;
    if (getObstacleDistance() < OBSTACLE_THRESHOLD) {
        Serial.println("Turning right due to obstacle!");
        stopMoving();
        turnRight(turningSpeed);
    } else {
        moveForward(50);
    }
}

void MotorController::brake() {
    digitalWrite(motorA1, HIGH);
    digitalWrite(motorA2, LOW);
    digitalWrite(motorB1, HIGH);
    digitalWrite(motorB2, LOW);
    analogWrite(enableA, 150);
    analogWrite(enableB, 150);
    delay(50);
}

void MotorController::brakeTurnLeft() {
    digitalWrite(motorA1, HIGH);
    digitalWrite(motorA2, LOW);
    digitalWrite(motorB1, LOW);
    digitalWrite(motorB2, HIGH);
    analogWrite(enableA, 150);
    analogWrite(enableB, 0);
    
    delay(75);

    digitalWrite(motorA1, LOW);
    digitalWrite(motorA2, LOW);
    digitalWrite(motorB1, LOW);
    digitalWrite(motorB2, LOW);
}

void MotorController::brakeTurnRight() {
    digitalWrite(motorA1, LOW);
    digitalWrite(motorA2, HIGH);
    digitalWrite(motorB1, HIGH);
    digitalWrite(motorB2, LOW);
    analogWrite(enableA, 0);
    analogWrite(enableB, 150);

    delay(75);

    digitalWrite(motorA1, LOW);
    digitalWrite(motorA2, LOW);
    digitalWrite(motorB1, LOW);
    digitalWrite(motorB2, LOW);
}