#include "mqHumidityMonitor.h"
#include <Arduino.h>  

// Create an instance for the DHT sensor
DHT dht(DHT_PIN, DHT_TYPE);

int readMQSensor() {
  // Read MQ sensor value
  return analogRead(MQ_PIN);
}

float readHumidity() {
  // Initialize DHT sensor
  dht.begin();
  
  // Read and return humidity value
  return dht.readHumidity();
}