#include "./Blinker.hpp"

#include <Arduino.h>

namespace Components {

  Blinker::Blinker(int pin, int on) :
    _pin(pin),
    _on(on) {
  }

  void Blinker::setup() {
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, !_on);
  }

  void Blinker::blink(size_t count, unsigned long delay) {
    blink(count, delay, delay);
  }

  // Blinking is synchronous so we don't interrupt it
  void Blinker::blink(size_t count, unsigned long on, unsigned long off) {
    if (count) {
      digitalWrite(_pin, _on);
      delay(on);
      for (size_t i = 1; i < count; i++) {
        digitalWrite(_pin, !_on);
        delay(off);
        digitalWrite(_pin, _on);
        delay(on);
      }
      digitalWrite(_pin, !_on);
    }
  }

}
