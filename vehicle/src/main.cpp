#include <Arduino.h>
#include "MotorController.h"
#include "GyroController.h"
#include "FireSuppression.h"
#include "Communication.h"

GyroController gyro;
FireSuppressionSystem fireSystem;
MotorController motor(MOTOR_A1, MOTOR_A2, ENABLE_A, MOTOR_B1, MOTOR_B2, ENABLE_B, TRIG_PIN, ECHO_PIN,IR_RIGHT, gyro, fireSystem);
Communication bt;

String roomNumber;

void setup() {
    Serial.begin(115200);
    bt.initBluetooth();
    gyro.initialize();
    fireSystem.initialize();
}                                               

void loop() {
    float currentYaw = gyro.getYaw();
    String roomNumber = bt.receiveRoomNumber();  // Get once
    Serial.print("Received Room Number: ");
    Serial.println(roomNumber);
    motor.moveToRoom(roomNumber);  // Use the same value
    Serial.print("Yaw: ");
    Serial.println(currentYaw);
    delay(50);
}