#ifndef COMMUNICATION_H
#define COMMUNICATION_H
#include <Arduino.h>
#include <WiFiEsp.h>
#include <WiFiEspServer.h>
#include <SoftwareSerial.h>
#include "arduino_secrets.h"  // Include your secrets file

#define BT_RX 18 // HC-06 TX → Mega RX1 (Pin 18)
#define BT_TX 19 // HC-06 RX → Mega TX1 (Pin 19)

class Communication {
public:
    Communication();
    void initBluetooth();
    String receiveRoomNumber();

private:
    String roomNumber;
};

#endif  // COMMUNICATION_H