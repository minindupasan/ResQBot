#include "GyroController.h"
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Arduino.h>

GyroController::GyroController() {
    // Constructor implementation
}

void GyroController::initialize() {
    if (!mpu.begin()) {
        Serial.println("Failed to find MPU6050 chip");
        while (1) {
            delay(10);
        }
    }
    Serial.println("MPU6050 Found!");
    calibrateGyro();
    lastTime = millis();
}

float GyroController::getYaw() {
    unsigned long currentTime = millis();
    float dt = (currentTime - lastTime) / 1000.0; // Time difference in seconds
    lastTime = currentTime;

    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    // Gyroscope Z-axis value in degrees per second
    float gyroZ = g.gyro.z * 57.2958 - gyroZ_offset; // Convert rad/s to deg/s and subtract offset

    // Integrate gyroscope data to get yaw angle
    currentYaw += gyroZ * dt;

    return currentYaw;
}

void GyroController::calibrateGyro() {
    Serial.println("Calibrating gyroscope...");
    float sum = 0;
    int n = 500;

    for (int i = 0; i < n; i++) {
        sensors_event_t a, g, temp;
        mpu.getEvent(&a, &g, &temp);
        sum += g.gyro.z * 57.2958; // Convert rad/s to deg/s
        delay(5);
    }

    gyroZ_offset = sum / n;
    Serial.print("Gyro Z Offset: ");
    Serial.println(gyroZ_offset);
    Serial.println("Calibration complete!");
}