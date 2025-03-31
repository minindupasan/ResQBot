#include "flame_detection.h"

void fireControl() {
  int flameDetected = detectFlame();  // Store the result once

  if (flameDetected == 1) {
    Serial.println("🔥 Fire detected in Room 1!");
    alertFire();
  }
  else if (flameDetected == 2) {
    Serial.println("🔥 Fire detected in Room 2!");
    alertFire();
  }
  else {
    Serial.println("✅ No fire detected.");
    stopBuzzer(); // Ensure buzzer stops if no fire is detected
  }
}

int detectFlame() {
  // Read sensor values once
  int room1State = digitalRead(IR_FLAME_PIN_1);
  int room2State = digitalRead(IR_FLAME_PIN_2);

  Serial.print("📡 Room 1 Sensor: ");
  Serial.println(room1State);
  Serial.print("📡 Room 2 Sensor: ");
  Serial.println(room2State);

  if (room1State == HIGH) return 1;
  if (room2State == LOW) return 2;
  
  return 0;
}

void alertFire() {
  for (int i = 0; i < 3; i++) {
    alertBuzzer(1000); // Alert with a tone
    delay(500);
    stopBuzzer();
    delay(500);
  }
}

void alertBuzzer(int frequency) {
  tone(BUZZER_PIN, frequency); // Generate a tone at the given frequency
}

void stopBuzzer() {
  noTone(BUZZER_PIN); // Stop the tone
}