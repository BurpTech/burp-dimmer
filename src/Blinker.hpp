#ifndef Blinker_hpp
#define Blinker_hpp

#include <Arduino.h>

#include "Debug.hpp"

class Blinker {
  public:
    Blinker(int pin, int on) :
      _pin(pin),
      _on(on) {
    }

    void setup() {
      pinMode(_pin, OUTPUT);
      _set(_OFF);
    }

    void blink(size_t count, unsigned long delay) {
      blink(count, delay, delay);
    }

    // Blinking is synchronous so we don't interrupt it
    void blink(size_t count, unsigned long on, unsigned long off) {
      if (count) {
        _set(_ON);
        delay(on);
        for (size_t i = 1; i < count; i++) {
          _set(_OFF);
          delay(off);
          _set(_ON);
          delay(on);
        }
        _set(_OFF);
      }
    }

  private:
    enum State {
      _ON = true,
      _OFF = false
    };

    int _pin;
    int _on;

    void _set(State state) {
      DEBUG_PRINT(state ? "ON" : "OFF");
      digitalWrite(_pin, state ? _on : !_on);
    }
};

#endif
