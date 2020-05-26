#ifndef Blinker_hpp
#define Blinker_hpp

#include <Arduino.h>

#include "Debug.hpp"

class Blinker {
  public:
    struct Pattern {
      unsigned long off;
      unsigned long on;
    };

    Blinker(int pin, int on) :
      _pin(pin),
      _on(on) {
    }

    void setup() {
      pinMode(_pin, OUTPUT);
      _set(State::OFF);
    }

    // Blinking is synchronous so we don't interrupt it
    void blink(const Pattern ** pattern) {
      while (*pattern) {
        _set(State::OFF);
        delay((*pattern)->off);
        _set(State::ON);
        delay((*pattern)->on);
        pattern++;
      }
      _set(State::OFF);
    }

  private:
    enum State {
      ON = true,
      OFF = false
    };

    int _pin;
    int _on;

    void _set(State state) {
      DEBUG_PRINT(state ? "ON" : "OFF");
      digitalWrite(_pin, state ? _on : !_on);
    }
};

#endif
