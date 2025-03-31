#include "communication.h"

WiFiClient client;
void initWiFi() {
    Serial.print("📶 Connecting to Wi-Fi...");
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("\n✅ Connected to Wi-Fi!");
} 

void sendFireAlert(int roomNumber) {

    Serial.print("📤 Sending fire alert for Room ");
    Serial.println(roomNumber);

    if (client.connect(SERVER_IP, SERVER_PORT)) {
        String httpRequest = "GET /fire?room=" + String(roomNumber) + " HTTP/1.1\r\n" +
                             "Host: " + String(SERVER_IP) + "\r\n" +
                             "Connection: close\r\n\r\n";
        client.print(httpRequest);
        client.stop();
        Serial.println("✅ Alert sent successfully.");
    } else {
        Serial.println("❌ Failed to connect to ESP-01.");
    }
}