#include "FireSuppression.h"
#include <Servo.h>

FireSuppressionSystem::FireSuppressionSystem() {
    this->pumpRelayPin = PUMP_RELAY_PIN;
    this->servoPin = SERVO_PIN;
    this->sensor1 = FLAME_SENSOR_1;
    this->sensor2 = FLAME_SENSOR_2;
    this->sensor3 = FLAME_SENSOR_3;
    this->isSuppressing = false;
}

void FireSuppressionSystem::initialize() {
    nozzleServo.attach(servoPin);
    pinMode(pumpRelayPin, OUTPUT);
    pinMode(sensor1, INPUT);
    pinMode(sensor2, INPUT);
    pinMode(sensor3, INPUT);
    digitalWrite(pumpRelayPin, HIGH); // Initialize relay as OFF
}

void FireSuppressionSystem::checkFire() {
    state1 = digitalRead(sensor1);
    state2 = digitalRead(sensor2);
    state3 = digitalRead(sensor3);

    if((state1==LOW || state2==LOW || state3==LOW) && !isSuppressing) {
        activateSuppression();
    } else {
        stopSuppression();
    }
    
}

void FireSuppressionSystem::activateSuppression() {
    isSuppressing = true;
    digitalWrite(pumpRelayPin, LOW); // Turn on relay
    for(int i=0; i<180; i++) {
        nozzleServo.write(i);
        delay(5);
    }
    for(int i=180; i>0; i--) {
        nozzleServo.write(i);
        delay(5);
    }
    nozzleServo.write(90);
    gyroController.resetSystem();
}

void FireSuppressionSystem::stopSuppression() {
    digitalWrite(pumpRelayPin, HIGH); // Turn off relay
    isSuppressing = false;
}
