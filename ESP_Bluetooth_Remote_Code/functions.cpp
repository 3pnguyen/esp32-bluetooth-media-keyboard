#include <Arduino.h>
#include <BleCombo.h>
#include <esp_sleep.h>
#include "misc/functions.h"
#include "customizable-info/pins.h"

void wakeUp() {
  delay(20);
  Keyboard.begin();
}

void goToSleep() {
  Serial.println("Entering sleep…");
  Serial.flush();
  Keyboard.end();
  gpio_wakeup_enable((gpio_num_t)SLEEP_BUTTON, GPIO_INTR_HIGH_LEVEL);
  esp_sleep_enable_gpio_wakeup();
  esp_light_sleep_start();
}

void pressMediaKey(const uint8_t *key, String keyName, int debounce) {
  if (keyName != "") Serial.println("→ " + keyName);
  Keyboard.write(key);
  delay(debounce);
}

int voltageToPercent(float v) {
  const int N = 9;
  const float volts[N] = {4.20, 4.00, 3.95, 3.90, 3.85, 3.80, 3.70, 3.60, 3.30};
  const int pct[N]   = {100,  85,   75,   60,   50,   35,   20,   10,    0};

  if (v >= volts[0]) return 100;
  if (v <= volts[N-1]) return 0;

  for (int i = 0; i < N-1; ++i) {
    if (v <= volts[i] && v >= volts[i+1]) {
      float t = (v - volts[i+1]) / (volts[i] - volts[i+1]); // 0..1
      float p = pct[i+1] + t * (pct[i] - pct[i+1]);
      return (int)round(p);
    }
  }
  return 0;
}