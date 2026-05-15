#include "classes/IntervalTimer.h"

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

// ----------------------------------------------------- Objects -----------------------------------------------------

IntervalTimer null_reconnection(NULL_RECONNECTION_INTERVAL);
IntervalTimer battery_level_update(BATTERY_LEVEL_UPDATE_INTERVAL);
