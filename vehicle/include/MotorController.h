#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include <Arduino.h>

class MotorController {
public:
    MotorController(int motorA1, int motorA2, int enableA, int motorB1, int motorB2, int enableB, int irLeft, int irRight,int irObstacle);
    void moveForward(int speed);
    void moveBackward(int speed);
    void stop();
    void adjustSpeed();
    void LEFT();
    void RIGHT();

private:
    int motorA1, motorA2, enableA;
    int motorB1, motorB2, enableB;
    int irLeft, irRight,irObstacle;
};

#endif