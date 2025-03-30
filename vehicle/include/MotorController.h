#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include <Arduino.h>
#include "GyroController.h"
#include "FireSuppression.h"

#define TARGET_ANGLE 70
#define OBSTACLE_THRESHOLD 17  // Set obstacle detection threshold in cm

class MotorController {
public:
    MotorController(int motorA1, int motorA2, int enableA, int motorB1, int motorB2, int enableB, int trigPin, int echoPin, GyroController &gyro, FireSuppressionSystem &fireSystem);
    void moveForward(int speed);
    void moveBackward(int speed);
    void turnLeft(int speed);
    void turnRight(int speed);
    void controlCar();
    void brakeTurnLeft();
    void brakeTurnRight();
    void brake();
    void stopMoving();
    void stopMotors();
    float getObstacleDistance(); // Function to get distance from ultrasonic sensor

private:
    int motorA1, motorA2, enableA;
    int motorB1, motorB2, enableB;
    int trigPin, echoPin; // Ultrasonic sensor pins
    GyroController *gyro;
    FireSuppressionSystem *fireSystem;
};

#endif