#include "Communication.h"

SoftwareSerial megaSerial(ARDUINO_RX, ARDUINO_TX);  // Serial communication with Mega
WiFiEspServer server(80);  // Server running on port 80

void setupWiFi() {
    Serial.begin(115200);
    megaSerial.begin(9600);

    // Start Wi-Fi connection
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("\n✅ ESP-01 Connected to Wi-Fi!");
}

void setupServer() {
    server.begin();  // Start the server to listen for incoming requests
}

void handleClientRequests() {
    WiFiEspClient client = server.available();
    if (client) {
        String request = client.readStringUntil('\r');
        Serial.println(request);
        
        if (request.indexOf("GET /fire?room=1") != -1) {
            Serial.println("🔥 Fire Alert: Room 1");
            sendRoomToMega('1');  // Send room number 1 to Arduino Mega
        } 
        else if (request.indexOf("GET /fire?room=2") != -1) {
            Serial.println("🔥 Fire Alert: Room 2");
            sendRoomToMega('2');  // Send room number 2 to Arduino Mega
        }

        client.flush();
        client.stop();
    }
}

void sendRoomToMega(char roomNumber) {
    megaSerial.write(roomNumber);  // Send room number to Arduino Mega
}