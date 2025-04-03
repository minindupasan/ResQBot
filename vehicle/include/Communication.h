#ifndef COMMUNICATION_H
#define COMMUNICATION_H
#include <Arduino.h>
#include <WiFiEsp.h>
#include <WiFiEspServer.h>
#include <SoftwareSerial.h>
#include "arduino_secrets.h"  // Include your secrets file

const int bluetoothRx = 18; // HC-06 TX → Mega RX1 (Pin 18)
const int bluetoothTx = 19; // HC-06 RX → Mega TX1 (Pin 19)

void initBluetooth();
String receiveRoomNumber();

#endif  // COMMUNICATION_H