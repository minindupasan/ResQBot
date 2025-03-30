#include <Arduino.h>
#define TRIG_PIN 9  // Define the pin connected to the TRIG of the ultrasonic sensor
#define ECHO_PIN 10 // Define the pin connected to the ECHO of the ultrasonic sensor

void setup() {
    Serial.begin(115200); // Start serial communication at 9600 baud
    pinMode(TRIG_PIN, OUTPUT); // Set TRIG pin as an output
    pinMode(ECHO_PIN, INPUT);  // Set ECHO pin as an input
}

void loop() {
    long duration;
    float distance;

    // Trigger the ultrasonic pulse
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    // Read the echo response
    duration = pulseIn(ECHO_PIN, HIGH);

    // Convert duration to distance (in cm)
    distance = duration * 0.034 / 2;

    // Print the distance
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    delay(500); // Wait before next measurement
}