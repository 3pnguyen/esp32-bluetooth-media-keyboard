#include <Arduino.h>
#include "custom-classes/TimeDebounce.h"

//debounce classes done by chatgpt lol

TimeDebounce::TimeDebounce(uint8_t buttonPin, unsigned long delayMs) {
  pin = buttonPin;
  debounceDelay = delayMs;
  pinMode(pin, INPUT_PULLUP);
  lastStableState = digitalRead(pin);
  currentState = lastStableState;
  lastChangeTime = millis();
}

bool TimeDebounce::update() {
  bool reading = digitalRead(pin);
  if (reading != lastStableState) {
    // reset timer when state changes
    lastChangeTime = millis();
  }
  if ((millis() - lastChangeTime) > debounceDelay) {
    if (reading != currentState) {
      currentState = reading;
      return true;  // state changed and stable
    }
  }
  lastStableState = reading;
  return false;  // no stable change yet
}

bool TimeDebounce::isPressed() {
  return currentState == LOW;  // assuming LOW = pressed
}
