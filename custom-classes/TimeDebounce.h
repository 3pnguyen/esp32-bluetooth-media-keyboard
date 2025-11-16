#ifndef TIMEDEOUNCE_H
#define TIMEDEBOUNCE_H

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

#endif