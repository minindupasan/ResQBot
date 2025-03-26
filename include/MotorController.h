#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

class MotorController {
public:
    MotorController(int motorA1, int motorA2, int enableA, int motorB1, int motorB2, int enableB, int irSensor);
    void moveForward(int speed);
    void moveBackward(int speed);
    void stop();
    void adjustSpeed(float yawError);

private:
    int motorA1, motorA2, enableA;
    int motorB1, motorB2, enableB;
    int irSensor;  // IR sensor pins
};

#endif