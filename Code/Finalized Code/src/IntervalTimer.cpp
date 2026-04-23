#include <Arduino.h>
#include "IntervalTimer.h"

IntervalTimer::IntervalTimer(unsigned long intervalMs) : interval(intervalMs) {}

bool IntervalTimer::isReady() {
  unsigned long currentTime = millis();

  if (currentTime - lastTime >= interval) {
    lastTime = currentTime;
    return true;
  }
  return false;
}

void IntervalTimer::reset() {
  lastTime = millis();
}
