#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

void setup() {
    Serial.begin(115200);

    // Enable Master Mode by setting second parameter to `true`
    SerialBT.begin("ESP32_BT", true);  
    Serial.println("ESP32 Bluetooth Started in Master Mode");

    // Try to connect to HC-05
    bool connected = SerialBT.connect("HC-06");
    if (connected) {
        Serial.println("✅ Connected to HC-06!");
    } else {
        Serial.println("❌ Failed to connect. Make sure HC-06 is in pairing mode.");
    }
}

void loop() {
    if (SerialBT.connected()) {
        Serial.println("✅ HC-05 Connected!");
        if (SerialBT.available()) {
            String receivedData = SerialBT.readStringUntil('\n');
            Serial.print("📩 Received: ");
            Serial.println(receivedData);
        }
    } else {
        Serial.println("⏳ Waiting for HC-05 connection...");
        delay(2000);
    }
}