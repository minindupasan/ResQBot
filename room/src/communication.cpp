#include <WiFi.h>
#include "communication.h"  // Ensure this has roomNumber as a global or passed variable

WiFiServer server(80);  // Port 80
WiFiClient client;

void initWifi() {
  Serial.println("Initializing WiFi...");

  WiFi.begin(SECRET_SSID, SECRET_OPTIONAL_PASS);

  // Wait for connection with timeout
  unsigned long startAttempt = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - startAttempt < 15000) {
    Serial.println("Connecting to WiFi...");
    delay(1000);
  }

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi connection failed!");
    return;
  }

  Serial.println("Connected to WiFi");
  Serial.print("ESP32 IP Address: ");
  Serial.println(WiFi.localIP());

  server.begin();
  Serial.println("Server started on port 80");
}

void sendRoomNumber(String roomNumber) {
  // Check if already connected
  if (!client || !client.connected()) {
    Serial.println("Waiting for client to connect...");
    client = server.available();
  }

  if (client && client.connected()) {
    client.println(roomNumber);
    Serial.println("Room number sent to Arduino: " + roomNumber);
  } else {
    Serial.println("Client not connected yet.");
  }
}