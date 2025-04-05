#include "MotorController.h"
#include <Arduino.h>


MotorController::MotorController(int motorA1, int motorA2, int enableA, int motorB1, int motorB2, int enableB, int trigPin, int echoPin,int irRight, GyroController &gyro, FireSuppressionSystem &fireSystem) {
    this->motorA1 = motorA1;
    this->motorA2 = motorA2;
    this->enableA = enableA;
    this->motorB1 = motorB1;
    this->motorB2 = motorB2;
    this->enableB = enableB;
    this->trigPin = trigPin;
    this->echoPin = echoPin;
    this->irRight = irRight;
    this->gyro = &gyro;
    this->fireSystem = &fireSystem;

    pinMode(motorA1, OUTPUT);
    pinMode(motorA2, OUTPUT);
    pinMode(enableA, OUTPUT);
    pinMode(motorB1, OUTPUT);
    pinMode(motorB2, OUTPUT);
    pinMode(enableB, OUTPUT);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(irRight, INPUT);
}

bool MotorController::isObstacleDetected() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    long duration = pulseIn(echoPin, HIGH);
    float distance = duration * 0.034 / 2; // Convert to cm

    return distance < OBSTACLE_THRESHOLD;
}

void MotorController::moveForward(int baseSpeed) {
    if (isObstacleDetected() || fireSystem->isFireDetected()) {
        stopMoving();
        if (fireSystem->isFireDetected()) {
            Serial.println("Fire detected! Stopping motors.");
            fireSystem->activateSuppression();
            delay(2000); // Wait for 2 seconds
            moveBackward(60); // Move backward for 2 seconds
            delay(1000);
        }
        else {
            Serial.println("Obstacle detected! Stopping motors.");
        }
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
    Serial.println("Stopping motors");
    brake();
    digitalWrite(motorA1, LOW);
    digitalWrite(motorA2, LOW);
    digitalWrite(motorB1, LOW);
    digitalWrite(motorB2, LOW);
    analogWrite(enableA, 0);
    analogWrite(enableB, 0);
    delay(2000);
}

void MotorController::stopMotors() {
    Serial.println("Stopping motors");
    digitalWrite(motorA1, LOW);
    digitalWrite(motorA2, LOW);
    digitalWrite(motorB1, LOW);
    digitalWrite(motorB2, LOW);
    analogWrite(enableA, 0);
    analogWrite(enableB, 0);
}

void MotorController::turnLeft(int speed) {
    Serial.println("Turning left");
    float targetYaw = gyro->getYaw() - TARGET_ANGLE;
    stopMotors();

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
    stopMotors();
    gyro->resetSystem();
}

void MotorController::turnRight(int speed) {
    Serial.println("Turning right");
    float targetYaw = gyro->getYaw() + TARGET_ANGLE;
    stopMotors();

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
    // gyro->resetSystem();
}

void MotorController::controlCar() {
    int turningSpeed = 60;
    bool fireDetected = fireSystem->isFireDetected();

    // Obstacle detection logic
    if (isObstacleDetected()) {
        Serial.println("Turning right due to obstacle!");
        stopMoving();
        turnRight(turningSpeed);
    } 
    // Fire detection logic
    else if (fireDetected) {
        Serial.println("Fire detected! Stopping motors and activating suppression.");
        stopMoving();                    // Stop motors before suppressing fire
        fireSystem->activateSuppression(); // Activate fire suppression
    } 
    // Default case: move forward if no obstacle or fire detected
    else {
        Serial.println("No obstacle, no fire detected. Moving forward.");
        moveForward(60); 
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

int MotorController::isRightDetected() {
    return(digitalRead(irRight)==LOW);
}

void MotorController::moveToRoom(String roomNumber) {
    int turningSpeed = 60;
    int speed = 60;
    Serial.print("Moving to room: ");
    Serial.println(roomNumber);

    if (roomNumber == "room1") {
        Serial.println("Navigating to Room 1"); 
        moveForward(speed);

        if (!isRightDetected() && !isObstacleDetected()) {
            Serial.println("Room 1 detected, turning right");
            delay(300);
            stopMoving();
            delay(2000); // Wait for 2 seconds
            turnRight(turningSpeed);
            delay(2000); // Adjust delay as needed
            moveForward(speed);
        } else if (isObstacleDetected()) {
            Serial.println("Obstacle detected, stopping");
            stopMoving();
        }
    }
}