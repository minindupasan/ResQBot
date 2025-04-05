#include "Communication.h"

Communication::Communication() {
    // Constructor
}

void Communication::initBluetooth() {
    Serial.begin(115200);
    Serial1.begin(9600); // HC-06 default baud rate
    Serial.println("Vehicle Ready to Receive via HC-06");
}

String Communication::receiveRoomNumber() {
    if (Serial1.available()) {
        roomNumber = Serial1.readStringUntil('\n');
        roomNumber.trim();  // Remove trailing newline or spaces
    }
    return roomNumber;
}                                                                                                               