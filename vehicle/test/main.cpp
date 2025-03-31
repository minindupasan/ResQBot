#include <Arduino.h>

#define TRIG_PIN 9  // Define the pin connected to the TRIG of the ultrasonic sensor
#define ECHO_PIN 10 // Define the pin connected to the ECHO of the ultrasonic sensor

// Define pins for the flame sensors
#define FLAME_SENSOR_1 24
#define FLAME_SENSOR_2 22
#define FLAME_SENSOR_3 26

void setup() {
    Serial.begin(115200); // Start serial communication at 115200 baud
    pinMode(TRIG_PIN, OUTPUT); // Set TRIG pin as an output
    pinMode(ECHO_PIN, INPUT);  // Set ECHO pin as an input

    // Set flame sensor pins as input
    pinMode(FLAME_SENSOR_1, INPUT);
    pinMode(FLAME_SENSOR_2, INPUT);
    pinMode(FLAME_SENSOR_3, INPUT);
}

void loop() {
    // Test ultrasonic sensor
    long duration;
    float distance;

    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    duration = pulseIn(ECHO_PIN, HIGH);
    distance = duration * 0.034 / 2;

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    // Test flame sensors
    int flame1 = digitalRead(FLAME_SENSOR_1);
    int flame2 = digitalRead(FLAME_SENSOR_2);
    int flame3 = digitalRead(FLAME_SENSOR_3);

    Serial.print("Flame Sensor 1: ");
    Serial.println(flame1 == LOW ? "Flame detected" : "No flame");

    Serial.print("Flame Sensor 2: ");
    Serial.println(flame2 == LOW ? "Flame detected" : "No flame");

    Serial.print("Flame Sensor 3: ");
    Serial.println(flame3 == LOW ? "Flame detected" : "No flame");

    delay(50); // Wait before next measurement
}