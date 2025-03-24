#include <Arduino.h>
#include "MotorController.h"
#include "GyroController.h"

// Motor pin definitions
int motorA1 = 42;  // IN1
int motorA2 = 40;  // IN2
int enableA = 2;  // ENA (Enable pin)
int motorB1 = 38;  // IN3
int motorB2 = 36;  // IN4
int enableB = 3;  // ENB (Enable pin)

// Define IR sensor pins
#define IR_LEFT 50
#define IR_RIGHT 52

// Create motor controller object
MotorController motor(motorA1, motorA2, enableA, motorB1, motorB2, enableB, IR_LEFT, IR_RIGHT);
 
GyroController gyro;

void setup() {
    Serial.begin(115200);
    while (!Serial)
        delay(10); // Wait for serial port to connect

    gyro.initialize();  // Initialize the gyroscope
}

void loop() {
    // Get the current yaw from the gyroscope
    float currentYaw = gyro.getYaw();

    // Calculate the yaw error (desired yaw = 0)
    float yawError = currentYaw;  // Assuming we want to keep yaw at 0

    // Adjust motor speeds based on yaw error to maintain a straight path
    motor.adjustSpeed(yawError);

    Serial.print("Yaw: ");
    Serial.print(currentYaw);
    Serial.print(" Yaw Error: ");
    Serial.println(yawError);

    delay(50);
}