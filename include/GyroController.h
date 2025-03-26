#ifndef GYROCONTROLLER_H
#define GYROCONTROLLER_H

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <Arduino.h>
#include <avr/wdt.h> // Required for watchdog functions

class GyroController {
public:
    GyroController();
    void initialize();
    float getYaw();
    void calibrateGyro();
    void resetSystem();

private:
    Adafruit_MPU6050 mpu;
    float currentYaw = 0;   // Current yaw angle
    float gyroZ_offset = 0; // Offset for gyro drift
    unsigned long lastTime = 0;
};

#endif