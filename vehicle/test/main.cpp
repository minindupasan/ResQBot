#include <Arduino.h>

const int bluetoothRx = 18; // HC-06 TX → Mega RX1 (Pin 18)
const int bluetoothTx = 19; // HC-06 RX → Mega TX1 (Pin 19)

void setup() {
    Serial.begin(115200);
    Serial1.begin(9600); // HC-06 default baud rate
    Serial.println("Arduino Mega Ready to Receive via HC-06");
}

void loop() {
    if (Serial1.available()) {
        String receivedData = Serial1.readStringUntil('\n');
        Serial.print("📩 Received: ");
        Serial.println(receivedData);
    }
}