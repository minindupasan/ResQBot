#ifndef FLAME_DETECTION_H
#define FLAME_DETECTION_H

#include <Arduino.h>

// Define the pin for IR flame sensor
#define IR_FLAME_PIN_1     4       // IR flame sensor digital pin
#define IR_FLAME_PIN_2     5       // IR flame sensor digital pin
#define BUZZER_PIN 25

void fireControl();
void alertFire();
int detectFlame();
void alertBuzzer(int frequency =1000);
void stopBuzzer();

#endif // FLAME_DETECTION_H