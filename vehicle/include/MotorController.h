#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include <Arduino.h>
#include "GyroController.h"

class MotorController {
public:
    MotorController(int motorA1, int motorA2, int enableA, int motorB1, int motorB2, int enableB, int irObstacle, GyroController &gyro);
    void moveForward(int speed);
    void moveBackward(int speed);
    void stop();
    void turnLeft();
    void turnRight();

private:
    int motorA1, motorA2, enableA;
    int motorB1, motorB2, enableB;
    int irObstacle;
    GyroController *gyro;
};

#endif