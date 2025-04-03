#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <Arduino.h>
#include "BluetoothSerial.h"

// Function prototype
void initBluetooth();
void sendRoomNumber(String roomNumber);

#endif