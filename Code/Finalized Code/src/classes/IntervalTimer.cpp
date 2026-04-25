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

IntervalTimer bluetooth_led_flash(300);
IntervalTimer indicator_led_flash(150);
IntervalTimer null_reconnection(3000);
IntervalTimer battery_level_update(1000);
