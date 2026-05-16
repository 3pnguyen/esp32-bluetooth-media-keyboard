#include <Arduino.h>
#include <BleCombo.h>
#include <driver/gpio.h>
#include <esp_sleep.h>
#include "constants/battery.h"
#include "constants/pins.h"
#include "constants/led.h"
#include "functions.h"

#include "classes/ReleaseDebounce.h"
#include "classes/IntervalTimer.h"
#include "classes/Incremental.h"
#include "classes/ChangeDetector.h"
#include "classes/EMAFilter.h"

int section = 0;
// Last battery percentage sent over BLE. Starts invalid so the first reading is always reported.
int reportedBatteryPercent = -1;

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
  #ifndef TEST

    float pinVoltage = analogReadMilliVolts(POWER_VD) / 1000.0;
    float voltage = pinVoltage * ((POWER_VD_R1 + POWER_VD_R2) / POWER_VD_R2);
    voltage_ema.calculate(voltage);
    // Use the filtered voltage for percent conversion; raw ADC readings can jitter enough to bounce the BLE level.
    int percent = voltageToPercent(voltage_ema.level);
    
    if (voltage_ema.aboveThreshold()) setIndicatorLedOff(INDICATOR_LED_R);
    else analogWrite(INDICATOR_LED_R, R_BRIGHTNESS);

    if (digitalRead(SLEEP_BUTTON) == LOW) {
      delay(100);
      if (digitalRead(SLEEP_BUTTON) == LOW) {
        goToSleep();
        wakeUp();
      }
    }

    if (Keyboard.isConnected()) {
      setIndicatorLedsOff();

      if (battery_level_update.isReady()) {
        // Only report meaningful changes so the host does not see 1% oscillations around lookup-table boundaries.
        if (reportedBatteryPercent < 0 || abs(percent - reportedBatteryPercent) >= BATTERY_REPORT_HYSTERESIS) {
          reportedBatteryPercent = percent;
          Keyboard.setBatteryLevel(reportedBatteryPercent);
        }
      }
      
      if (cycle_button.update()) {
        section = (section + 1) % 2;
        Serial.println("Section: " + String(section));
        blinkLED(INDICATOR_LED_G, G_BRIGHTNESS, section + 1, INDICATOR_LED_FLASH_INTERVAL);
      }

      switch (section) {
        case 0:
          if (button_one.update()) pressMediaKey(KEY_MEDIA_PLAY_PAUSE, "Play/Pause");
          else if (button_two.update()) pressMediaKey(KEY_MEDIA_PREVIOUS_TRACK, "Previous Track");
          else if (button_three.update()) pressMediaKey(KEY_MEDIA_NEXT_TRACK, "Next Track");
          break;

        case 1:
          if (button_one.update()) pressMediaKey(KEY_MEDIA_VOLUME_UP, "Volume Up");
          else if (button_two.update()) pressMediaKey(KEY_MEDIA_VOLUME_DOWN, "Volume Down");
          else if (button_three.update()) pressMediaKey(KEY_MEDIA_MUTE, "Mute");
          break;
      }

    } else {
      setIndicatorLedOff(INDICATOR_LED_R);
      setIndicatorLedOff(INDICATOR_LED_G);

      blinkLED(INDICATOR_LED_B, B_BRIGHTNESS, 1, BLUETOOTH_LED_FLASH_INTERVAL);      

      if (null_reconnection.isReady()) {
        null_reconnection.reset();
        ESP.restart();
      }
    }

  #else

  #endif

  delay(5);
}
