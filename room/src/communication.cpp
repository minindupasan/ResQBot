#include "communication.h"

BluetoothSerial SerialBT;

void initBluetooth() {
    SerialBT.begin("ESP32_BT", true);  // Master Mode
    Serial.println("ESP32 Bluetooth Started in Master Mode");

    while (!SerialBT.connect("HC-06")) {
        Serial.println("❌ Failed to connect. Retrying... Ensure Vehicle is in pairing mode.");
        delay(1000); // Wait before retrying
    }

    Serial.println("✅ Connected to Vehicle!");
}

void sendRoomNumber(String roomNumber) {
    if (SerialBT.connected()) {
        SerialBT.println(roomNumber); // Send message to HC-06
        Serial.println("Room number sent to Vehicle");
    } else {
        Serial.println("Waiting for Vehicle connection...");
    }
    delay(1000);
}