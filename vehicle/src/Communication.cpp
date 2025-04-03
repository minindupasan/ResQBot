#include "Communication.h"

void initBluetooth() {
    Serial.begin(115200);
    Serial1.begin(9600); // HC-06 default baud rate
    Serial.println("Vehicle Ready to Receive via HC-06");
}

String receiveRoomNumber() {
    String receivedData;
    if (Serial1.available()) {
        receivedData = Serial1.readStringUntil('\n');
        Serial.print("Received: ");
        Serial.println(receivedData);
    }
    return receivedData;
}