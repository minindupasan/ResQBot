#ifndef COMMUNICATION_H
#define COMMUNICATION_H
#include <Arduino.h>
#include <WiFiEsp.h>
#include <WiFiEspServer.h>
#include <SoftwareSerial.h>

// Wi-Fi Credentials
#define WIFI_SSID "Dialog 4G 875"
#define WIFI_PASSWORD "f45902DF"

// Pin Definitions for Communication
#define ARDUINO_RX 10  // Connect to Mega TX
#define ARDUINO_TX 11  // Connect to Mega RX

// SoftwareSerial for communication with Arduino Mega
extern SoftwareSerial megaSerial;

// WiFi server for handling requests
extern WiFiEspServer server;

// Function Declarations
void setupWiFi();
void setupServer();
void handleClientRequests();
void sendRoomToMega(char roomNumber);

#endif  // COMMUNICATION_H