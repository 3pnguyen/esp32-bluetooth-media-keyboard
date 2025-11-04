#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <Arduino.h>

void wakeUp();
void goToSleep();
void pressMediaKey(const uint8_t *key, String keyName = "", int debounce = 50);
int voltageToPercent(float v);

#endif