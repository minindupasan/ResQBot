#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <Arduino.h>
#include <WiFi.h>
#include "arduino_secrets.h"

// Wi-Fi credentials
#define WIFI_SSID SECRET_SSID
#define WIFI_PASSWORD SECRET_PASS

// ESP-01 Server IP Address (Static IP)
#define SERVER_IP "192.168.1.100"
#define SERVER_PORT 80

// Function prototype
void sendFireAlert(int roomNumber);
void initWiFi();

#endif