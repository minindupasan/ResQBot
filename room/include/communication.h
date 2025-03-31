#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <WiFi.h>

// Wi-Fi credentials
#define WIFI_SSID "Dialog 4G 875"
#define WIFI_PASSWORD "f45902DF"

// ESP-01 Server IP Address (Static IP)
#define SERVER_IP "192.168.1.100"
#define SERVER_PORT 80

// Function prototype
void sendFireAlert(int roomNumber);
void initWiFi();

#endif