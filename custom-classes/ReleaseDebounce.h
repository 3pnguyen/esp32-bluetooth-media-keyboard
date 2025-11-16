#ifndef RELEASEDEBOUNCE_H
#define RELEASEDEBOUNCE_H

class ReleaseDebounce {
  private:
    uint8_t pin;
    bool pressedFlag;

  public:
    ReleaseDebounce(uint8_t buttonPin);
    bool update();
    bool isPressed();
};

#endif