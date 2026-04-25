#pragma once

#include <Arduino.h>
#include "pins.h"

class ReleaseDebounce {
  private:
    uint8_t pin;
    bool pressedFlag;

  public:
    ReleaseDebounce(uint8_t buttonPin);
    bool update();
    bool isPressed();
};

// ----------------------------------------------------- Objects -----------------------------------------------------

extern ReleaseDebounce button_one;
extern ReleaseDebounce button_two;
extern ReleaseDebounce button_three;
extern ReleaseDebounce cycle_button;
