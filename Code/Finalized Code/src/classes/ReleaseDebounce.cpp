#include "classes/ReleaseDebounce.h"

//debounce classes done by chatgpt lol

ReleaseDebounce::ReleaseDebounce(uint8_t buttonPin) {
  pin = buttonPin;
  pinMode(pin, INPUT_PULLUP);
  pressedFlag = false;
}

bool ReleaseDebounce::update() {
  bool state = digitalRead(pin);

  if (state == LOW && !pressedFlag) {
    // button pressed down, but don't trigger yet
    pressedFlag = true;
  }

  if (state == HIGH && pressedFlag) {
    // button released -> trigger event
    pressedFlag = false;
    return true;
  }

  return false; // no event
}

bool ReleaseDebounce::isPressed() {
  return digitalRead(pin) == LOW;
}

// ----------------------------------------------------- Objects -----------------------------------------------------

ReleaseDebounce button_one(BUTTON_1);
ReleaseDebounce button_two(BUTTON_2);
ReleaseDebounce button_three(BUTTON_3);
ReleaseDebounce cycle_button(BUTTON_4);
