#pragma once

#include <Arduino.h>
#include <BleCombo.h>
#include <driver/gpio.h>
#include <esp_sleep.h>
#include "pins.h"

#include "classes/IntervalTimer.h" 

void wakeUp();
void goToSleep();
void setIndicatorLedsOff();
void setIndicatorLedHold(bool enabled);
void pressMediaKey(const uint8_t *key, String keyName = "", int debounce = 50);
int voltageToPercent(float v);