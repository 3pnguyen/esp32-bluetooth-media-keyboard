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

IntervalTimer bluetooth_led_flash(BLUETOOTH_LED_FLASH_INTERVAL);
IntervalTimer indicator_led_flash(INDICATOR_LED_FLASH_INTERVAL);
IntervalTimer null_reconnection(NULL_RECONNECTION_INTERVAL);
IntervalTimer battery_level_update(BATTERY_LEVEL_UPDATE_INTERVAL);
