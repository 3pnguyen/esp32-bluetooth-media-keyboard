#pragma once

#include <Arduino.h>

class TimeDebounce {
  private:
    uint8_t pin;
    unsigned long debounceDelay;
    unsigned long lastChangeTime;
    bool lastStableState;
    bool currentState;

  public:
    TimeDebounce(uint8_t buttonPin, unsigned long delayMs = 20);
    bool update();
    bool isPressed();
};
