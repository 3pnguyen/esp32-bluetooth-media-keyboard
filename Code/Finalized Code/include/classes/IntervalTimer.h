#pragma once

#include <Arduino.h>

class IntervalTimer {
  private:
    unsigned long lastTime = 0;
    unsigned long interval;

  public:
    IntervalTimer(unsigned long intervalMs);
    bool isReady();
    void reset();
};

// ----------------------------------------------------- Objects -----------------------------------------------------

extern IntervalTimer bluetooth_led_flash;
extern IntervalTimer indicator_led_flash;
extern IntervalTimer null_reconnection;
extern IntervalTimer battery_level_update;
