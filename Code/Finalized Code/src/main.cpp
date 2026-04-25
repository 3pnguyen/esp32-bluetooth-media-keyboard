#include <Arduino.h>
#include <BleCombo.h>
#include <driver/gpio.h>
#include <esp_sleep.h>
#include "battery.h"
#include "pins.h"

#include "classes/TimeDebounce.h"
#include "classes/ReleaseDebounce.h"
#include "classes/IntervalTimer.h"
#include "classes/Incremental.h"
#include "classes/ChangeDetector.h"
#include "classes/EMAFilter.h"

void wakeUp();
void goToSleep();
void setIndicatorLedsOff();
void setIndicatorLedHold(bool enabled);
void pressMediaKey(const uint8_t *key, String keyName = "", int debounce = 50);
int voltageToPercent(float v);

//#define TEST

ReleaseDebounce button_one(BUTTON_1);
ReleaseDebounce button_two(BUTTON_2);
ReleaseDebounce button_three(BUTTON_3);
ReleaseDebounce cycle_button(BUTTON_4);
//no need for a debounce class for the sleep button
IntervalTimer bluetooth_led_flash(300);
IntervalTimer indicator_led_flash(150);
IntervalTimer null_reconnection(3000);
Incremental indicator_led_incremental;
ChangeDetector<int> section_selection(0);
EMAFilter<float> voltage_ema(0.5, 3.65);
IntervalTimer battery_level_update(1000);

int section = 0;

void setup() {
  pinMode(BUTTON_1, INPUT_PULLUP);
  pinMode(BUTTON_2, INPUT_PULLUP);
  pinMode(BUTTON_3, INPUT_PULLUP);
  pinMode(BUTTON_4, INPUT_PULLUP);
  pinMode(SLEEP_BUTTON, INPUT_PULLUP);
  pinMode(POWER_VD, INPUT);
  pinMode(INDICATOR_LED_R, OUTPUT);
  pinMode(INDICATOR_LED_G, OUTPUT);
  pinMode(INDICATOR_LED_B, OUTPUT);
  setIndicatorLedsOff();

  Serial.begin(115200);
  Serial.println("\nBegin\n");


  delay(20);
  if (digitalRead(SLEEP_BUTTON) == HIGH) {
    Serial.println("Lid is open – staying awake");
    wakeUp();
  } else {
    Serial.println("Lid closed – go back to sleep immediately");
    goToSleep();
    wakeUp();
  }
}

void loop() {
  float voltage = (analogRead(POWER_VD) / ADC_MAX) * VREF * ((POWER_VD_R1 + POWER_VD_R2) / POWER_VD_R2);
  voltage_ema.calculate(voltage);
  int percent = voltageToPercent(voltage);
  digitalWrite(INDICATOR_LED_R, (voltage_ema.aboveThreshold()) ? LOW : HIGH);

  if (digitalRead(SLEEP_BUTTON) == LOW) {
    delay(100);
    if (digitalRead(SLEEP_BUTTON) == LOW) {
      goToSleep();
      wakeUp();
    }
  }

  if (Keyboard.isConnected()) {
    digitalWrite(INDICATOR_LED_B, LOW);

    if (battery_level_update.isReady()) Keyboard.setBatteryLevel(percent);
    
    if (cycle_button.update()) {
      section = (section + 1) % 2;
      Serial.println("Section: " + String(section));
    }

    #ifdef TEST
    #else
      if (section_selection.update(section)) indicator_led_incremental.reset();
      switch (section) {
        case 0:
          if (button_one.update()) pressMediaKey(KEY_MEDIA_PLAY_PAUSE, "Play/Pause");
          else if (button_two.update()) pressMediaKey(KEY_MEDIA_PREVIOUS_TRACK, "Previous Track");
          else if (button_three.update()) pressMediaKey(KEY_MEDIA_NEXT_TRACK, "Next Track");
          if (indicator_led_flash.isReady() && indicator_led_incremental.counter < 2) {
            indicator_led_incremental.increment();
            digitalWrite(INDICATOR_LED_G, (digitalRead(INDICATOR_LED_G) == HIGH) ? LOW : HIGH);
          }
          break;

        case 1:
          if (button_one.update()) pressMediaKey(KEY_MEDIA_VOLUME_UP, "Volume Up");
          else if (button_two.update()) pressMediaKey(KEY_MEDIA_VOLUME_DOWN, "Volume Down");
          else if (button_three.update()) pressMediaKey(KEY_MEDIA_MUTE, "Mute");
          if (indicator_led_flash.isReady() && indicator_led_incremental.counter < 4) {
            indicator_led_incremental.increment();
            digitalWrite(INDICATOR_LED_G, (digitalRead(INDICATOR_LED_G) == HIGH) ? LOW : HIGH);
          }
          break;
      }
    #endif

  } else {
    digitalWrite(INDICATOR_LED_R, LOW);
    digitalWrite(INDICATOR_LED_G, LOW);

    if (bluetooth_led_flash.isReady()) digitalWrite(INDICATOR_LED_B, (digitalRead(INDICATOR_LED_B) == HIGH) ? LOW : HIGH);

    if (null_reconnection.isReady()) {
      null_reconnection.reset();
      ESP.restart();
    }
  }

  delay(5);
}

void wakeUp() {
  setIndicatorLedHold(false);
  setIndicatorLedsOff();
  bluetooth_led_flash.reset();
  indicator_led_flash.reset();
  null_reconnection.reset();
  delay(20);
  Keyboard.begin();
  setIndicatorLedsOff();
}

void goToSleep() {
  Serial.println("Entering sleep…");
  Serial.flush();
  setIndicatorLedsOff();
  Keyboard.end();
  setIndicatorLedsOff();
  setIndicatorLedHold(true);
  gpio_wakeup_enable((gpio_num_t)SLEEP_BUTTON, GPIO_INTR_HIGH_LEVEL);
  esp_sleep_enable_gpio_wakeup();
  esp_light_sleep_start();
  setIndicatorLedHold(false);
  setIndicatorLedsOff();
  gpio_wakeup_disable((gpio_num_t)SLEEP_BUTTON);
}

void setIndicatorLedsOff() {
  digitalWrite(INDICATOR_LED_R, LOW);
  digitalWrite(INDICATOR_LED_G, LOW);
  digitalWrite(INDICATOR_LED_B, LOW);
}

void setIndicatorLedHold(bool enabled) {
  if (enabled) {
    gpio_hold_en((gpio_num_t)INDICATOR_LED_R);
    gpio_hold_en((gpio_num_t)INDICATOR_LED_G);
    gpio_hold_en((gpio_num_t)INDICATOR_LED_B);
  } else {
    gpio_hold_dis((gpio_num_t)INDICATOR_LED_R);
    gpio_hold_dis((gpio_num_t)INDICATOR_LED_G);
    gpio_hold_dis((gpio_num_t)INDICATOR_LED_B);
  }
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
