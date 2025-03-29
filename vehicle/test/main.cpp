#include <Arduino.h>

// Define IR sensor pins
int irLeft = 49;  // Left IR sensor
int irRight = 51; // Right IR sensor
int irObstacle = 50; // Obstacle IR sensor

void setup() {
    Serial.begin(115200);
    while (!Serial)
        delay(10);

    // Initialize IR sensor pins as inputs
    pinMode(irLeft, INPUT);
    pinMode(irRight, INPUT);
    pinMode(irObstacle, INPUT);
}

void loop() {
    // Read sensor values
    int leftValue = digitalRead(irLeft);
    int rightValue = digitalRead(irRight);
    int obstacleValue = digitalRead(irObstacle);

    // Print sensor values
    Serial.print("Left IR: ");
    Serial.print(leftValue);
    Serial.print(" | Right IR: ");
    Serial.print(rightValue);
    Serial.print(" | Obstacle IR: ");
    Serial.println(obstacleValue);

    delay(500); // Adjust delay as needed
}