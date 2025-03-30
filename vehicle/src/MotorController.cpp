#include "MotorController.h"
#include "GyroController.h"
#include <Arduino.h>

MotorController::MotorController(int motorA1, int motorA2, int enableA, int motorB1, int motorB2, int enableB, int irObstacle, GyroController &gyro) {
    this->motorA1 = motorA1;
    this->motorA2 = motorA2;
    this->enableA = enableA;
    this->motorB1 = motorB1;
    this->motorB2 = motorB2;
    this->enableB = enableB;
    this->irObstacle = irObstacle;
    this->gyro = &gyro;

    pinMode(motorA1, OUTPUT);
    pinMode(motorA2, OUTPUT);
    pinMode(enableA, OUTPUT);
    pinMode(motorB1, OUTPUT);
    pinMode(motorB2, OUTPUT);
    pinMode(enableB, OUTPUT);
    pinMode(irObstacle, INPUT);
}

void MotorController::moveForward(int baseSpeed) {
    if (digitalRead(irObstacle) == LOW) {
        stop();
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
    if (digitalRead(irObstacle) == LOW) {
        stop();
        Serial.println("Obstacle detected! Stopping motors.");
        return;
    }
    
    analogWrite(enableA, speed);
    analogWrite(enableB, speed);
    digitalWrite(motorA1, HIGH);
    digitalWrite(motorA2, LOW);
    digitalWrite(motorB1, HIGH);
    digitalWrite(motorB2, LOW);
}

void MotorController::stop() {
    // Apply brief reverse power for braking
    digitalWrite(motorA1, HIGH);
    digitalWrite(motorA2, LOW);
    digitalWrite(motorB1, HIGH);
    digitalWrite(motorB2, LOW);
    analogWrite(enableA, 150); // Adjust braking power (0-255)
    analogWrite(enableB, 150);

    delay(25); // Short braking duration (tune as needed)
    brake(); // Complete stop
}

void MotorController::turnLeft(int speed) {
    float targetYaw = gyro->getYaw() - 90.0;
    stop();
    
    analogWrite(enableA, speed);
    analogWrite(enableB, speed);
    digitalWrite(motorA1, LOW);
    digitalWrite(motorA2, HIGH);
    digitalWrite(motorB1, HIGH);
    digitalWrite(motorB2, LOW);
    
    while (gyro->getYaw() > targetYaw) {
        Serial.println(gyro->getYaw());
        delay(10);
    }

    brakeTurnLeft();
}

void MotorController::turnRight(int speed) {
    float targetYaw =  90.0;
    stop();
    
    analogWrite(enableA, speed);
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
}

void MotorController::brake(){
        // Completely stop the motors
        digitalWrite(motorA1, LOW);
        digitalWrite(motorA2, LOW);
        digitalWrite(motorB1, LOW);
        digitalWrite(motorB2, LOW);
        analogWrite(enableA, 0);
        analogWrite(enableB, 0);
        delay(2000); // Allow time for the motors to stop
}

void MotorController::brakeTurnLeft() {
    // Reverse motors briefly for braking effect

    digitalWrite(motorA1, HIGH);
    digitalWrite(motorA2, LOW);
    digitalWrite(motorB1, LOW);
    digitalWrite(motorB2, HIGH);
    analogWrite(enableA, 150); // Braking power (0-255)
    analogWrite(enableB, 150);
    
    delay(100);  // Braking duration for turning left (tune as needed)
    digitalWrite(motorA1, LOW);
    digitalWrite(motorA2, LOW);
    digitalWrite(motorB1, LOW);
    digitalWrite(motorB2, LOW);
}

void MotorController::brakeTurnRight() {
    // Reverse motors briefly for braking effect
    digitalWrite(motorA1, LOW);
    digitalWrite(motorA2, HIGH);
    digitalWrite(motorB1, HIGH);
    digitalWrite(motorB2, LOW);
    analogWrite(enableA, 150); // Braking power (0-255)
    analogWrite(enableB, 150);

    delay(100);  // Braking duration for turning right (tune as needed)

    digitalWrite(motorA1, LOW);
    digitalWrite(motorA2, LOW);
    digitalWrite(motorB1, LOW);
    digitalWrite(motorB2, LOW);
}

void MotorController::controlCar() {
    int turningSpeed = 70; // Adjust turning speed as needed
    // Replace condition1 and condition2 with your actual conditions
    if (0) {
        turnLeft(turningSpeed);
    }
    else if (1) {
        turnRight(turningSpeed );
    }
    else if (digitalRead(irObstacle) == LOW) {
        stop();
        Serial.println("Obstacle detected! Stopping motors.");
    }
    else {
        moveForward(50); // Adjust the base speed as needed
    }
}