#include <Arduino.h>
#include <BleCombo.h>
#include <driver/gpio.h>
#include <esp_sleep.h>
#include "battery.h"
#include "pins.h"
#include "functions.h"

#include "classes/TimeDebounce.h"
#include "classes/ReleaseDebounce.h"
#include "classes/IntervalTimer.h"
#include "classes/Incremental.h"
#include "classes/ChangeDetector.h"
#include "classes/EMAFilter.h"

//#define TEST

//no need for a debounce class for the sleep button

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
