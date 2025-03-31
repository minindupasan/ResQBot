#ifndef MQ_HUMIDITY_MONITOR_H
#define MQ_HUMIDITY_MONITOR_H

#include <DHT.h>

// Define sensor pins
#define MQ_PIN           34      // MQ sensor analog pin
#define DHT_PIN          15      // DHT sensor digital pin
#define DHT_TYPE         DHT22   // Change to DHT11 if using DHT11 sensor

// Threshold for fire detection (can adjust as needed)
#define FIRE_THRESHOLD   200     // MQ sensor threshold

// Threshold for humidity detection (optional logic)
#define HUMIDITY_THRESHOLD 60    // Humidity threshold

// Function declarations
int readMQSensor();
float readHumidity();

#endif // MQ_HUMIDITY_MONITOR_H