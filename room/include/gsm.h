#ifndef GSM_H
#define GSM_H

#include <Arduino.h>
#include <SoftwareSerial.h>

// Define GSM module pins
#define RX_PIN           16      // GSM RX pin
#define TX_PIN           17      // GSM TX pin

// Function declaration to send SMS
void sendSMS(String message);

#endif // GSM_SIM800_H