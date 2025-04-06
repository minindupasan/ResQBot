#include <Arduino.h>
#include "MotorController.h"
#include "GyroController.h"
#include "FireSuppression.h"
#include "Communication.h"

GyroController gyro;
FireSuppressionSystem fireSystem;
MotorController motor(MOTOR_A1, MOTOR_A2, ENABLE_A, MOTOR_B1, MOTOR_B2, ENABLE_B, TRIG_PIN, ECHO_PIN, IR_RIGHT, gyro, fireSystem);
Communication wifi;

String roomNumber;

void setup() {
    Serial.begin(115200);  // Debugging via USB
    Serial1.begin(115200); // Communication with ESP12E
    delay(2000); // Allow time for the ESP12E to initialize
    
    Serial.println("Initializing...");
    wifi.initWifi();  
    Serial.println("Wi-Fi initialized");
  
    gyro.initialize();
    fireSystem.initialize();
  }                                             

void loop() {
    float currentYaw = gyro.getYaw();
    Serial.print("Current Yaw: ");
    Serial.println(currentYaw);
    roomNumber = wifi.receiveRoomNumber();  
    
    if (roomNumber.length() > 0) { 
        Serial.print("Received Room Number: ");
        Serial.println(roomNumber);
        motor.moveToRoom(roomNumber);
    }

    delay(50); 
}