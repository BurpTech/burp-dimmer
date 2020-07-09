#pragma once

#include <Arduino.h>

namespace BurpDimmer {

  namespace Light {
    constexpr char filePath[] = "/light.json";
    constexpr size_t fileSize = 256;
    constexpr int pin = D1;
    constexpr int rotaryEncoderPinA = D5;
    constexpr int rotaryEncoderPinB = D6;
    constexpr int buttonPin = D7;
  }

  namespace Config {
    constexpr char filePath[] = "/config.json";
    constexpr size_t fileSize = 1024;
  }

  constexpr unsigned long buttonDebounceDelay = 20;
  constexpr int blinkerPin = LED_BUILTIN;
  constexpr unsigned long blinkTime = 200;
  constexpr int blinkerOn = LOW;
  constexpr int buttonPin = D2;
  constexpr unsigned long shortDelay = 2000;
  constexpr unsigned long longDelay = 5000;

}
