#include "gsm.h"

// Create instance for GSM communication using SoftwareSerial
SoftwareSerial gsmSerial(RX_PIN, TX_PIN);

void sendSMS(String message) {
  // Initialize GSM module
  gsmSerial.begin(9600);
  
  // Set GSM module to text message mode
  gsmSerial.println("AT+CMGF=1");
  delay(1000);

  // Send message to predefined phone number
  gsmSerial.println("AT+CMGS=\"+1234567890\"");  // Replace with your phone number
  delay(1000);
  gsmSerial.println(message);  // Send the message
  delay(1000);
  gsmSerial.write(26);  // Send Ctrl+Z to send the message
  delay(1000);
  
  Serial.println("Message sent.");
}