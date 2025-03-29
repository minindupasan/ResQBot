#include "flame_detection.h"

bool detectFlame() {
  // Read IR flame sensor value and return if flame is detected (HIGH indicates flame detected)
  return digitalRead(IR_FLAME_PIN) == HIGH;
}